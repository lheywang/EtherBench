/**
 * @file    vfs_syscall.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement an override of the STD functions, to reroute the
 *          standard prints to the rights elements.
 * @version 0.1
 * @date    2026-05-14
 *
 * @copyright Copyright (c) 2026
 *
 */
// Just a quick logger config
#define LOG_MODULE "FILE_SYSCALLS"

// ======================================================================
//                               INCLUDES
// ======================================================================
// Local libraries
#include "logger.h"
#include "vfs.h"

// ThreadX
#include "tx_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

int _open(char *path, int flags, ...) {
    (void)path;
    (void)flags;
    /* Pretend like we always fail */
    return -1;
}

int _read(int file, char *ptr, int len) {
    (void)file;
    return len;
}

int _write(int file, char *ptr, int len) {
    (void)file;
    return len;
}

int _close(int file) {
    (void)file;
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}