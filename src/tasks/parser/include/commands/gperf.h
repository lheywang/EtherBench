/**
 * @file    gperf.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   A small header to include the right files, as needed.
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*scpi_handler_t)(char *args, void *context);

struct scpi_command_entry {
    const char *name;
    scpi_handler_t handler;
};

struct shell_command_entry {
    const char *name;
    scpi_handler_t handler;
};

struct keywords_command_entry {
    const char *name;
    int id;
};

// Just a trick to ensure C++17 won't complain about that.
#define register

/*
 * Find commands functions
 */
const struct scpi_command_entry *
find_scpi_command(register const char *str, register size_t len);

const struct shell_command_entry *
find_shell_command(register const char *str, register size_t len);

const struct keywords_command_entry *
find_keywords_command(register const char *str, register size_t len);

#ifdef __cplusplus
}
#endif