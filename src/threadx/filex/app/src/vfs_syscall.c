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

// ======================================================================
//                               INCLUDES
// ======================================================================
// Local libraries
#define LOG_MODULE "SYSCALL"
#include "logger.h"
#include "vfs.h"

// ThreadX
#include "tx_api.h"

// STD
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>

// ======================================================================
//                              FUNCTIONS
// ======================================================================

int _open(char *path, int flags, ...) {

    /*
     * Check if we can fetch an new file descriptor. If not, exit.
     */
    UINT fd = vfs_get_fd();
    if (fd == -1) {
        return fd;
    }

    /*
     * Convert the flags
     */
    UINT fx_open_mode = FX_OPEN_FOR_READ;
    if ((flags & O_WRONLY) || (flags & O_RDWR)) {
        fx_open_mode = FX_OPEN_FOR_WRITE;
    }

    /*
     * Call the vfs helper
     */
    if (vfs_open(&vfs_fd_table[fd], path, fx_open_mode) != TX_SUCCESS)
        return -1;
    return fd;
}

int _read(int file, char *ptr, int len) {

    /*
     * Check for the validity of the file. If
     */
    if ((file == VFS_FD_STDIN) || (file == VFS_FD_STDERR) || (file == VFS_FD_STDOUT)) {
        LOG("Attempted unsupported operation (read) from STDIN-STDERR-STDOUT. Returning an empty string.");
        *ptr = '\0';
        return 1;
    }

    /*
     * Get the matching file descriptor, and ensuring that's correct
     */
    int fd = file - VFS_FD_OFFSET;
    if (fd > MAX_VFS_CONCURRENT_FILES - 1) {
        LOG("File %d is an invalid ID.", fd);
        errno = ENOENT;
        return -1;
    }
    if (vfs_fd_table[fd].type == VFS_MOUNT_NONE) {
        LOG("File %d is not openned.", fd);
        errno = ENOENT;
        return -1;
    }

    /*
     * Call the internal vfs files
     */
    if (vfs_read(&vfs_fd_table[fd], ptr, len) != TX_SUCCESS)
        return -1;
    return len;
}

int _write(int file, char *ptr, int len) {
    /*
     * Check for the validity of the file:
     */
    if ((file == VFS_FD_STDERR) || (file == VFS_FD_STDOUT)) {
        LOG("%.*s", len, ptr);
        return len;
    } else if (file == VFS_FD_STDIN) {
        LOG("Attempted unsupported operation (write) to STDIN. Returning an empty string.");
        return len;
    }

    /*
     * Get the matching file descriptor
     */
    int fd = file - VFS_FD_OFFSET;
    if (fd > MAX_VFS_CONCURRENT_FILES - 1) {
        LOG("File %d is an invalid ID.", fd);
        errno = ENOENT;
        return -1;
    }
    if (vfs_fd_table[fd].type == VFS_MOUNT_NONE) {
        LOG("File %d is not openned.", fd);
        errno = ENOENT;
        return -1;
    }

    /*
     * Call the internal vfs files
     */
    if (vfs_write(&vfs_fd_table[fd], ptr, len) != TX_SUCCESS)
        return -1;
    return len;
}

int _close(int file) {
    /*
     * Check for the validity of the file:
     */
    if ((file == VFS_FD_STDIN) || (file == VFS_FD_STDERR) || (file == VFS_FD_STDOUT)) {
        return 0;
    }

    /*
     * Get the matching file descriptor
     */
    int fd = file - VFS_FD_OFFSET;
    if (fd > MAX_VFS_CONCURRENT_FILES - 1) {
        LOG("File %d is an invalid ID.", fd);
        errno = ENOENT;
        return -1;
    }
    if (vfs_fd_table[fd].type == VFS_MOUNT_NONE) {
        LOG("File %d is not openned.", fd);
        errno = ENOENT;
        return -1;
    }

    /*
     * Call the internal vfs files
     */
    if (vfs_close(&vfs_fd_table[fd]) != TX_SUCCESS)
        return -1;
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    /*
     * Check for the validity of the file:
     */
    if ((file == VFS_FD_STDIN) || (file == VFS_FD_STDERR) || (file == VFS_FD_STDOUT)) {
        LOG("Attempted unsupported operation (seek) to STDIN/OUT/ERR. Operation ignored.");
        errno = ESPIPE;
        return -1;
    }

    /*
     * Get the matching file descriptor
     */
    int fd = file - VFS_FD_OFFSET;
    if (fd > MAX_VFS_CONCURRENT_FILES - 1) {
        LOG("File %d is an invalid ID.", fd);
        return ENOENT;
    }
    if (vfs_fd_table[fd].type == VFS_MOUNT_NONE) {
        LOG("File %d is not openned.", fd);
        return ENOENT;
    }

    /*
     * Call the internal vfs files
     */
    if (vfs_seek(&vfs_fd_table[fd], ptr, dir) != TX_SUCCESS)
        return -1;
    return 0;
}