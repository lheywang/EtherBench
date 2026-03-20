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

// STD
#include <stdint.h>

/*
 * BOS Header descriptor, to declare the MS OS 2.0 capability to Windows.
 */
const bos_descriptor_set_t bos_descriptor = {
    .header = {
        .bLength            = sizeof(bos_header_t),
        .bDescriptorType    = 0x0F, // BOS
        .wTotalLength       = sizeof(bos_header_t) + sizeof(bos_ms_20_descriptor_t),
        .bNumDeviceCaps     = 1
    },
    .ms_20_descriptor = {
        .bLength                = sizeof(bos_ms_20_descriptor_t),
        .bDescriptorType        = 0x10, // Device Capability
        .bDevCapabilityType    = 0x05, // Platform
        .bReserved             = 0x00,
        .PlatformCapabilityUUID = {0xDF, 0x60, 0xDD, 0xD8, 0x89, 0x45, 0xC7, 0x4C, 0x9C, 0xD2, 0x65, 0x9D, 0x9E,    0x64, 0x8A, 0x9F},
        .dwWindowsVersion      = WINDOWS_8_1_VERSION,
        .wMSOSDescriptorSetTotalLength = sizeof(ms_os_20_descriptor_set_t), // Total length of the MS OS 2.0 descriptor set
        .bMS_VendorCode        = MS_VENDOR_CODE,
        .bAltEnumCode          = 0x00 // No alternate enumeration
    }
};

 /*
  * MS OS 20 Header
  */
/*
 * Here we just need to instantiate a global struct, defined as const.
 * And the magic will happen : No CPU load, just pure flash read.
 */
const ms_os_20_descriptor_set_t ms_os_20_descriptor = {

    .header = {
        .wLength          = sizeof(ms_os_20_set_header_t),
        .wDescriptorType  = MS_OS_20_SET_HEADER_DESCRIPTOR,
        .dwWindowsVersion = WINDOWS_8_1_VERSION,
        .wTotalLength     = sizeof(ms_os_20_descriptor_set_t)
    },
    .config_subset = {
        .wLength             = sizeof(ms_os_20_subset_header_configuration_t),
        .wDescriptorType     = MS_OS_20_SUBSET_HEADER_CONFIGURATION,
        .bConfigurationValue = 0x00,
        .bReserved           = 0x00,
        .wTotalLength        = sizeof(ms_os_20_descriptor_set_t) - sizeof(ms_os_20_set_header_t)
    },
    .function_subset = {
        .wLength               = sizeof(ms_os_20_subset_header_function_t),
        .wDescriptorType       = MS_OS_20_SUBSET_HEADER_FUNCTION,
        .bFirstInterfaceNumber = 0x01, // L'ID de votre interface DPUMP
        .bReserved             = 0x00,
        .wSubsetLength         = sizeof(ms_os_20_descriptor_set_t) - sizeof(ms_os_20_set_header_t) - sizeof(ms_os_20_subset_header_configuration_t)
    },
    .compatible_id = {
        .wLength         = sizeof(ms_os_20_feature_compatible_id_t),
        .wDescriptorType = MS_OS_20_FEATURE_COMPATBLE_ID,
        .CompatibleID    = {'W', 'I', 'N', 'U', 'S', 'B', 0, 0},
        .SubCompatibleID = {0}
    },
    .registry_property = {
        .wLength             = sizeof(ms_os_20_feature_reg_property_t),
        .wDescriptorType     = MS_OS_20_FEATURE_REG_PROPERTY,
        .wPropertyDataType   = MS_OS_20_REG_MULTI_SZ,
        .wPropertyNameLength = 42,
        .PropertyName        = {'D',0,'e',0,'v',0,'i',0,'c',0,'e',0,'I',0,'n',0,'t',0,'e',0,'r',0,'f',0,'a',0,'c',0,'e',0,'G',0,'U',0,'I',0,'D',0,'s',0,0,0},
        .wPropertyDataLength = 80,
        .PropertyData        = {'{',0,'C',0,'D',0,'B',0,'3',0,'B',0,'5',0,'A',0,'D',0,'-',0,'2',0,'9',0,'3',0,'B',0,'-',0,'4',0,'6',0,'6',0,'3',0,'-',0,'A',0,'A',0,'3',0,'6',0,'-',0,'1',0,'A',0,'A',0,'E',0,'4',0,'6',0,'4',0,'6',0,'3',0,'7',0,'7',0,'6',0,'}',0,0,0,0,0}
    }
};

