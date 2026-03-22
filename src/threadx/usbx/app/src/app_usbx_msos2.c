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
#include "msos1.h"
#include "msos2.h"

#define LOG_MODULE "USBX_MSOS"
#include "logger.h"

// RTOS
#include "tx_api.h"
#include "ux_api.h"
#include "ux_system.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT bsp_usb_custom_request_handler(
    ULONG request,
    ULONG request_value,
    ULONG request_index,
    ULONG request_length,
    UCHAR *transfer_request_pointer,
    ULONG *transfer_request_length_pointer) {

    // request correspond à votre bMS_VendorCode (0x01)
    // request_index = 0x04 correspond à la demande d'Extended Compat ID (WinUSB)
    if (request == 0x01 && request_index == 0x0004) {
        ULONG length = sizeof(ms_os_10_descriptor);
        ULONG transfer_length = (request_length < length) ? request_length : length;

        memcpy(
            (void *)transfer_request_pointer,
            (const void *)&ms_os_10_descriptor,
            transfer_length);

        *transfer_request_length_pointer = transfer_length;
        return UX_SUCCESS;
    }

    // if (request == 0x06 && (request_value >> 8) == 0x0F) {

    //     LOG("Responded to a BOS descriptor request");

    //     ULONG length = sizeof(bos_descriptor);
    //     ULONG transfer_length = (request_length < length) ? request_length : length;

    //     memcpy(
    //         (void *)transfer_request_pointer,
    //         (const void *)&bos_descriptor,
    //         transfer_length);
    //     *transfer_request_length_pointer = transfer_length;

    //     return UX_SUCCESS;
    // }

    // if (request == MS_VENDOR_CODE && request_index == MS_OS_20_DESCRIPTOR_INDEX) {
    //     ULONG length = sizeof(ms_os_20_descriptor);
    //     ULONG transfer_length = (request_length < length) ? request_length : length;

    //     LOG("Responded to an MS_OS_20 descriptor request");

    //     memcpy(
    //         (void *)transfer_request_pointer,
    //         (const void *)&ms_os_20_descriptor,
    //         transfer_length);
    //     *transfer_request_length_pointer = transfer_length;

    //     return UX_SUCCESS;
    // }

    /*
     * Unknown request. Let just stall here (won't hurt, the correct driver is already
     * loaded).
     */
    return UX_ERROR;
}
