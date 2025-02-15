// SPDX-License-Identifier: Apache-2.0
// Copyright 2021 Ricardo Quesada
// http://retro.moe/unijoysticle2

#include "sdkconfig.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#include "arduino_bootstrap.h"
#include "arduino_platform.h"

#include <esp_arduino_version.h>
#include <esp_chip_info.h>
#include <esp_console.h>
#include <esp_ota_ops.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#include "bt/uni_bt.h"
#include "cmd_system.h"
#include "controller/uni_controller.h"
#include "platform/uni_platform.h"
#include "uni_common.h"
#include "uni_hid_device.h"
#include "uni_log.h"
#include "uni_version.h"

// Sanity check
#ifndef CONFIG_BLUEPAD32_PLATFORM_CUSTOM
#error "Must use BLUEPAD32_PLATFORM_CUSTOM"
#endif

//
// Globals
//
#define MAX_PENDING_REQUESTS 16

// Arduino device "instance"
typedef struct arduino_instance_s {
    // Gamepad index, from 0 to CONFIG_BLUEPAD32_MAX_DEVICES
    // -1 means gamepad was not assigned yet.
    // It is used to map "controllers_" to the uni_hid_device.
    int8_t controller_idx;
} arduino_instance_t;
_Static_assert(sizeof(arduino_instance_t) < HID_DEVICE_MAX_PLATFORM_DATA, "Arduino instance too big");

static QueueHandle_t pending_queue_ = NULL;
static SemaphoreHandle_t controller_mutex_ = NULL;
static arduino_controller_t controllers_[CONFIG_BLUEPAD32_MAX_DEVICES];
static int used_controllers_ = 0;

static arduino_instance_t* get_arduino_instance(uni_hid_device_t* d);
static uint8_t predicate_arduino_index(uni_hid_device_t* d, void* data);

//
// Shared by CPU 0 (bluetooth) / CPU1 (Arduino)
//
// BTStack / Bluepad32 are not thread safe.
// This code is the bridge between CPU1 and CPU0.
//

typedef enum {
    PENDING_REQUEST_CMD_NONE = 0,
    PENDING_REQUEST_CMD_LIGHTBAR_COLOR = 1,
    PENDING_REQUEST_CMD_PLAYER_LEDS = 2,
    PENDING_REQUEST_CMD_RUMBLE = 3,
    PENDING_REQUEST_CMD_DISCONNECT = 4,
} pending_request_cmd_t;

typedef struct {
    // Gamepad index: from 0 to CONFIG_BLUEPAD32_MAX_DEVICES-1
    uint8_t controller_idx;
    pending_request_cmd_t cmd;
    // Must have enough space to hold at least 4 arguments: red, green, blue
    union {
        uint8_t player_led;
        uint8_t leds[3];
        struct {
            uint16_t rumble_delayed_start;
            uint16_t rumble_duration;
            uint8_t rumble_weak_magnitude;
            uint8_t rumble_strong_magnitude;
        };
    } args;
} pending_request_t;

//
// CPU 0 - Bluepad32 process
//

// BTStack / Bluepad32 are not thread safe.
// Be extra careful when calling code that runs on the other CPU

static void arduino_init(int argc, const char** argv) {
    memset(&controllers_, 0, sizeof(controllers_));
    for (int i = 0; i < CONFIG_BLUEPAD32_MAX_DEVICES; i++) {
        controllers_[i].idx = UNI_ARDUINO_GAMEPAD_INVALID;
    }
}

static uint8_t predicate_arduino_index(uni_hid_device_t* d, void* data) {
    int wanted_idx = (int)data;
    arduino_instance_t* ins = get_arduino_instance(d);
    if (ins->controller_idx != wanted_idx)
        return 0;
    return 1;
}

