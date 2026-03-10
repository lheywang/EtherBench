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

#define LOG_MODULE "PARSER"
// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "task_parser.h"

// Local libraries
#include "ShellStream/ShellStreambase.hpp"
#include "commands/gperf.h"
#include "logger.h"

// RTOS
#include "tx_api.h"

// ======================================================================
//                              VARIABLES
// ======================================================================
extern TX_BLOCK_POOL parser_pool;
extern TX_QUEUE parser_input;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void parser_task(ULONG arg) {
    TX_PARAMETER_NOT_USED(arg);

    parserInput_t *cmd = nullptr;
    char response_buffer[SHELL_LINE_LENGTH];

    while (1) {
        // Fetch the next message on the queue
        tx_queue_receive(&parser_input, &cmd, TX_WAIT_FOREVER);
        if (cmd == nullptr)
            continue;

        // Parse it (not for now)
        LOG("Got command : %s", cmd->command);

        // Respond to it
        if (cmd->reply_stream == nullptr)
            continue;

        // TODO : Parse the command now !

        ShellStreamBase *stream = static_cast<ShellStreamBase *>(cmd->reply_stream);
        stream->transmit("Responded !");

        // Free the block we used
        tx_block_release(cmd);
    }
}
