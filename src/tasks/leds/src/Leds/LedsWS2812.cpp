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

// LUT correction table
#include "gamma_lut.h"

// HAL
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_tim.h"

// STD
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <math.h>

// RTOS
#include "tx_api.h"
#include "tx_handler.h"

// ======================================================================
//                              EXTERNS
// ======================================================================

extern DCACHE_HandleTypeDef hdcache1;

// ======================================================================
//                              CONSTANTS
// ======================================================================

constexpr size_t HEARTBEAT_SAMPLES = 100;
constexpr std::array<uint8_t, HEARTBEAT_SAMPLES> generate_heartbeat_lut() {

    std::array<uint8_t, HEARTBEAT_SAMPLES> table{};

    for (size_t phase = 0; phase < HEARTBEAT_SAMPLES; phase += 1) {
        if (phase < 15) {
            table[phase] = (phase * 255) / 15;
        } else if (phase < 30) {
            table[phase] = 255 - ((phase - 15) * 255) / 15;
        }

        else if (phase >= 40 && phase < 50) {
            table[phase] = ((phase - 40) * 200) / 10;
        } else if (phase >= 50 && phase < 60) {
            table[phase] = 200 - ((phase - 50) * 200) / 10;
        }
    }

    return table;
}

constexpr auto heartbeat_lut = generate_heartbeat_lut();

// ======================================================================
//                              CLASS IMPL.
// ======================================================================
LedsWS2812::LedsWS2812(
    TX_TIMER *timer, TIM_HandleTypeDef *htim, uint32_t timer_channel, uint32_t TimerFreq)
    : LedsBase(timer) {

    // Finish base class init
    this->init_timer("RingLed01");

    // Copy new values
    this->htim = htim;
    this->timer_channel = timer_channel;
    this->timer_freq = TimerFreq;

    // Clear buffers
    memset(&this->leds_buffer, 0x00, sizeof(this->leds_buffer));
    memset(&this->pixel_buffer, 0x00, sizeof(this->pixel_buffer));

    return;
}

LedsWS2812::LedsWS2812(
    TX_TIMER *timer,
    const char *timer_name,
    TIM_HandleTypeDef *htim,
    uint32_t timer_channel,
    uint32_t TimerFreq)
    : LedsBase(timer) {

    // Finish base class init
    this->init_timer(timer_name);

    // Copy new values
    this->htim = htim;
    this->timer_channel = timer_channel;
    this->timer_freq = TimerFreq;

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

void LedsWS2812::init_hw_timer() {

    // Get the period in ns.
    uint32_t period = (1000000 / this->timer_freq);

    // Compute timer options
    this->T0H = WS2812_T0H_NS / period;
    this->T1H = WS2812_T1H_NS / period;

    // Basic timer init
    this->htim->Init.Prescaler = 0;
    this->htim->Init.CounterMode = TIM_COUNTERMODE_UP;

    this->htim->Init.Period = (WS2812_BIT_NS / period);

    this->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    this->htim->Init.RepetitionCounter = 0;

    this->htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_PWM_Init(this->htim) != HAL_OK) {
        Tx_Error_Handler(RING_FAIL_TIM_INIT);
    }

    TIM_OC_InitTypeDef sConfigOC;
    memset(&sConfigOC, 0x00, sizeof(sConfigOC));

    sConfigOC.OCMode = TIM_OCMODE_PWM1;

    sConfigOC.Pulse = 0;

    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCIDLESTATE_RESET;

    if (HAL_TIM_PWM_ConfigChannel(this->htim, &sConfigOC, this->timer_channel) !=
        HAL_OK) {
        Tx_Error_Handler(RING_FAIL_PWM_INIT);
    }

    return;
}

void LedsWS2812::stop_hw_timer() {

    // Stop any DMA :
    HAL_TIM_PWM_Stop_DMA(this->htim, this->timer_channel);

    return;
}

void LedsWS2812::refresh_leds() {
    // Update to say : Hey, I've registerd that change !
    if (this->previous_effect != this->current_effect.type) {
        this->current_effect.tick = 0;
        this->current_effect.progress = 0;
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

    // Update the leds
    this->compute_timer_cycles();
    this->send_buffer();
    return;
}

void LedsWS2812::compute_timer_cycles() {

    uint32_t dma_index = 0;

    // We fill the buffer, depending on the target value.
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        for (int bit = 23; bit < 0; bit -= 1) {
            this->leds_buffer[dma_index] =
                ((this->pixel_buffer[pixel]._raw >> bit) & 0x00000001) ? this->T1H
                                                                       : this->T0H;
        }
        dma_index += 1;
    }

    this->leds_buffer[dma_index] =
        0; // Force the last value to be 0 --> latch colors on the leds.

    return;
}