static void process_pending_requests(void) {
    pending_request_t request;

    while (xQueueReceive(pending_queue_, &request, (TickType_t)0) == pdTRUE) {
        int idx = request.controller_idx;
        uni_hid_device_t* d = uni_hid_device_get_instance_with_predicate(predicate_arduino_index, (void*)idx);
        if (d == NULL) {
            loge("Arduino: device cannot be found while processing pending request\n");
            return;
        }
        switch (request.cmd) {
            case PENDING_REQUEST_CMD_LIGHTBAR_COLOR:
                if (d->report_parser.set_lightbar_color != NULL)
                    d->report_parser.set_lightbar_color(d, request.args.leds[0], request.args.leds[1],
                                                        request.args.leds[2]);
                break;
            case PENDING_REQUEST_CMD_PLAYER_LEDS:
                if (d->report_parser.set_player_leds != NULL)
                    d->report_parser.set_player_leds(d, request.args.player_led);
                break;

            case PENDING_REQUEST_CMD_RUMBLE:
                if (d->report_parser.play_dual_rumble != NULL)
                    d->report_parser.play_dual_rumble(d, request.args.rumble_delayed_start,
                                                      request.args.rumble_duration, request.args.rumble_weak_magnitude,
                                                      request.args.rumble_strong_magnitude);
                break;

            case PENDING_REQUEST_CMD_DISCONNECT:
                // Don't call "uni_hid_device_disconnect" since it will
                // disconnect the "d" immediately and functions in the
                // stack trace might depend on it. Instead, call it from
                // a callback.
                idx = uni_hid_device_get_idx_for_instance(d);
                uni_bt_disconnect_device_safe(idx);
                break;

            default:
                loge("Arduino: Invalid pending command: %d\n", request.cmd);
        }
    }
}

//
// Platform Overrides
//
static void arduino_on_init_complete(void) {
    controller_mutex_ = xSemaphoreCreateMutex();
    assert(controller_mutex_ != NULL);

    pending_queue_ = xQueueCreate(MAX_PENDING_REQUESTS, sizeof(pending_request_t));
    assert(pending_queue_ != NULL);

#if !CONFIG_AUTOSTART_ARDUINO
    arduino_bootstrap();
#endif  // !CONFIG_AUTOSTART_ARDUINO
}

static void arduino_on_device_connected(uni_hid_device_t* d) {
    arduino_instance_t* ins = get_arduino_instance(d);
    memset(ins, 0, sizeof(*ins));
    ins->controller_idx = UNI_ARDUINO_GAMEPAD_INVALID;
}

static void arduino_on_device_disconnected(uni_hid_device_t* d) {
    arduino_instance_t* ins = get_arduino_instance(d);
    // Only process it if the gamepad has been assigned before
    if (ins->controller_idx != UNI_ARDUINO_GAMEPAD_INVALID) {
        if (ins->controller_idx < 0 || ins->controller_idx >= CONFIG_BLUEPAD32_MAX_DEVICES) {
            loge("Arduino: unexpected gamepad idx, got: %d, want: [0-%d]\n", ins->controller_idx,
                 CONFIG_BLUEPAD32_MAX_DEVICES);
            return;
        }
        used_controllers_--;

        memset(&controllers_[ins->controller_idx], 0, sizeof(controllers_[0]));
        controllers_[ins->controller_idx].idx = UNI_ARDUINO_GAMEPAD_INVALID;

        ins->controller_idx = UNI_ARDUINO_GAMEPAD_INVALID;
    }
}

static uni_error_t arduino_on_device_ready(uni_hid_device_t* d) {
    if (used_controllers_ == CONFIG_BLUEPAD32_MAX_DEVICES) {
        // No more available seats, reject connection
        logi("Arduino: More available seats\n");
        return UNI_ERROR_NO_SLOTS;
    }

    arduino_instance_t* ins = get_arduino_instance(d);
    if (ins->controller_idx != UNI_ARDUINO_GAMEPAD_INVALID) {
        loge("Arduino: unexpected value for on_device_ready; got: %d, want: -1\n", ins->controller_idx);
        return UNI_ERROR_INVALID_CONTROLLER;
    }

    // Find first available controller
    for (int i = 0; i < CONFIG_BLUEPAD32_MAX_DEVICES; i++) {
        if (controllers_[i].idx == UNI_ARDUINO_GAMEPAD_INVALID) {
            controllers_[i].idx = i;

            memcpy(controllers_[i].properties.btaddr, d->conn.btaddr, sizeof(controllers_[0].properties.btaddr));
            controllers_[i].properties.type = d->controller_type;
            controllers_[i].properties.subtype = d->controller_type;
            controllers_[i].properties.vendor_id = d->vendor_id;
            controllers_[i].properties.product_id = d->product_id;
            controllers_[i].properties.flags =
                (d->report_parser.set_player_leds ? ARDUINO_PROPERTY_FLAG_PLAYER_LEDS : 0) |
                (d->report_parser.play_dual_rumble ? ARDUINO_PROPERTY_FLAG_RUMBLE : 0) |
                (d->report_parser.set_lightbar_color ? ARDUINO_PROPERTY_FLAG_PLAYER_LIGHTBAR : 0);

            ins->controller_idx = i;
            used_controllers_++;
            break;
        }
    }

    logd("Arduino: assigned gamepad idx is: %d\n", ins->controller_idx);

    if (d->report_parser.set_player_leds != NULL) {
        d->report_parser.set_player_leds(d, ins->controller_idx + 1);
    }
    return UNI_ERROR_SUCCESS;
}

