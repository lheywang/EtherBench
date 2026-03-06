/**
 * @file    app_usbx_status.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement changement handlers for USBX statuses.
 * @version 0.1
 * @date    2026-03-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_usbx_status.h"

// Local libraries
#define LOG_MODULE "USBX_STATUS"
#include "logger.h"

// USBX Core Headers
#include "tx_api.h"
#include "ux_api.h"
#include "ux_dcd_stm32.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_dpump.h"
#include "ux_device_class_storage.h"
#include "ux_device_stack.h"

// ThreadX
#include "tx_handler.h"

// Callbacks from the shell interface to the parser.
extern void usb_push_data(const uint8_t *data, const uint32_t len);
extern void usb_connect(UX_SLAVE_CLASS_CDC_ACM *cdc_instance);
extern void usb_disconnect();

// ======================================================================
//                              VARIABLES
// ======================================================================
// Flags
TX_EVENT_FLAGS_GROUP usbx_app_flags;

// Handles
UX_SLAVE_CLASS_CDC_ACM *usbx_terminal = UX_NULL;
UX_SLAVE_CLASS_CDC_ACM *usbx_bridge = UX_NULL;
UX_SLAVE_CLASS_DPUMP *usbx_cmsis = UX_NULL;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT USBD_ChangeFunction(ULONG Device_State) {
    UINT status = UX_SUCCESS;

    switch (Device_State) {
    case UX_DEVICE_ATTACHED:
        tx_event_flags_set(&usbx_app_flags, USBX_STATUS_ATTACHED, TX_OR);
        LOG("USBX Device attached");
        break;

    case UX_DEVICE_REMOVED:
        tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_ATTACHED, TX_AND);
        LOG("USBX Device removed");
        break;

    case UX_DCD_STM32_DEVICE_CONNECTED:
        tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CONNECTED, TX_OR);
        LOG("USBX Device connected");
        break;

    case UX_DCD_STM32_DEVICE_DISCONNECTED:
        tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_CONNECTED, TX_AND);
        LOG("USBX Device disconnected");
        break;

    case UX_DCD_STM32_DEVICE_SUSPENDED:
        tx_event_flags_set(&usbx_app_flags, USBX_STATUS_SUSPENDED, TX_OR);
        tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_RESUMED, TX_AND);
        LOG("USBX Device suspended");
        break;

    case UX_DCD_STM32_DEVICE_RESUMED:
        tx_event_flags_set(&usbx_app_flags, USBX_STATUS_RESUMED, TX_OR);
        tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_SUSPENDED, TX_AND);
        LOG("USBX Device resumed");
        break;

    case UX_DCD_STM32_SOF_RECEIVED:
        break;

    default:

        break;
    }

    return status;
}

/*
 * USB TERMINAL
 */
VOID USBX_TerminalDisable(VOID *cdc_instance) {

    // Set some flags
    usbx_terminal = (UX_SLAVE_CLASS_CDC_ACM *)cdc_instance;
    tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_CDC_TERMINAL_CONNECTED, TX_AND);

    // Call the disconnection function.
    usb_disconnect();

    LOG("USBX Disabled terminal");
    return;
}

VOID USBX_TerminalEnable(VOID *cdc_instance) {

    // Set some flags
    usbx_terminal = (UX_SLAVE_CLASS_CDC_ACM *)cdc_instance;
    tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CDC_TERMINAL_CONNECTED, TX_OR);

    // Call the connection function.
    usb_connect(usbx_terminal);
    LOG("USBX Enabled terminal");
    return;
}

VOID USBX_TerminalChange(VOID *cdc_instance) {

    // Nothing to be done here !
    tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CDC_TERMINAL_CHANGE_REQUIRED, TX_OR);
    LOG("USBX Changed terminal");
    return;
}

/*
 * USB-USART BRIDGE
 */
VOID USBX_USARTBridgeDisable(VOID *cdc_instance) {

    usbx_bridge = (UX_SLAVE_CLASS_CDC_ACM *)cdc_instance;
    tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_CDC_USB_USART_CONNECTED, TX_AND);
    LOG("USBX Disabled bridge");
    return;
}

VOID USBX_USARTBridgeEnable(VOID *cdc_instance) {

    usbx_bridge = (UX_SLAVE_CLASS_CDC_ACM *)cdc_instance;
    tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CDC_USB_USART_CONNECTED, TX_OR);
    LOG("USBX Enabled bridge");
    return;
}

VOID USBX_USARTBridgeChange(VOID *cdc_instance) {
    tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CDC_USB_USART_CHANGE_REQUIRED, TX_OR);
    LOG("USBX Changed bridge");
    return;
}

/*
 * CMSIS-DEBUGGER
 */
VOID USBX_CMSISDisable(VOID *cmsis_instance) {

    usbx_cmsis = (UX_SLAVE_CLASS_DPUMP *)cmsis_instance;
    tx_event_flags_set(&usbx_app_flags, ~USBX_STATUS_CMSIS_CONNECTED, TX_AND);
    LOG("USBX Disabled CMSIS");
    return;
}

VOID USBX_CMSISEnable(VOID *cmsis_instance) {

    usbx_cmsis = (UX_SLAVE_CLASS_DPUMP *)cmsis_instance;
    tx_event_flags_set(&usbx_app_flags, USBX_STATUS_CMSIS_CONNECTED, TX_OR);
    LOG("USBX Enabled CMSIS");
    return;
}