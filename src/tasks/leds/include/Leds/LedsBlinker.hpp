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
    void on_timer_tick(ULONG arg) override;

  public:
    LedsBlinker(TX_TIMER *timer, GPIO_TypeDef *port, uint16_t pin);
    LedsBlinker(
        TX_TIMER *timer, const char *timer_name, GPIO_TypeDef *port, uint16_t pin);
    ~LedsBlinker();
};

#ifdef __cplusplus
}
#endif