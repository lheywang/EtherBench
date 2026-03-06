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

// STD
#include <cstdint>
#include <cstring>

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

void ShellStreamBase::process(const char c) {

    // First, check if we're out of limits
    if (this->current_len == (size_t)(SHELL_LINE_LENGTH - 1))
        return;

    // First, copy the caracter into the incomming buffer.
    this->line_buffer[this->current_len] = c;

    // Check for the end of line
    int eol_len = strlen(eol);
    if (strcmp(&this->line_buffer[this->current_len - eol_len], this->eol) != 0) {

        // Perhaps the user did wanted to supress a char ?
        if (c == '\b' || c == 0x7F) {
            this->line_buffer[this->current_len] = '\0';
            this->line_buffer -= 1;

            if (this->echo_enabled) {
                this->transmit('\b');
            }

            return;
        }

        // Or, did he sent a normal character ?
        if (c >= 32 && c <= 126) {
            if (this->current_len < (size_t)(SHELL_LINE_LENGTH - 1)) {
                this->current_len += 1;

                if (this->echo_enabled) {
                    this->transmit(c);
                }
            }

            return;
        }

        return;
    }

    /*
     * Build here the request to the parser input ! (As we detected an end of line !)
     */
    this->build_request();

    return;
}
void ShellStreamBase::process(const char *c, const size_t len) {
    // First, check if we're out of limits
    if (this->current_len == (size_t)(SHELL_LINE_LENGTH - 1))
        return;

    // Check if the user did send an end of line
    // Check for the end of line
    int eol_len = strlen(eol);
    if (strcmp(&c[len - eol_len], this->eol) != 0) {

        for (int k = 0; k < (int)len; k += 1) {
            // Perhaps the user did wanted to supress a char ?
            if (c[k] == '\b' || c[k] == 0x7F) {
                this->line_buffer[this->current_len] = '\0';
                this->line_buffer -= 1;

                if (this->echo_enabled) {
                    this->transmit('\b');
                }

                return;
            }

            // Or, did he sent a normal character ?
            if (c[k] >= 32 && c[k] <= 126) {
                if (this->current_len < (size_t)(SHELL_LINE_LENGTH - 1)) {
                    this->current_len += 1;

                    if (this->echo_enabled) {
                        this->transmit(c);
                    }
                }

                return;
            }
        }

        return;
    }

    /*
     * Build here the request to the parser input ! (As we detected an end of line !)
     */
    this->build_request();
}

void ShellStreamBase::process(const char *str) {
    // We don't required much more logic here.
    this->process(str, strlen(str));
    return;
}

void ShellStreamBase::build_request() { return; }
