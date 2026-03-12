/**
 * @file    LedsBlinker.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "Leds/LedsBlinker.hpp"

// Local libraries
#include "Leds/LedsBase.hpp"
#include "Leds/LedsBaseCommands.h"

// STD
#include <cstddef>

// HAL
#include "stm32h5xx_hal.h"

// RTOS
#include "tx_api.h"

// ======================================================================
//                              CLASS IMPL.
// ======================================================================

LedsBlinker::LedsBlinker(TX_TIMER *timer, GPIO_TypeDef *port, uint16_t pin)
    : LedsBase(timer) {
    this->init_timer("Blnk01");

    // Copy the new values into it our custom layer
    this->port = port;
    this->pin = pin;

    return;
}

LedsBlinker::LedsBlinker(
    TX_TIMER *timer, const char timer_name, GPIO_TypeDef *port, uint16_t pin)
    : LedsBase(timer) {

    this->init_timer(&timer_name);

    // Copy the new values into our custom layer
    this->port = port;
    this->pin = pin;

    return;
}

LedsBlinker::~LedsBlinker() {
    // Mother class is destructed automatically.
    return;
}

void LedsBlinker::on_timer_tick(ULONG arg) {
    LedsBlinker *ClassInstance = reinterpret_cast<LedsBlinker *>(arg);
    HAL_GPIO_TogglePin(ClassInstance->port, ClassInstance->pin);
    return;
}