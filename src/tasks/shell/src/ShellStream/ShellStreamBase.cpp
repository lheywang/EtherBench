/**
 * @file    ShellStreamBase.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the basic features of the ShellStreamBase class.
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
// Header
#include "ShellStream/ShellStreamBase.hpp"

// Local libraries
#include "task_shell.h"

// STD
#include <cstdint>
#include <cstring>

// RTOS
#include "tx_api.h"

// ======================================================================
//                              VARIABLES
// ======================================================================
extern TX_BLOCK_POOL parser_pool;
extern TX_QUEUE parser_input;

// ======================================================================
//                            CLASS IMPL
// ======================================================================

ShellStreamBase::ShellStreamBase(
    char *static_buffer, size_t buffer_size, const char *eol, bool enable_echo) {

    // Copy the base buffer address.
    this->line_buffer = static_buffer;

    // Copy the remaining data
    this->max_len = buffer_size;
    this->current_len = 0;

    this->eol = eol;
    this->echo_enabled = enable_echo;

    // Empty the current buffer
    memset(this->line_buffer, 0x00, this->max_len);
    return;
}

void ShellStreamBase::transmit(const char c) {
    this->hw_transmit(&c, 1);
    return;
}

void ShellStreamBase::transmit(const char *c, const size_t len) {
    this->hw_transmit(c, len);
    return;
}

void ShellStreamBase::transmit(const char *str) {
    this->hw_transmit(str, strlen(str));
    return;
}

void ShellStreamBase::process(const char *c, const size_t len) {

    if (c == nullptr || len == 0) {
        return;
    }

    for (int k = 0; k < (int)len; k += 1) {
        char ch = c[k];

        if (ch == '\r' || ch == '\n') {
            if (this->current_len == 0 && ch == '\n') {
                continue;
            }

            this->line_buffer[this->current_len] = '\0';

            // In case of newline, we don't transfer it. That's already handled by the
            // ShellNewLine !

            // Build the request
            this->build_request();
            this->current_len = 0;

            // Directly show the user that we're ready for the next one
            this->transmit(ShellNewLine);

            continue;
        }

        if (ch == '\b' || ch == 0x7F) {
            if (this->current_len > 0) {
                this->current_len -= 1;
                this->line_buffer[this->current_len] = '\0';

                if (this->echo_enabled) {
                    this->transmit("\b \b");
                }
            }
            continue;
        }

        if (ch >= 32 && ch <= 126) {

            if (this->current_len < (size_t)(SHELL_LINE_LENGTH - 1)) {

                this->line_buffer[this->current_len] = ch;
                this->current_len += 1;

                if (this->echo_enabled) {
                    char echo_char[2] = {ch, '\0'};
                    this->transmit(echo_char);
                }
            }
            continue;
        }
    }
}

void ShellStreamBase::process(const char *str) {
    // We don't required much more logic here.
    this->process(str, strlen(str));
    return;
}

void ShellStreamBase::build_request() {

    // Return if we just received an empty enter.
    if (this->current_len == 0) {
        return;
    }

    // Create our struc
    struct parserInput_t *response = nullptr;

    /*
     * First, get some memory to fill
     */
    UINT alloc_status = tx_block_allocate(&parser_pool, (VOID **)&response, TX_NO_WAIT);

    if (alloc_status != TX_SUCCESS) {
        if (this->echo_enabled) {
            this->transmit(
                "Could not transmit the command. Could not fetch enough memory.");
        }
        return;
    }

    /*
     * Build the response
     */
    response->reply_stream = this;
    strncpy(response->command, this->line_buffer, SHELL_LINE_LENGTH);

    // Ensure we won't go too far.
    response->command[SHELL_LINE_LENGTH - 1] = '\0';

    /*
     * Send this pointer to the queue
     */
    UINT send_status = tx_queue_send(&parser_input, &response, TX_NO_WAIT);
    if (send_status != TX_SUCCESS) {
        // Free the memory we allocated
        tx_block_release(response);

        // Eventually send a message
        if (this->echo_enabled) {
            this->transmit("Could not send the command to the parser. The FIFO is full.");
        }
        return;
    }

    return;
}
