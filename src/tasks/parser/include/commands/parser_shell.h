/**
 * @file    parser_shell.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define standard shell commands
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDE
// ======================================================================
#include <stdint.h>

// ======================================================================
//                              FUNCTIONS
// ======================================================================

// Standard shell
int shell_cat(char *args, void *context);
int shell_cd(char *args, void *context);
int shell_clear(char *args, void *context);
int shell_file(char *args, void *context);
int shell_ls(char *args, void *context);
int shell_mkdir(char *args, void *context);
int shell_mv(char *args, void *context);
int shell_pwd(char *args, void *context);

// Custom functions
int shell_actions(char *args, void *context);
int shell_analog(char *args, void *context);
int shell_conf(char *args, void *context);
int shell_io(char *args, void *context);
int shell_log(char *args, void *context);
int shell_prog(char *args, void *context);
int shell_seq(char *args, void *context);
int shell_spy(char *args, void *context);

#ifdef __cplusplus
}
#endif