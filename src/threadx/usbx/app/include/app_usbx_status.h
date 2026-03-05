/**
 * @file    app_usbx_status.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define status updates functions within the USBX stack.
 * @version 0.1
 * @date 2026-03-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                                INCLUDES
// ======================================================================
// RTOS
#include "tx_api.h"

// USBX
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_dpump.h"
#include "ux_device_class_storage.h"
#include "ux_device_stack.h"

// ======================================================================
//                                VARIABLES
// ======================================================================
// Flags
extern TX_EVENT_FLAGS_GROUP usbx_app_flags;

// Handles
extern UX_SLAVE_CLASS_CDC_ACM *usbx_terminal;
extern UX_SLAVE_CLASS_CDC_ACM *usbx_bridge;
extern UX_SLAVE_CLASS_DPUMP *usbx_cmsis;
// ======================================================================
//                                EVENTS
// ======================================================================

/**
 * @brief Define standard USBX flags, to be used accross the project.
 *
 * @warning
 *
 */
enum USBX_STATUS {
    // 8 LSB are reserved for the device status
    USBX_STATUS_ATTACHED = 0x00000001,
    USBX_STATUS_CONNECTED = 0x00000002,
    USBX_STATUS_SUSPENDED = 0x00000004,
    USBX_STATUS_RESUMED = 0x00000008,
    USBX_STATUS_SOF = 0x0000010,

    // Next 8 bits are reserved for the CDC devices (2x 4 bits).
    USBX_STATUS_CDC_TERMINAL_CONNECTED = 0x00000100,
    USBX_STATUS_CDC_TERMINAL_CHANGE_REQUIRED = 0x00000200,
    USBX_STATUS_CDC_TERMINAL_ERROR = 0x00000800,
    USBX_STATUS_CDC_USB_USART_CONNECTED = 0x00001000,
    USBX_STATUS_CDC_USB_USART_CHANGE_REQUIRED = 0x00002000,
    USBX_STATUS_CDC_USB_USART_ERROR = 0x00008000,

    // Next 8 bits are reserved for the MSC devices (2x 8 bits).
    USBX_STATUS_MSC_CONNECTED = 0x00010000,
    USBX_STATUS_MSC_ERROR = 0x00080000,

    // Last 8 (MSB) are reserved for the CMSIS-DAP debugger
    USBX_STATUS_CMSIS_CONNECTED = 0x01000000,
    USBX_STATUS_CMSIS_ERROR = 0x08000000
};

// ======================================================================
//                                FUNCTIONS
// ======================================================================

/**
 * @brief Callback called when the device change of state.
 *
 * @param   Device_State
 * @return  UINT
 */
UINT USBD_ChangeFunction(ULONG Device_State);

VOID USBX_TerminalDisable(VOID *cdc_instance);
VOID USBX_TerminalEnable(VOID *cdc_instance);
VOID USBX_TerminalChange(VOID *cdc_instance);

VOID USBX_USARTBridgeDisable(VOID *cdc_instance);
VOID USBX_USARTBridgeEnable(VOID *cdc_instance);
VOID USBX_USARTBridgeChange(VOID *cdc_instance);

VOID USBX_CMSISDisable(VOID *cmsis_instance);
VOID USBX_CMSISEnable(VOID *cmsis_instance);
