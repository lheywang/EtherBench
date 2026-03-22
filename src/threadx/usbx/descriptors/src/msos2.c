/**
 * @file    msos2.c
 * @author  leonard.heywang <leonard.heywang@proton.me>
 * @brief   Define the MS OS 2.0 descriptor methods.
 * @version 0.1
 * @date    2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "msos2.h"

// Local libraries
#include "descriptor_config.h"

// STD
#include <stdint.h>

/*
 * BOS Header descriptor, to declare the MS OS 2.0 capability to Windows.
 */
const bos_descriptor_set_t bos_descriptor = {
    .header =
        {
            .bLength = sizeof(bos_header_t),
            .bDescriptorType = 0x0F, // BOS
            .wTotalLength = sizeof(bos_header_t) + sizeof(bos_ms_20_descriptor_t),
            .bNumDeviceCaps = 1,
        },

    .ms_20_descriptor =
        {
            .bLength = sizeof(bos_ms_20_descriptor_t),
            .bDescriptorType = 0x10, // Device Capability
            .bDevCapabilityType = PLATFORM,
            .bReserved = RESERVED,
            .PlatformCapabilityUUID = MS_OS_20_PLATFORM_CAPABILITY_UUID,
            .dwWindowsVersion = WINDOWS_8_1_VERSION,
            .wMSOSDescriptorSetTotalLength = sizeof(ms_os_20_descriptor_set_t),
            .bMS_VendorCode = MS_VENDOR_CODE,
            .bAltEnumCode = 0x00, // No alternate enumeration
        },
};

/*
 * MS OS 20 Header
 */
/*
 * Here we just need to instantiate a global struct, defined as const.
 * And the magic will happen : No CPU load, just pure flash read.
 */
const ms_os_20_descriptor_set_t ms_os_20_descriptor = {

    .header =
        {
            .wLength = sizeof(ms_os_20_set_header_t),
            .wDescriptorType = MS_OS_20_SET_HEADER_DESCRIPTOR,
            .dwWindowsVersion = WINDOWS_8_1_VERSION,
            .wTotalLength = sizeof(ms_os_20_descriptor_set_t),
        },

    .config_subset =
        {
            .wLength = sizeof(ms_os_20_subset_header_configuration_t),
            .wDescriptorType = MS_OS_20_SUBSET_HEADER_CONFIGURATION,
            .bConfigurationValue = 0x00,
            .bReserved = RESERVED,
            .wTotalLength =
                sizeof(ms_os_20_descriptor_set_t) - sizeof(ms_os_20_set_header_t),
        },

    .function_subset =
        {
            .wLength = sizeof(ms_os_20_subset_header_function_t),
            .wDescriptorType = MS_OS_20_SUBSET_HEADER_FUNCTION,
            .bFirstInterfaceNumber = DEBUGGER_INTERFACE_0,
            .bReserved = RESERVED,
            .wSubsetLength = sizeof(ms_os_20_descriptor_set_t) -
                             sizeof(ms_os_20_set_header_t) -
                             sizeof(ms_os_20_subset_header_configuration_t),
        },

    .compatible_id =
        {
            .wLength = sizeof(ms_os_20_feature_compatible_id_t),
            .wDescriptorType = MS_OS_20_FEATURE_COMPATBLE_ID,
            .CompatibleID = MS_OS_20_WINUSB_COMPATIBLE_ID,
            .SubCompatibleID = {0},
        },

    .registry_property =
        {
            .wLength = sizeof(ms_os_20_feature_reg_property_t),
            .wDescriptorType = MS_OS_20_FEATURE_REG_PROPERTY,
            .wPropertyDataType = MS_OS_20_REG_MULTI_SZ,
            .wPropertyNameLength = MS_OS_20_PROPERTY_NAME_LENGTH,
            .PropertyName = MS_OS_20_REGISTRY_PROPERTY_NAME,
            .wPropertyDataLength = MS_OS_20_PROPERTY_DATA_LENGTH,
            .PropertyData = MS_OS_20_REGISTRY_PROPERTY_DATA,
        },
};
