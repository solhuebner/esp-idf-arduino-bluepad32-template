
// clang-format off
// ../src/components/bluepad32/include/bt/uni_bt_service.gatt.h generated from ../src/components/bluepad32/bt/uni_bt_service.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate ../src/components/bluepad32/include/bt/uni_bt_service.gatt.h:
// ../external/btstack/tool/compile_gatt.py ../src/components/bluepad32/bt/uni_bt_service.gatt ../src/components/bluepad32/include/bt/uni_bt_service.gatt.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#include <stdint.h>

// Reference: https://en.cppreference.com/w/cpp/feature_test
#if __cplusplus >= 200704L
constexpr
#endif
const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME - READ
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE CHARACTERISTIC-GAP_DEVICE_NAME - READ -'Bluepad32'
    // READ_ANYBODY
    0x11, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x2a, 0x42, 0x6c, 0x75, 0x65, 0x70, 0x61, 0x64, 0x33, 0x32, 
    // 0x0004 PRIMARY_SERVICE-GATT_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x01, 0x18, 
    // 0x0005 CHARACTERISTIC-GATT_DATABASE_HASH - READ
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x02, 0x06, 0x00, 0x2a, 0x2b, 
    // 0x0006 VALUE CHARACTERISTIC-GATT_DATABASE_HASH - READ -''
    // READ_ANYBODY
    0x18, 0x00, 0x02, 0x00, 0x06, 0x00, 0x2a, 0x2b, 0xff, 0x6d, 0x13, 0xfc, 0x16, 0x4f, 0xb3, 0xd3, 0x3f, 0x90, 0xbf, 0x11, 0x30, 0x5d, 0x19, 0x59, 
    // Bluepad32 Service
    // 0x0007 PRIMARY_SERVICE-4627C4A4-AC00-46B9-B688-AFC5C1BF7F63
    0x18, 0x00, 0x02, 0x00, 0x07, 0x00, 0x00, 0x28, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x00, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Bluepad32 Characteristics
    // Bluepad32 version
    // 0x0008 CHARACTERISTIC-4627C4A4-AC01-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x08, 0x00, 0x03, 0x28, 0x02, 0x09, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x01, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0009 VALUE CHARACTERISTIC-4627C4A4-AC01-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    // READ_ANYBODY
    0x16, 0x00, 0x02, 0x03, 0x09, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x01, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Max supported connections
    // 0x000a CHARACTERISTIC-4627C4A4-AC02-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x03, 0x28, 0x02, 0x0b, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x02, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x000b VALUE CHARACTERISTIC-4627C4A4-AC02-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    // READ_ANYBODY
    0x16, 0x00, 0x02, 0x03, 0x0b, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x02, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Whether to enable BLE connections
    // 0x000c CHARACTERISTIC-4627C4A4-AC03-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x03, 0x28, 0x0a, 0x0d, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x03, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x000d VALUE CHARACTERISTIC-4627C4A4-AC03-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x0d, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x03, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Scan for new connections
    // 0x000e CHARACTERISTIC-4627C4A4-AC04-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x0e, 0x00, 0x03, 0x28, 0x0a, 0x0f, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x04, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x000f VALUE CHARACTERISTIC-4627C4A4-AC04-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x0f, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x04, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // List of connected devices. Returns all connected devices at once.
    // 0x0010 CHARACTERISTIC-4627C4A4-AC05-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x10, 0x00, 0x03, 0x28, 0x02, 0x11, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x05, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0011 VALUE CHARACTERISTIC-4627C4A4-AC05-46B9-B688-AFC5C1BF7F63 - READ | DYNAMIC
    // READ_ANYBODY
    0x16, 0x00, 0x02, 0x03, 0x11, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x05, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Notify all connected devices, only when there is a change, one at the time.
    // Ideally it should be merged with the previous one, but don't know how to increase
    // the MTU for the notify package.
    // 0x0012 CHARACTERISTIC-4627C4A4-AC06-46B9-B688-AFC5C1BF7F63 - NOTIFY | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x12, 0x00, 0x03, 0x28, 0x10, 0x13, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x06, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0013 VALUE CHARACTERISTIC-4627C4A4-AC06-46B9-B688-AFC5C1BF7F63 - NOTIFY | DYNAMIC
    // 
    0x16, 0x00, 0x00, 0x03, 0x13, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x06, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0014 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x14, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // Mappings: Nintendo or Xbox: A,B,X,Y vs B,A,Y,X
    // 0x0015 CHARACTERISTIC-4627C4A4-AC07-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x15, 0x00, 0x03, 0x28, 0x0a, 0x16, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x07, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0016 VALUE CHARACTERISTIC-4627C4A4-AC07-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x16, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x07, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Whether to enable Allowlist in connections
    // 0x0017 CHARACTERISTIC-4627C4A4-AC08-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x17, 0x00, 0x03, 0x28, 0x0a, 0x18, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x08, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0018 VALUE CHARACTERISTIC-4627C4A4-AC08-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x18, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x08, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // List of addresses in the allowlist.
    // 0x0019 CHARACTERISTIC-4627C4A4-AC09-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x19, 0x00, 0x03, 0x28, 0x0a, 0x1a, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x09, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x001a VALUE CHARACTERISTIC-4627C4A4-AC09-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x1a, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x09, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Whether to enable Virtual Devices
    // 0x001b CHARACTERISTIC-4627C4A4-AC0A-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x1b, 0x00, 0x03, 0x28, 0x0a, 0x1c, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0a, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x001c VALUE CHARACTERISTIC-4627C4A4-AC0A-46B9-B688-AFC5C1BF7F63 - READ | WRITE | DYNAMIC
    // READ_ANYBODY, WRITE_ANYBODY
    0x16, 0x00, 0x0a, 0x03, 0x1c, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0a, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Disconnect a device
    // 0x001d CHARACTERISTIC-4627C4A4-AC0B-46B9-B688-AFC5C1BF7F63 - WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x1d, 0x00, 0x03, 0x28, 0x08, 0x1e, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0b, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x001e VALUE CHARACTERISTIC-4627C4A4-AC0B-46B9-B688-AFC5C1BF7F63 - WRITE | DYNAMIC
    // WRITE_ANYBODY
    0x16, 0x00, 0x08, 0x03, 0x1e, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0b, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // Delete stored Bluetooth bond keys
    // 0x001f CHARACTERISTIC-4627C4A4-AC0C-46B9-B688-AFC5C1BF7F63 - WRITE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x1f, 0x00, 0x03, 0x28, 0x08, 0x20, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0c, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // 0x0020 VALUE CHARACTERISTIC-4627C4A4-AC0C-46B9-B688-AFC5C1BF7F63 - WRITE | DYNAMIC
    // WRITE_ANYBODY
    0x16, 0x00, 0x08, 0x03, 0x20, 0x00, 0x63, 0x7f, 0xbf, 0xc1, 0xc5, 0xaf, 0x88, 0xb6, 0xb9, 0x46, 0x0c, 0xac, 0xa4, 0xc4, 0x27, 0x46, 
    // add Battery Service


    // #import <battery_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.battery_service
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.battery_service.xml
    // Battery Service 180F
    // 0x0021 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x21, 0x00, 0x00, 0x28, 0x0f, 0x18, 
    // 0x0022 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL - DYNAMIC | READ | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x22, 0x00, 0x03, 0x28, 0x12, 0x23, 0x00, 0x19, 0x2a, 
    // 0x0023 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL - DYNAMIC | READ | NOTIFY
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x23, 0x00, 0x19, 0x2a, 
    // 0x0024 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x24, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // #import <battery_service.gatt> -- END
    // add Device ID Service


    // #import <device_information_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.device_information
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.device_information.xml
    // Device Information 180A
    // 0x0025 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION
    0x0a, 0x00, 0x02, 0x00, 0x25, 0x00, 0x00, 0x28, 0x0a, 0x18, 
    // 0x0026 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x26, 0x00, 0x03, 0x28, 0x02, 0x27, 0x00, 0x29, 0x2a, 
    // 0x0027 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x27, 0x00, 0x29, 0x2a, 
    // 0x0028 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x28, 0x00, 0x03, 0x28, 0x02, 0x29, 0x00, 0x24, 0x2a, 
    // 0x0029 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x29, 0x00, 0x24, 0x2a, 
    // 0x002a CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x2a, 0x00, 0x03, 0x28, 0x02, 0x2b, 0x00, 0x25, 0x2a, 
    // 0x002b VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x2b, 0x00, 0x25, 0x2a, 
    // 0x002c CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x2c, 0x00, 0x03, 0x28, 0x02, 0x2d, 0x00, 0x27, 0x2a, 
    // 0x002d VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x2d, 0x00, 0x27, 0x2a, 
    // 0x002e CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x2e, 0x00, 0x03, 0x28, 0x02, 0x2f, 0x00, 0x26, 0x2a, 
    // 0x002f VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x2f, 0x00, 0x26, 0x2a, 
    // 0x0030 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x30, 0x00, 0x03, 0x28, 0x02, 0x31, 0x00, 0x28, 0x2a, 
    // 0x0031 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x31, 0x00, 0x28, 0x2a, 
    // 0x0032 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x32, 0x00, 0x03, 0x28, 0x02, 0x33, 0x00, 0x23, 0x2a, 
    // 0x0033 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x33, 0x00, 0x23, 0x2a, 
    // 0x0034 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x34, 0x00, 0x03, 0x28, 0x02, 0x35, 0x00, 0x2a, 0x2a, 
    // 0x0035 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x35, 0x00, 0x2a, 0x2a, 
    // 0x0036 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID - DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x36, 0x00, 0x03, 0x28, 0x02, 0x37, 0x00, 0x50, 0x2a, 
    // 0x0037 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID - DYNAMIC | READ
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x37, 0x00, 0x50, 0x2a, 
    // #import <device_information_service.gatt> -- END
    // END
    0x00, 0x00, 
}; // total size 546 bytes 


