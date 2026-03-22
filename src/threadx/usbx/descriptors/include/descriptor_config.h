/**
 * @file    descriptor_config.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Store the values that are shared accross all descriptors.
 * @version 0.1
 * @date    2026-03-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                        VENDORS ID & SETTINGS
// ======================================================================
// Here we're using the ST ones, because the MCU is an ST one.
// Ensure to use the correct ones !
#define ST_VENDORID (0x0483)
#define ST_PRODUCTID (0xEB05)
#define DEVICE_ID (0x0105)

// Here, we're defining values about the strings.
// This can make sure the compiler will work for us, when needed !
#define STR_MANUFACTURER "EtherBench Labs"
#define STR_PRODUCT "EtherBench v1"
#define STR_SERIAL "EB-2026-0014"

// Here we define what the task manager show as device names :
#define STR_COM1 "EtherBench TERMINAL"
#define STR_COM2 "EtherBench USART"
#define STR_MSC1 "EtherBench FLASH"
#define STR_DBG1 "EtherBench CMSIS-DAP Debugger"

#define STR_MS_OS_10 "MSFT100\x01"

// ======================================================================
//                                ENUMS
// ======================================================================
enum USBX_INTERFACE_NUMBER {
    CDC_TERMINAL_INTERFACE_0 = 0x00,
    CDC_TERMINAL_INTERFACE_1 = 0x01,

    CDC_STREAM_INTERFACE_0 = 0x02,
    CDC_STREAM_INTERFACE_1 = 0x03,

    DEBUGGER_INTERFACE_0 = 0x04,
};
