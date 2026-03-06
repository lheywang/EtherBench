/**
 * @file    usb_bridge.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   C / C++ bridge for the NetXDuo stack.
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "bridge/usb_bridge.h"

// Class
#include "ShellStream/ShellStreamCdc.hpp"

// ======================================================================
//                              VARIABLES
// ======================================================================
static uint8_t usb_buffer[SHELL_LINE_LENGTH];

ShellStreamCdc usb_stream((char *)usb_buffer, sizeof(usb_buffer));

// ======================================================================
//                              FUNCTIONS
// ======================================================================

extern "C" void usb_push_data(const uint8_t *data, const uint32_t len) {
    // Check if data is OK.
    if (!data || len == 0)
        return;

    // Process the data.
    usb_stream.process((const char *)data, len);
    return;
}

extern "C" void usb_connect(UX_SLAVE_CLASS_CDC_ACM *cdc_instance) {
    usb_stream.connect(cdc_instance);
    return;
}
extern "C" void usb_disconnect() {
    usb_stream.disconnect();
    return;
}