//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_GAP_SERVICE_01_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_01_END_HANDLE 0x0003
#define ATT_SERVICE_GATT_SERVICE_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_END_HANDLE 0x0006
#define ATT_SERVICE_GATT_SERVICE_01_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_01_END_HANDLE 0x0006
#define ATT_SERVICE_4627C4A4_AC00_46B9_B688_AFC5C1BF7F63_START_HANDLE 0x0007
#define ATT_SERVICE_4627C4A4_AC00_46B9_B688_AFC5C1BF7F63_END_HANDLE 0x0020
#define ATT_SERVICE_4627C4A4_AC00_46B9_B688_AFC5C1BF7F63_01_START_HANDLE 0x0007
#define ATT_SERVICE_4627C4A4_AC00_46B9_B688_AFC5C1BF7F63_01_END_HANDLE 0x0020
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_START_HANDLE 0x0021
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_END_HANDLE 0x0024
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_01_START_HANDLE 0x0021
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_01_END_HANDLE 0x0024
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_START_HANDLE 0x0025
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_END_HANDLE 0x0037
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_01_START_HANDLE 0x0025
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_01_END_HANDLE 0x0037

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_GATT_DATABASE_HASH_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_4627C4A4_AC01_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0009
#define ATT_CHARACTERISTIC_4627C4A4_AC02_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x000b
#define ATT_CHARACTERISTIC_4627C4A4_AC03_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x000d
#define ATT_CHARACTERISTIC_4627C4A4_AC04_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x000f
#define ATT_CHARACTERISTIC_4627C4A4_AC05_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0011
#define ATT_CHARACTERISTIC_4627C4A4_AC06_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0013
#define ATT_CHARACTERISTIC_4627C4A4_AC06_46B9_B688_AFC5C1BF7F63_01_CLIENT_CONFIGURATION_HANDLE 0x0014
#define ATT_CHARACTERISTIC_4627C4A4_AC07_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0016
#define ATT_CHARACTERISTIC_4627C4A4_AC08_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0018
#define ATT_CHARACTERISTIC_4627C4A4_AC09_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x001a
#define ATT_CHARACTERISTIC_4627C4A4_AC0A_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x001c
#define ATT_CHARACTERISTIC_4627C4A4_AC0B_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x001e
#define ATT_CHARACTERISTIC_4627C4A4_AC0C_46B9_B688_AFC5C1BF7F63_01_VALUE_HANDLE 0x0020
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL_01_VALUE_HANDLE 0x0023
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL_01_CLIENT_CONFIGURATION_HANDLE 0x0024
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING_01_VALUE_HANDLE 0x0027
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING_01_VALUE_HANDLE 0x0029
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING_01_VALUE_HANDLE 0x002b
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING_01_VALUE_HANDLE 0x002d
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING_01_VALUE_HANDLE 0x002f
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING_01_VALUE_HANDLE 0x0031
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID_01_VALUE_HANDLE 0x0033
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_01_VALUE_HANDLE 0x0035
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID_01_VALUE_HANDLE 0x0037