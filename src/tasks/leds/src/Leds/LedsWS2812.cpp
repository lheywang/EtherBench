/**
 * @file    LedsWS2812.cpp
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
#include "Leds/LedsWS2812.hpp"

// Local libraries
#include "Leds/LedsBase.hpp"
#include "Leds/LedsBaseCommands.h"

// HAL
#include "stm32h5xx_hal.h"

// STD
#include <cstddef>
#include <cstring>

// RTOS
#include "tx_api.h"

// ======================================================================
//                              CLASS IMPL.
// ======================================================================
LedsWS2812::LedsWS2812(TX_TIMER *timer, TIM_HandleTypeDef *htim, uint32_t TimerFreq)
    : LedsBase(timer) {

    // Finish base class init
    this->init_timer("RingLed01");

    // Copy new values
    this->htim = htim;
    this->init_hw_timer(TimerFreq);

    // Clear buffers
    memset(&this->leds_buffer, 0x00, sizeof(this->leds_buffer));
    memset(&this->pixel_buffer, 0x00, sizeof(this->pixel_buffer));

    return;
}

LedsWS2812::LedsWS2812(
    TX_TIMER *timer, const char timer_name, TIM_HandleTypeDef *htim, uint32_t TimerFreq)
    : LedsBase(timer) {

    // Finish base class init
    this->init_timer(&timer_name);

    // Copy new values
    this->htim = htim;
    this->init_hw_timer(TimerFreq);

    memset(&this->leds_buffer, 0x00, sizeof(this->leds_buffer));
    memset(&this->pixel_buffer, 0x00, sizeof(this->pixel_buffer));

    return;
}
LedsWS2812::~LedsWS2812() {
    this->stop_hw_timer();
    // Mother class is destructed automatically.
    return;
}

void LedsWS2812::on_timer_tick(ULONG arg) {
    LedsWS2812 *ClassInstance = reinterpret_cast<LedsWS2812 *>(arg);
    ClassInstance->refresh_leds();
    return;
}

void LedsWS2812::init_hw_timer(uint32_t freq_kHz) {

    // Get the period in ns.
    uint32_t period = (1000000 / freq_kHz);

    // Compute timer options
    this->Timer_Period = WS2812_BIT_NS / period;
    this->T0H = WS2812_T0H_NS / period;
    this->T1H = WS2812_T1H_NS / period;

    // Init the timer

    return;
}

void LedsWS2812::refresh_leds() {
    // Update to say : Hey, I've registerd that change !
    if (this->previous_effect != this->current_effect.type) {
        // perform clear here
    }
    this->previous_effect = this->current_effect.type;

    /*
     * Call the right update function
     */
    switch (this->current_effect.type) {

    case leds_effects::EFFECT_FLASH:
        this->effect_flash();
        break;

    case leds_effects::EFFECT_SOLID:
        this->effect_solid();
        break;

    case leds_effects::EFFECT_SPIN:
        this->effect_spin();
        break;

    case leds_effects::EFFECT_BREATHING:
        this->effect_breathing();
        break;

    case leds_effects::EFFECT_PROGRESS:
        this->effect_progress();
        break;

    case leds_effects::EFFECT_VU_METER:
        this->effect_vu_meter();
        break;

    case leds_effects::EFFECT_RAINBOW:
        this->effect_rainbow();
        break;

    case leds_effects::EFFECT_HEARTBEAT:
        this->effect_heartbeat();
        break;

    default:
        break;
    }
    return;
}

void LedsWS2812::set_effect(const PixelEffect new_effect) {

    // Check if we have something to do ...
    if (new_effect.type == this->previous_effect) {
        return;
    }

    // First, stop the timer (to never refresh while computing)
    this->stop_timer();

    /*
     * Copy the new parameters and for the refresh.
     * This will write to the leds
     */
    memcpy(&this->current_effect, &new_effect, sizeof(PixelEffect));
    this->refresh_leds();

    /*
     * Restart the timer with the new parameters
     */
    switch (this->current_effect.type) {

    case leds_effects::EFFECT_FLASH:
        this->start_timer(WS2812_FLASH_PERIOD_MS);
        break;

    case leds_effects::EFFECT_SPIN:
        this->start_timer(WS2812_SPIN_PERIOD_MS);
        break;

    case leds_effects::EFFECT_BREATHING:
        this->start_timer(WS2812_BREATHING_PERIOD_MS);
        break;
    case leds_effects::EFFECT_PROGRESS:
        this->start_timer(WS2812_PROGRESS_PERIOD_MS);
        break;

    case leds_effects::EFFECT_VU_METER:
        this->start_timer(WS2812_VU_METER_PERIOD_MS);
        break;

    case leds_effects::EFFECT_RAINBOW:
        this->start_timer(WS2812_RAINBOW_PERIOD_MS);
        break;

    case leds_effects::EFFECT_HEARTBEAT:
        this->start_timer(WS2812_HEARTBEAT_PERIOD_MS);
        break;

    default:
    case leds_effects::EFFECT_SOLID:
        break;
    }
    return;
}

void LedsWS2812::set_effect_progress(uint8_t progress) {

    if (progress < this->current_effect.progress) {
        return;
    }

    this->current_effect.progress = progress;
    return;
}

void LedsWS2812::stop_hw_timer() { return; }

void LedsWS2812::effect_flash() { return; }
void LedsWS2812::effect_solid() { return; }
void LedsWS2812::effect_spin() { return; }
void LedsWS2812::effect_breathing() { return; }
void LedsWS2812::effect_progress() { return; }
void LedsWS2812::effect_vu_meter() { return; }
void LedsWS2812::effect_rainbow() { return; }
void LedsWS2812::effect_heartbeat() { return; }
