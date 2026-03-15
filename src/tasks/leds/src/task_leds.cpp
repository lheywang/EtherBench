/**
 * @file    idle.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Source file for most simple task, a blinking led, to show
 * 			the system hasn't crashed (yet ?)
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "task_leds.h"

// Local libraries
#include "Leds/LedsBaseCommands.h"
#include "Leds/LedsBlinker.hpp"
#include "Leds/LedsWS2812.hpp"

// HAL
#include "init.h"
#include "main.h"
#include "stm32h5xx_hal.h"

// RTOS
#include "app_threadx.h"
#include "tx_api.h"

// ======================================================================
//                              EXTERNS
// ======================================================================
extern TIM_HandleTypeDef htim1;

// ======================================================================
//                              VARIABLES
// ======================================================================
// RTOS Parameters
TX_TIMER ring_timer;
TX_TIMER eth_green_timer;
TX_TIMER eth_yellow_timer;
TX_TIMER usb_blue_timer;
TX_TIMER usb_red_timer;
TX_TIMER flash_orange_timer;
TX_TIMER flash_green_timer;
TX_TIMER status_timer;

LedsWS2812 ring = LedsWS2812(&ring_timer, "RING LED TIMER", &htim1, 1, 250000);
LedsBlinker eth_green = LedsBlinker(&eth_green_timer, LED_GREEN_GPIO_Port, LED_GREEN_Pin);

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/*
 * TODO : Add the queue listener, and redirect the received commands to the correct
 * target.
 * This will call the correct instance of the classes, and which are just going to handle
 * correctly.
 * A standard blinker will be as any other protocol, but, in a way where on the init the
 * class would already be initialized with the correct value !
 */

void leds_task(ULONG arg) {
    TX_PARAMETER_NOT_USED(arg);

    Pixel a = {._raw = 0xFFFFFFFF};

    PixelEffect test = {
        .type = leds_effects::EFFECT_BREATHING,
        .primary = a,
        .secondary = a,
        .speed = 50,
        .width = 50,
        .progress = 50,
        .tick = 0};

    ring.set_effect(test);

    /*
     * That's just an infinite loop, which blink a led
     */
    while (1) {
        tx_thread_sleep(50);
        HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    }
}
