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
#include "task_parser.h"

// Local libraries
#include "commands/gperf.h"

// RTOS
#include "tx_api.h"

// ======================================================================
//                              VARIABLES
// ======================================================================

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void parser_task(ULONG arg) {
    TX_PARAMETER_NOT_USED(arg);

    int args = 2;
    int ctx = 2;

    /*
     * We're good !
     */
    struct scpi_command_entry *cmd = find_scpi_command("*cls", 4);
    int val = cmd->handler((char *)&args, (void *)&ctx);
    LOG("Got command : %d", val);

    cmd = find_scpi_command("*ese?", 5);
    val = cmd->handler((char *)&args, (void *)&ctx);
    LOG("Got command : %d", val);

    for (;;) {
        tx_thread_sleep(100);
    }
}
