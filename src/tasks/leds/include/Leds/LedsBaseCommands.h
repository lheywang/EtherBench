/**
 * @file    LedsBaseCommands.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
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
#include <stdint.h>

// ======================================================================
//                              DEFINES
// ======================================================================
// Macros to configure the frequencies
#define LEDS_F_Hz(x) (x)
#define LEDS_F_kHz(x) (LEDS_F_Hz(x) * 1000)
#define LEDS_F_MHz(x) (LEDS_F_kHz(x) * 1000)

// Macros to configure the periods
#define LEDS_T_Hz(x) (1000 / LEDS_F_Hz(x))
#define LEDS_T_kHz(x) (1000 / LEDS_F_kHz(x))
#define LEDS_T_MHz(x) (1000 / LEDS_F_MHz(x))

// Leds specs (included here for C compatibility)
#define LED_RING_PIXEL_NB 10 // Will be 20 on the final version.
#define LED_RING_BIT_PER_PIXEL 24

// ======================================================================
//                              STRUCTS
// ======================================================================
union Pixel {
    uint32_t _raw;

    struct {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t alpha;
    } aRGB;
};

// ======================================================================
//                              ENUMS
// ======================================================================
enum leds_effects {
    EFFECT_FLASH,
    EFFECT_SOLID,
    EFFECT_SPIN,
    EFFECT_BREATHING,
    EFFECT_PROGRESS,
    EFFECT_VU_METER,
    EFFECT_RAINBOW,
    EFFECT_HEARTBEAT
};
enum leds_target {
    LED_RING,
    LED_ETH_GREEN,
    LED_ETH_YELLOW,
    LED_USB_BLUE,
    LED_USB_RED,
    LED_FLASH_ORANGE,
    LED_FLASH_GREEN,
    LED_STATUS
};

#ifdef __cplusplus
}
#endif
