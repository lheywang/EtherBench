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

// ThreadX libraries
#include "app_netxduo.h"
#include "app_threadx.h"
#include "app_usbx_device.h"
#include "tx_api.h"

// Tasks
#include "logger.h"
#include "task_leds.h"
#include "task_parser.h"

// STD
#include <stdint.h>

// ======================================================================
//                              MEMORY AREAS
// ======================================================================
/*
 * Leds
 */
TX_THREAD leds_thread;
static __aligned(8) uint8_t leds_stack[IDLE_STACK_SIZE];

/*
 * Logger
 */
TX_THREAD logger_thread;
static __aligned(8) uint8_t logger_stack[LOGGER_STACK_SIZE];

/*
 * Parser
 */
TX_THREAD parser_thread;
static __aligned(8) uint8_t parser_stack[PARSER_STACK_SIZE];

/*
 * Semaphore
 */
TX_SEMAPHORE dma_trigger;
TX_SEMAPHORE dma_tx_done;

// ======================================================================
//                              FUNCTIONS
// ======================================================================extern

uint32_t launcher(void) {

    /*
     * Create semaphores
     */
    tx_semaphore_create(&dma_trigger, "dma trigger", 0);
    tx_semaphore_create(&dma_tx_done, "dma done", 0);

    /*
     * Creating the deferred logging task.
     * We do that first to ensure the messages WILL be deferred, when they could.
     */
    tx_thread_create(
        &logger_thread,
        "Deferred Logger",
        logger_task,
        0,
        logger_stack,
        LOGGER_STACK_SIZE,
        28,
        28,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    /*
     * Launching the USBX task
     */
    MX_USBX_Device_Init();

    /*
     * Launch the NetXDuo task
     */
    MX_NetXDuo_Init();

    /*
     * Creating the idle task
     */
    tx_thread_create(
        &parser_thread,
        "Parser",
        parser_task,
        0,
        parser_stack,
        PARSER_STACK_SIZE,
        20,
        20,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    /*
     * Creating the idle task
     */
    tx_thread_create(
        &leds_thread,
        "Leds control",
        leds_task,
        0,
        leds_stack,
        IDLE_STACK_SIZE,
        28,
        28,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    return 0;
}
