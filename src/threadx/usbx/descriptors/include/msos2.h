/**
 * @file    msos2.h
 * @author  leonard.heywang <leonard.heywang@proton.me>
 * @brief   Define the structs for the MS OS 2.0 descriptors, to enumerate different devices. For Windows only.
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
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                                ENUMS
// ======================================================================
enum MS_OS_20_SET_HEADER {MS_OS_20_SET_HEADER_DESCRIPTOR = 0x0000};
enum MS_OS_20_SUBSET_HEADER {MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x0001};
enum MS_OS_20_SUBSET_HEADER_FUNC {MS_OS_20_SUBSET_HEADER_FUNCTION = 0x0002};
enum MS_OS_20_FEATURE {MS_OS_20_FEATURE_COMPATBLE_ID = 0x0003};
enum MS_OS_20_FEATURE_REG {MS_OS_20_FEATURE_REG_PROPERTY = 0x0004};
enum MS_OS_20_REG {MS_OS_20_REG_MULTI_SZ = 0x0007};
enum MS_OS_20_WINDOWS_VERSION   {WINDOWS_8_1_VERSION = 0x06030000};
enum MS_OS_20_VENDOR_CODE    {MS_VENDOR_CODE = 0x01};

// ======================================================================
//                               STRUCTS
// ======================================================================

/*
 * BOS descriptors :
 */
typedef struct __attribute__((packed))
{
    uint8_t bLength;   
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumDeviceCaps;
} bos_header_t;

typedef struct __attribute__((packed))
{
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
    uint8_t  bConfigurationValue;
    uint8_t  bReserved;
    uint16_t wTotalLength;
} ms_os_20_subset_header_configuration_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t  bFirstInterfaceNumber;
    uint8_t  bReserved;
    uint16_t wSubsetLength;
} ms_os_20_subset_header_function_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t  CompatibleID[8];
    uint8_t  SubCompatibleID[8];
} ms_os_20_feature_compatible_id_t;

typedef struct __attribute__((packed)) {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint16_t wPropertyDataType;
    uint16_t wPropertyNameLength;
    uint8_t  PropertyName[42];
    uint16_t wPropertyDataLength;
    uint8_t  PropertyData[80]; 
} ms_os_20_feature_reg_property_t;

typedef struct __attribute__((packed)) {
    ms_os_20_set_header_t                  header;
    ms_os_20_subset_header_configuration_t config_subset;
    ms_os_20_subset_header_function_t      function_subset;
    ms_os_20_feature_compatible_id_t       compatible_id;
    ms_os_20_feature_reg_property_t        registry_property;
} ms_os_20_descriptor_set_t;

// ======================================================================
//                              VARIABLES
// ======================================================================
extern const ms_os_20_descriptor_set_t ms_os_20_descriptor;
extern const bos_descriptor_set_t bos_descriptor;

#ifdef __cplusplus
}
#endif