static void arduino_on_controller_data(uni_hid_device_t* d, uni_controller_t* ctl) {
    process_pending_requests();

    arduino_instance_t* ins = get_arduino_instance(d);
    if (ins->controller_idx < 0 || ins->controller_idx >= CONFIG_BLUEPAD32_MAX_DEVICES) {
        loge("Arduino: unexpected gamepad idx, got: %d, want: [0-%d]\n", ins->controller_idx,
             CONFIG_BLUEPAD32_MAX_DEVICES);
        return;
    }

    // Populate gamepad data on shared struct.
    xSemaphoreTake(controller_mutex_, portMAX_DELAY);
    controllers_[ins->controller_idx].data = *ctl;
    controllers_[ins->controller_idx].data_updated = true;
    xSemaphoreGive(controller_mutex_);
}

static void arduino_on_device_oob_event(uni_platform_oob_event_t event, void* data) {
    ARG_UNUSED(event);
    ARG_UNUSED(data);
    // TODO: Do something ?
}

static const uni_property_t* arduino_get_property(uni_property_idx_t idx) {
    ARG_UNUSED(idx);
    return NULL;
}

// Public: But must be called from CPU 0 - BTstack/BP32 process
uni_hid_device_t* arduino_get_internal_hid_device(int controller_idx) {
    if (controller_idx == UNI_ARDUINO_GAMEPAD_INVALID) {
        loge("Arduino: Invalid controller_idx, controller not assigned yet ?\n");
        return NULL;
    }
    if (controller_idx < 0 || controller_idx >= CONFIG_BLUEPAD32_MAX_DEVICES) {
        loge("Arduino: Invalid controller_idx, idx outside scope. controller_idx: %d\n", controller_idx);
        return NULL;
    }
    uni_hid_device_t* d = uni_hid_device_get_instance_with_predicate(predicate_arduino_index, (void*)controller_idx);
    if (!d) {
        loge("Arduino: device cannot be found for controller_idx: %d\n", controller_idx);
        return NULL;
    }
    return d;
}

//
// CPU 1 - Application (Arduino) process
//
int arduino_get_gamepad_data(int idx, arduino_gamepad_data_t* out_data) {
    int ret;

    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    ret = UNI_ARDUINO_ERROR_NO_DATA;
    xSemaphoreTake(controller_mutex_, portMAX_DELAY);
    if (controllers_[idx].data_updated) {
        *out_data = controllers_[idx].data.gamepad;
        controllers_[idx].data_updated = false;
        ret = UNI_ARDUINO_ERROR_SUCCESS;
    }
    xSemaphoreGive(controller_mutex_);

    return ret;
}

int arduino_get_controller_data(int idx, arduino_controller_data_t* out_data) {
    int ret;

    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    ret = UNI_ARDUINO_ERROR_NO_DATA;
    xSemaphoreTake(controller_mutex_, portMAX_DELAY);
    if (controllers_[idx].data_updated) {
        *out_data = controllers_[idx].data;
        controllers_[idx].data_updated = false;
        ret = UNI_ARDUINO_ERROR_SUCCESS;
    }
    xSemaphoreGive(controller_mutex_);

    return ret;
}

int arduino_get_gamepad_properties(int idx, arduino_gamepad_properties_t* out_properties) {
    return arduino_get_controller_properties(idx, out_properties);
}

int arduino_get_controller_properties(int idx, arduino_controller_properties_t* out_properties) {
    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    xSemaphoreTake(controller_mutex_, portMAX_DELAY);
    *out_properties = controllers_[idx].properties;
    xSemaphoreGive(controller_mutex_);

    return UNI_ARDUINO_ERROR_SUCCESS;
}

