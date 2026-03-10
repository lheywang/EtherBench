/**
 * @file    ShellStreamConfig.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   C compatible file that parametrize the ShellStreamBase class.
 * @version 0.1
 * @date    2026-03-10
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              DEFINES
// ======================================================================
#define SHELL_LINE_LENGTH 128

#define SHELL_COMMAND_FIFO_DEPTH 5

// ======================================================================
//                              Structs
// ======================================================================
/**
 * @brief A nice small struct to transfer data between the shell classes and the
 *        the parser task.
 *
 */
struct parserInput_t {
    void *reply_stream;
    char command[SHELL_LINE_LENGTH];
};

// ======================================================================
//                              DEFINES (2)
// ======================================================================
#define SHELL_STRUCT_SIZE (sizeof(struct parserInput_t))

#define SHELL_POOL_TOTAL_SIZE                                                            \
    (SHELL_STRUCT_SIZE + sizeof(void *) * SHELL_COMMAND_FIFO_DEPTH)
