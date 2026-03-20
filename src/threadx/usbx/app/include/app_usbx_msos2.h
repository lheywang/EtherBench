/**
 * @file    app_usbx_msos2.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Application-specific header for MS OS 2.0 descriptor handling.
 * @version 0.1
 * @date 2026-03-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local library
#include "msos2.h"

// RTOS
#include "ux_api.h"
#include "ux_system.h"
#include "tx_api.h"

#ifdef __cplusplus 
extern "C" {
#endif

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief Override a function to respond to MS_OS_20 requests, to ensure Windows will load
 * the classical WinUSB driver for our device, and won't complain. This is not needed under Linux, 
 * but it doesn't hurt either (request is never called).
 *
 * Shall be added as : _ux_system_slave->ux_system_slave_device.ux_slave_device_vendor_request_function = 
 *       bsp_usb_custom_request_handler;
 * 
 * @param request 
 * @param request_value 
 * @param request_index 
 * @param request_length 
 * @param transfer_request_pointer 
 * @param transfer_request_length_pointer 
 * @return UINT 
 */
UINT bsp_usb_custom_request_handler(
    ULONG  request, 
    ULONG  request_value, 
    ULONG  request_index, 
    ULONG  request_length, 
    UCHAR* transfer_request_pointer, 
    ULONG* transfer_request_length_pointer
);

#ifdef __cplusplus 
}
#endif