/**
 * @file    usb_bridge.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define a C / C++ friendly bridge for the USB stack
 * @version 0.1
 * @date 2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
#include <stddef.h>
#include <stdint.h>

// RTOS
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

extern "C" void usb_push_data(const uint8_t *data, const uint32_t len);
extern "C" void usb_connect(UX_SLAVE_CLASS_CDC_ACM *cdc_instance);
extern "C" void usb_disconnect();
