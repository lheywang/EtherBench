/**
 * @file    ShellStreamCdc.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implementation of the ShellStreamCdc class.
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
// Header
#include "ShellStream/ShellStreamCdc.hpp"

// Local Libraries
#include "task_shell.h"

// RTOS
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"

// ======================================================================
//                            CLASS IMPL
// ======================================================================

void ShellStreamCdc::hw_transmit(const char *data, size_t length) {
    if (cdc_instance) {
        ULONG actual_length;
        ux_device_class_cdc_acm_write(
            this->cdc_instance, (UCHAR *)data, length, &actual_length);
    }
    return;
}

void ShellStreamCdc::connect(UX_SLAVE_CLASS_CDC_ACM *cdc) {
    // Update class settings
    this->cdc_instance = cdc;

    // Add the welcome message
    this->transmit(ShellWelcome);
    this->transmit(ShellNewLine);
    return;
}

void ShellStreamCdc::disconnect() {
    this->cdc_instance = nullptr;
    return;
}