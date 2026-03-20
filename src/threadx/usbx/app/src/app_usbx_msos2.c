/**
 * @file    app_usbx_msos2.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Application-specific implementation for MS OS 2.0 descriptor handling.
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
#include "app_usbx_msos2.h"

// Local library
#include "msos2.h"

// RTOS
#include "ux_api.h"
#include "ux_system.h"
#include "tx_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT bsp_usb_custom_request_handler(
    ULONG  request, 
    ULONG  request_value, 
    ULONG  request_index, 
    ULONG  request_length, 
    UCHAR* transfer_request_pointer, 
    ULONG* transfer_request_length_pointer
)
{
    // if (request == 0x06 && (request_value >> 8) == 0x0F) {
    //     ULONG length = sizeof(bos_descriptor);
    //     ULONG transfer_length = (request_length < length) ? request_length : length;
        
    //     memcpy(transfer_request_pointer, bos_descriptor, transfer_length);
    //     *transfer_request_length_pointer = transfer_length;
        
    //     return UX_SUCCESS;
    // }

    // if (request == MS_VENDOR_CODE && request_index == MS_OS_20_DESCRIPTOR_INDEX) {
    //     ULONG length = sizeof(ms_os_20_descriptor);
    //     ULONG transfer_length = (request_length < length) ? request_length : length;
        
    //     memcpy(transfer_request_pointer, ms_os_20_descriptor, transfer_length);
    //     *transfer_request_length_pointer = transfer_length;
        
    //     return UX_SUCCESS;
    // }

    /*
     * Unknown request. Let just stall here (won't hurt, the correct driver is already loaded).
     */
    return UX_ERROR;
}