/**
 * @file    LedsBlinker.hpp.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define a basic blinker task.
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "LedsBase.hpp"

// HAL
#include "stm32h5xx_hal.h"

// RTOS
#include "tx_api.h"

// STD
#include <cstddef>

// ======================================================================
//                              CLASS
// ======================================================================

class LedsBlinker : public LedsBase {

  private:
    GPIO_TypeDef *port;
    uint16_t pin;

  protected:
    on_timer_tick(ULONG arg) override {
        LedsBlinker *ClassInstance = reinterpret_cast<LedsBlinker *>(arg);
        HAL_GPIO_TogglePin(ClassInstance->port, ClassInstance->pin);
        return;
    }

  public:
    LedsBlinker(TX_TIMER *timer, GPIO_TypeDef *port, uint16_t pin);
    LedsBlinker(
        TX_TIMER *timer, const char timer_name, GPIO_TypeDef *port, uint16_t pin) {
        // Init the base class
        LedsBase(timer);
        this->init_timer(&timer_name);

        // Copy the new values into our custom layer
        this->port = port;
        this->pin = pin;

        return;
    }
    ~LedsBlinker() {
        ~LedsBase();
        return;
    }
};

#ifdef __cplusplus
}
#endif