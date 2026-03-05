/**
 * @file    tx_handler.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define a common TX_handler file.
 * @version 0.1
 * @date    2026-03-04
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "tx_api.h"

// STD
#include <stdint.h>

// ======================================================================
//                               ENUMS
// ======================================================================
/**
 * @brief These errors codes may help the user / dev to identiy was caused
 *        the code to end up on this function.
 *
 */
enum tx_error_codes {
    UNKNOWN_ERROR = 0x00000000,
    EBADF = 0x00001000,
    EBUSY = 0x00002000,
    USB_HW_CONFIG_FAILED = 0x0000A000,
    USB_HW_CANNOT_START = 0x0000A001,
    ETH_DHCP_FAILED = 0x0000B000,
    ETH_TELNET_FAILED = 0x0000B001
};

// ======================================================================
//                              FUNCTIONS
// ======================================================================
/**
 * @brief Define a common error handler, which is basically an infinite loop
 * with a toggling led.
 *
 * @return VOID
 */
VOID Tx_Error_Handler(uint32_t error_code); //