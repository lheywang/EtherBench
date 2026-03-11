/**
 * @file    LedsWs2812.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define a basic WS2812 controller class.
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "LedsBase.hpp"

// HAL
#include "stm32h5xx_hal_tim_ex.h"

// STD
#include <cstddef>
#include <cstdint>

// ======================================================================
//                              CLASS
// ======================================================================

class LedsWS2812 : public LedsBase {

  private:
    uint16_t leds_buffer[LED_RING_BIT_PER_PIXEL * LED_RING_PIXEL_NB];
    // timer instance here
};