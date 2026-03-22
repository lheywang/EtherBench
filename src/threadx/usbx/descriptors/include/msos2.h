/**
 * @file    msos2.h
 * @author  leonard.heywang <leonard.heywang@proton.me>
 * @brief   Define the structs for the MS OS 2.0 descriptors, to enumerate different
 * devices. For Windows only.
 * @version 0.1
 * @date    2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "descriptor_config.h"

// STD
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                                ENUMS
// ======================================================================
enum MS_OS_20_CAPABILITY_CODE { PLATFORM = 0x05 };
enum MS_OS_20_REG { MS_OS_20_REG_MULTI_SZ = 0x0007 };
enum MS_OS_20_WINDOWS_VERSION { WINDOWS_8_1_VERSION = 0x06030000 };
enum MS_OS_20_VENDOR_CODE { MS_VENDOR_CODE = 0x01 };
enum MS_OS_20_RESERVED { RESERVED = 0x00 };

enum MS_OS_20_INDEX {
    MS_OS_20_DESCRIPTOR_INDEX = 0x07,
    MS_OS_20_SET_ALT_ENUMERATION = 0x08
};

enum MS_OS_20_DESCRIPTORS_TYPE {
    MS_OS_20_SET_HEADER_DESCRIPTOR = 0x00,
    MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x01,
    MS_OS_20_SUBSET_HEADER_FUNCTION = 0x02,
    MS_OS_20_FEATURE_COMPATBLE_ID = 0x03,
    MS_OS_20_FEATURE_REG_PROPERTY = 0x04,
    MS_OS_20_FEATURE_MIN_RESUME_TIME = 0x05,
    MS_OS_20_FEATURE_MODEL_ID = 0x06,
    MS_OS_20_FEATURE_CCGP_DEVICE = 0x07,
    MS_OS_20_FEATURE_VENDOR_REVISION = 0x08
};

enum MS_OS_20_PROPERTIES_LENGTH {
    MS_OS_20_PROPERTY_NAME_LENGTH = 42,
    MS_OS_20_PROPERTY_DATA_LENGTH = 80,
};

// ======================================================================
//                                DEFINES
// ======================================================================
#define MS_OS_20_PLATFORM_CAPABILITY_UUID                                                \
    {0xDF,                                                                               \
     0x60,                                                                               \
     0xDD,                                                                               \
     0xD8,                                                                               \
     0x89,                                                                               \
     0x45,                                                                               \
     0xC7,                                                                               \
     0x4C,                                                                               \
     0x9C,                                                                               \
     0xD2,                                                                               \
     0x65,                                                                               \
     0x9D,                                                                               \
     0x9E,                                                                               \
     0x64,                                                                               \
     0x8A,                                                                               \
     0x9F}

#define MS_OS_20_WINUSB_COMPATIBLE_ID {'W', 'I', 'N', 'U', 'S', 'B', 0, 0}

#define MS_OS_20_REGISTRY_PROPERTY_NAME                                                  \
    {'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, 'I', 0,                             \
     'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0, 'a', 0, 'c', 0,                             \
     'e', 0, 'G', 0, 'U', 0, 'I', 0, 'D', 0, 's', 0, 0,   0}

#define MS_OS_20_REGISTRY_PROPERTY_DATA                                                  \
    {'{', 0, 'C', 0, 'D', 0, 'B', 0, '3', 0, 'B', 0, '5', 0, 'A', 0, 'D', 0, '-', 0,     \
     '2', 0, '9', 0, '3', 0, 'B', 0, '-', 0, '4', 0, '6', 0, '6', 0, '3', 0, '-', 0,     \
     'A', 0, 'A', 0, '3', 0, '6', 0, '-', 0, '1', 0, 'A', 0, 'A', 0, 'E', 0, '4', 0,     \
     '6', 0, '4', 0, '6', 0, '3', 0, '7', 0, '7', 0, '6', 0, '}', 0, 0,   0, 0,   0}
// ======================================================================
//                               STRUCTS
// ======================================================================

/*
 * BOS descriptors :
 */
typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumDeviceCaps;
} bos_header_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDevCapabilityType;
    uint8_t bReserved;
    uint8_t PlatformCapabilityUUID[16];
    uint32_t dwWindowsVersion;
    uint16_t wMSOSDescriptorSetTotalLength;
    uint8_t bMS_VendorCode;
    uint8_t bAltEnumCode;
} bos_ms_20_descriptor_t;

typedef struct __attribute__((packed)) {
    bos_header_t header;
    bos_ms_20_descriptor_t ms_20_descriptor;
} bos_descriptor_set_t;

/*
 * MS OS 20 descriptors :
 */
typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint32_t dwWindowsVersion;
    uint16_t wTotalLength;
} ms_os_20_set_header_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t bConfigurationValue;
    uint8_t bReserved;
    uint16_t wTotalLength;
} ms_os_20_subset_header_configuration_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t bFirstInterfaceNumber;
    uint8_t bReserved;
    uint16_t wSubsetLength;
} ms_os_20_subset_header_function_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t CompatibleID[8];
    uint8_t SubCompatibleID[8];
} ms_os_20_feature_compatible_id_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint16_t wPropertyDataType;
    uint16_t wPropertyNameLength;
    uint8_t PropertyName[MS_OS_20_PROPERTY_NAME_LENGTH];
    uint16_t wPropertyDataLength;
    uint8_t PropertyData[MS_OS_20_PROPERTY_DATA_LENGTH];
} ms_os_20_feature_reg_property_t;

typedef struct __attribute__((packed)) {
    ms_os_20_set_header_t header;
    ms_os_20_subset_header_configuration_t config_subset;
    ms_os_20_subset_header_function_t function_subset;
    ms_os_20_feature_compatible_id_t compatible_id;
    ms_os_20_feature_reg_property_t registry_property;
} ms_os_20_descriptor_set_t;

// ======================================================================
//                              VARIABLES
// ======================================================================
extern const ms_os_20_descriptor_set_t ms_os_20_descriptor;
extern const bos_descriptor_set_t bos_descriptor;

#ifdef __cplusplus
}
#endif