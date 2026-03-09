/**
 * @file    ShellStreamBase.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the base ShellStream class, used for all of the other features.
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// STD
#include <cstddef>

// ======================================================================
//                              DEFINES
// ======================================================================
#define SHELL_LINE_LENGTH 128

// ======================================================================
//                              CLASS
// ======================================================================

class ShellStreamBase {
  private:
    char *line_buffer;
    size_t max_len;
    size_t current_len;
    const char *eol;
    bool echo_enabled;

    void build_request();

  protected:
    virtual void hw_transmit(const char *data, const size_t len) = 0;

  public:
    /*
     * Constructors
     */

    ShellStreamBase(
        char *static_buffer,
        size_t buffer_size,
        const char *eol = "\r\n",
        bool enable_echo = true);

    virtual ~ShellStreamBase() = default;

    /*
     * Stream API, to be available to others.
     */
    void transmit(const char c);
    void transmit(const char *c, const size_t len);
    void transmit(const char *str);

    /*
     * Reception API
     */
    void process(const char *c, const size_t len);
    void process(const char *str);
};