void LedsWS2812::send_buffer() {

    // Stop any current DMA transfers
    HAL_TIM_PWM_Stop_DMA(this->htim, this->timer_channel);

    // Flush the caches
    HAL_DCACHE_InvalidateByAddr(
        &hdcache1,
        reinterpret_cast<uint32_t *>(this->leds_buffer),
        sizeof(this->leds_buffer));

    // Trigger the next serie of DMA
    HAL_TIM_PWM_Start_DMA(
        this->htim,
        this->timer_channel,
        reinterpret_cast<uint32_t *>(this->leds_buffer),
        (sizeof(this->leds_buffer) / sizeof(this->leds_buffer[0])));

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

    // Trigger the refresh to update the status.
    this->refresh_leds();
    return;
}

void LedsWS2812::effect_flash() {

    // Swap the tick value between 0 and 1
    this->current_effect.tick = 1 - this->current_effect.tick;

    // Select the target colour
    Pixel temp = (this->current_effect.tick == 1) ? this->current_effect.primary
                                                  : this->current_effect.secondary;

    // Update the pixels
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        this->pixel_buffer[pixel] = this->apply_alpha(&temp, gamma_lut[temp.aRGB.alpha]);
    }

    return;
}
void LedsWS2812::effect_solid() {

    // Increment the tick counter (shall be useless anyway, timer is stopped)
    this->current_effect.tick += 1;

    // Update the pixels
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        this->pixel_buffer[pixel] = this->apply_alpha(
            &this->current_effect.primary,
            gamma_lut[this->current_effect.primary.aRGB.alpha]);
    }

    return;
}

void LedsWS2812::effect_breathing() {

    /*
     * This block will make a generate a ramp until LED_RING_BREATH_MAX is reached,
     * Then, a decreasing ramp for the same duration, and, finally, a 0 hold for some
     * cycles until LED_RING_BREATH_LENGTH is reached.
     */

    // Handle the tick counter update
    uint16_t local_tick = 0;
    this->current_effect.tick += 1;
    if (this->current_effect.tick <= LED_RING_BREATH_MAX) {
        local_tick = this->current_effect.tick;

    } else if (this->current_effect.tick <= (2 * LED_RING_BREATH_MAX)) {
        local_tick = (2 * LED_RING_BREATH_MAX) - this->current_effect.tick;

    } else if (this->current_effect.tick < LED_RING_BREATH_LENGTH) {
        local_tick = 0;

    } else {
        this->current_effect.tick = 0;
        local_tick = 0;
    }

    // Fetch the gamma for that value
    uint8_t Intensity = gamma_lut[(uint8_t)local_tick];

    // Apply to all pixels
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        this->pixel_buffer[pixel] =
            this->apply_alpha(&this->current_effect.primary, Intensity);
    }

    return;
}

void LedsWS2812::effect_spin() {

    // Handle the tick update
    if (this->current_effect.tick < LED_RING_PIXEL_NB) {
        this->current_effect.tick += 1;

    } else {
        this->current_effect.tick = 0;
    }

    // Compute the leds statuses
    uint8_t intensities[LED_RING_PIXEL_NB] = {0};
    for (int tail_pos = 0; tail_pos < this->current_effect.width; tail_pos += 1) {
        intensities[tail_pos] = gamma_lut
            [LED_CORR_MAXVAL - (tail_pos * LED_CORR_MAXVAL) / this->current_effect.width];
    }

    /*
     * Until now, the first index is the maximal level index, and the
     * this->current_effect.width is the first to be empty.
     *
     * This array does not take account for the real position !
     */

    // Apply the leds to the effects :
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {

        int8_t index = this->current_effect.tick - pixel;
        if (index < 0) {
            index = LED_RING_PIXEL_NB + index;
        }

        this->pixel_buffer[index] =
            this->apply_alpha(&this->current_effect.primary, intensities[index]);
    }

    return;
}

