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
#include "../include/task_leds.h"
#include "app_threadx.h"
#include "main.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================
void leds_task(ULONG arg) {
    /*
     * That's just an infinite loop, which blink a led
     */
    while (1) {
        tx_thread_sleep(50);
        HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    }
}