int arduino_set_player_leds(int idx, uint8_t leds) {
    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    pending_request_t request = (pending_request_t){
        .controller_idx = idx,
        .cmd = PENDING_REQUEST_CMD_PLAYER_LEDS,
        .args.player_led = leds,
    };
    xQueueSendToBack(pending_queue_, &request, (TickType_t)0);

    return UNI_ARDUINO_ERROR_SUCCESS;
}

int arduino_set_lightbar_color(int idx, uint8_t r, uint8_t g, uint8_t b) {
    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    pending_request_t request = (pending_request_t){
        .controller_idx = idx,
        .cmd = PENDING_REQUEST_CMD_LIGHTBAR_COLOR,
        .args.leds[0] = r,
        .args.leds[1] = g,
        .args.leds[2] = b,
    };
    xQueueSendToBack(pending_queue_, &request, (TickType_t)0);

    return UNI_ARDUINO_ERROR_SUCCESS;
}

int arduino_play_dual_rumble(int idx,
                             uint16_t delayed_start_ms,
                             uint16_t duration_ms,
                             uint8_t weak_magnitude,
                             uint8_t strong_magnitude) {
    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    pending_request_t request = (pending_request_t){
        .controller_idx = idx,
        .cmd = PENDING_REQUEST_CMD_RUMBLE,
        .args.rumble_delayed_start = delayed_start_ms,
        .args.rumble_duration = duration_ms,
        .args.rumble_weak_magnitude = weak_magnitude,
        .args.rumble_strong_magnitude = strong_magnitude,
    };
    xQueueSendToBack(pending_queue_, &request, (TickType_t)0);

    return UNI_ARDUINO_ERROR_SUCCESS;
}

int arduino_disconnect_controller(int idx) {
    if (idx < 0 || idx >= CONFIG_BLUEPAD32_MAX_DEVICES)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;
    if (controllers_[idx].idx == UNI_ARDUINO_GAMEPAD_INVALID)
        return UNI_ARDUINO_ERROR_INVALID_DEVICE;

    pending_request_t request = (pending_request_t){
        .controller_idx = idx,
        .cmd = PENDING_REQUEST_CMD_DISCONNECT,
    };
    xQueueSendToBack(pending_queue_, &request, (TickType_t)0);

    return UNI_ARDUINO_ERROR_SUCCESS;
}

int arduino_forget_bluetooth_keys(void) {
    uni_bt_del_keys_safe();
    return UNI_ARDUINO_ERROR_SUCCESS;
}

static void version(void) {
    esp_chip_info_t info;
    esp_chip_info(&info);

    const esp_app_desc_t* app_desc = esp_app_get_description();

    logi("\nFirmware info:\n");
    logi("\tBluepad32 Version: v%s (%s)\n", UNI_VERSION_STRING, app_desc->version);
    logi("\tArduino Core Version: v%d.%d.%d\n", ESP_ARDUINO_VERSION_MAJOR, ESP_ARDUINO_VERSION_MINOR,
         ESP_ARDUINO_VERSION_PATCH);
    logi("\tCompile Time: %s %s\n", app_desc->date, app_desc->time);

    logi("\n");
    cmd_system_version();
}

static int cmd_version(int argc, char** argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    version();
    return 0;
}

static void arduino_register_cmds(void) {
    const esp_console_cmd_t version = {
        .command = "version",
        .help = "Gets the Firmware version",
        .hint = NULL,
        .func = &cmd_version,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&version));
}

//
// Helpers
//
static arduino_instance_t* get_arduino_instance(uni_hid_device_t* d) {
    return (arduino_instance_t*)&d->platform_data[0];
}

//
// Public
//
struct uni_platform* get_arduino_platform(void) {
    static struct uni_platform plat = {
        .name = "Arduino",
        .init = arduino_init,
        .on_init_complete = arduino_on_init_complete,
        .on_device_connected = arduino_on_device_connected,
        .on_device_disconnected = arduino_on_device_disconnected,
        .on_device_ready = arduino_on_device_ready,
        .on_oob_event = arduino_on_device_oob_event,
        .on_controller_data = arduino_on_controller_data,
        .get_property = arduino_get_property,
        .register_console_cmds = arduino_register_cmds,
    };

    return &plat;
}