void LedsWS2812::effect_progress() {

    // No ticks are updates are needed here. This function is only called on progress
    // updates.

    uint32_t total_brightness = this->current_effect.progress * LED_RING_PIXEL_NB;

    // Compute the target alpha
    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        uint32_t pixel_start = pixel * LED_CORR_MAXVAL;

        /*
         * Select the intensity based on some
         */
        uint8_t intensity = 0;

        if (total_brightness > (pixel_start + LED_CORR_MAXVAL)) {
            intensity = LED_CORR_MAXVAL;
        } else if (total_brightness > pixel_start) {
            intensity = total_brightness - pixel_start;
        }

        // Apply the pixel value
        this->pixel_buffer[pixel] =
            this->apply_alpha(&this->current_effect.primary, gamma_lut[intensity]);
    }

    return;
}

void LedsWS2812::effect_vu_meter() {

    // No ticks are updates are needed here. This function is only called on progress
    // updates.

    uint32_t total_brightness = this->current_effect.progress * (LED_RING_PIXEL_NB / 2);

    // Compute the target alpha
    for (int pixel = 0; pixel < (LED_RING_PIXEL_NB / 2); pixel += 1) {
        uint32_t pixel_start = pixel * LED_CORR_MAXVAL;

        /*
         * Select the intensity based on some
         */
        uint8_t intensity = 0;

        if (total_brightness > (pixel_start + LED_CORR_MAXVAL)) {
            intensity = LED_CORR_MAXVAL;
        } else if (total_brightness > pixel_start) {
            intensity = total_brightness - pixel_start;
        }

        // Apply the pixel value
        this->pixel_buffer[(LED_RING_PIXEL_NB / 2) + pixel] =
            this->apply_alpha(&this->current_effect.primary, gamma_lut[intensity]);
        this->pixel_buffer[(LED_RING_PIXEL_NB / 2) - pixel] =
            this->apply_alpha(&this->current_effect.primary, gamma_lut[intensity]);
    }

    return;
}

void LedsWS2812::effect_rainbow() {

    // Get the offset to be applied
    uint8_t offset = (this->current_effect.tick * this->current_effect.speed) & 0xFF;

    // Increment the tick
    this->current_effect.tick += 1;

    // Reset the tick when we hit 0
    if (offset == 0) {
        this->current_effect.tick = 0;
    }

    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {

        uint8_t hue = (pixel * 256 / LED_RING_PIXEL_NB) + offset;

        Pixel color = this->current_effect.primary;
        hue = 255 - hue;

        if (hue < 85) {
            color.aRGB.r = 255 - (hue * 3);
            color.aRGB.g = 0;
            color.aRGB.b = (hue * 3);
        } else if (hue < 170) {
            color.aRGB.r = 0;
            color.aRGB.g = (hue * 3);
            color.aRGB.b = 255 - (hue * 3);
        } else {
            color.aRGB.r = (hue * 3);
            color.aRGB.g = 255 - (hue * 3);
            color.aRGB.b = 0;
        }

        this->pixel_buffer[pixel] =
            this->apply_alpha(&color, gamma_lut[color.aRGB.alpha]);
    }
    return;
}

void LedsWS2812::effect_heartbeat() {

    this->current_effect.tick += 1;
    if (this->current_effect.tick >= HEARTBEAT_SAMPLES) {
        this->current_effect.tick = 0;
    }

    uint8_t raw_intensity = heartbeat_lut[this->current_effect.tick];
    uint8_t intensity = gamma_lut[raw_intensity];

    for (int pixel = 0; pixel < LED_RING_PIXEL_NB; pixel += 1) {
        this->pixel_buffer[pixel] =
            this->apply_alpha(&this->current_effect.primary, intensity);
    }

    return;
}

inline Pixel LedsWS2812::apply_alpha(Pixel *input, uint8_t alpha) {

    /*
     * This value does perform an error : Rather than dividing by 255,
     * which is slow, we shift by 8 (divide by 256).
     * This induce a small error.
     */
    Pixel output;

    // Just checks to save useless CPU cycles.
    if (alpha == 0) {
        output.aRGB.r = 0;
        output.aRGB.g = 0;
        output.aRGB.b = 0;
    } else if (alpha == LED_CORR_MAXVAL) {
        output.aRGB.r = input->aRGB.r;
        output.aRGB.g = input->aRGB.g;
        output.aRGB.b = input->aRGB.b;
    } else {
        output.aRGB.r = (input->aRGB.r * alpha) >> 8;
        output.aRGB.g = (input->aRGB.g * alpha) >> 8;
        output.aRGB.b = (input->aRGB.b * alpha) >> 8;
    }

    return output;
}
