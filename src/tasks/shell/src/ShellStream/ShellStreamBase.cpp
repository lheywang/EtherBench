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

            if (this->echo_enabled) {
                this->transmit("\r\n");
            }

            this->build_request();
            
            this->current_len = 0; 
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
        // Protection contre le buffer overflow
        if (this->current_len < (size_t)(SHELL_LINE_LENGTH - 1)) {
            
            // CORRECTION : On stocke bien le caractère en RAM !
            this->line_buffer[this->current_len] = ch;
            this->current_len += 1;

            if (this->echo_enabled) {
                // On n'echo QUE ce caractère, pas tout le buffer 'c'
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

void ShellStreamBase::build_request() { return; }
