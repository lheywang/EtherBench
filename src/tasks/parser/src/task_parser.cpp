/**
 * @file    task_logger.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement a logger module, which handle a fast,
 * 			DMA based IO, from high level functions.
 *
 * @version 0.1
 * @date    2026-03-01
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "logger.h"

// Local library
#include "app_threadx.h"
#include "main.h"
#include "stm32h5xx_hal_uart.h"
#include "tx_api.h"

// STD
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// ======================================================================
//                              VARIABLES
// ======================================================================

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void parser_task(ULONG arg) {
    TX_PARAMETER_NOT_USED(arg);

    for (;;) {
        tx_thread_sleep(100);
    }
}
