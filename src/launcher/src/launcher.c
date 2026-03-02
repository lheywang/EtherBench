/**
 * @file    launcher.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Source file for the global launcher. Create and get the memory
 * 			for the different tasks.
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
#include "launcher.h"

// Local libraries
#include "main.h"

// ThreadX library
#include "app_threadx.h"
#include "app_usbx_device.h"

// STD
#include <stdint.h>

#include "logger.h"
#include "task_leds.h"

// ======================================================================
//                              MEMORY AREAS
// ======================================================================
/*
 * Leds
 */
TX_THREAD leds_thread;
uint8_t leds_stack[IDLE_STACK_SIZE];

/*
 * Logger
 */
TX_THREAD logger_thread;
uint8_t logger_stack[LOGGER_STACK_SIZE];

// ======================================================================
//                              FUNCTIONS
// ======================================================================extern

uint32_t launcher(void) {

    /*
     * Launching the USBX task
     */
    MX_USBX_Device_Init();

    /*
     * Creating the idle task
     */
    tx_thread_create(&leds_thread, "Leds control", leds_task, 0, leds_stack, IDLE_STACK_SIZE, 31, 31, TX_NO_TIME_SLICE,
                     TX_AUTO_START);

    tx_thread_create(&logger_thread, "Deferred Logger", logger_task, 0, logger_stack, LOGGER_STACK_SIZE, 31, 31,
                     TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_sleep(20);

    LOG("Booted HAL, %d", HAL_OK);

    return 0;
}
