/**
 * @file    vfs.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the low level VFS api, called from the syscalls.
 * @version 0.1
 * @date    2026-05-14
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "vfs.h"

// Local libraries

// ThreadX
#include "tx_api.h"

// FileX
#include "fx_api.h"

// LevelX
#include "lx_api.h"

// STD
#include <errno.h>
#include <stdarg.h>
#include <string.h>

// ======================================================================
//                              VARIABLES
// ======================================================================
// Mutexes, one for each access. Thus, combined access are permitted.
static TX_MUTEX vfs_sd_mutex;
static TX_MUTEX vfs_flash_mutex;
static TX_MUTEX vfs_mutex;

// VFS table
static VFS_FILE vfs_fd_table[MAX_VFS_CONCURRENT_FILES];

// ======================================================================
//                              EXTERNS
// ======================================================================
extern FX_MEDIA sdio_disk;
extern FX_MEDIA flash_disk;
extern LX_NAND_FLASH NAND_settings;
extern LX_NAND_FLASH NAND_backtrace;

// ======================================================================
//                           PRIVATE FUNCTIONS
// ======================================================================
/**
 * @brief Seek for an available file descriptor for openning.
 *        return the corresponding ID.
 *
 * @return UINT
 */
UINT _vfs_get_fd();

/**
 * @brief Return the correct mutex for the requested operation.
 *        Can be the mutex that target the SD or the FLASH.
 *
 * @param type[in] The VFS table type.
 *
 * @return TX_MUTEX*
 */
TX_MUTEX *_vfs_get_mutex(VFS_MOUNT_TYPE type);

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT vfs_init() {

    // Create the mutexes
    tx_mutex_create(&vfs_sd_mutex, "SD_MUTEX", TX_NO_INHERIT);
    tx_mutex_create(&vfs_flash_mutex, "FLASH_MUTEX", TX_NO_INHERIT);
    tx_mutex_create(&vfs_mutex, "GENERIC_MUTEX", TX_NO_INHERIT);

    // Empty the table
    memset(&vfs_fd_table, 0x00, sizeof(vfs_fd_table));

    // Return sucess
    return TX_SUCCESS;
}

UINT vfs_open(char *path, int flags, ...) {
    UINT status = TX_SUCCESS;
    /*
     * Wait for the mutex over our internal table...
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Check if we can fetch an new file descriptor
     */
    UINT fd = _vfs_get_fd();
    if (fd == -1) {
        status = ENFILE;
        goto release_table_mutex;
    }

    /*
     * todo: Parse the requested file, and, ask for openning..
     */

release_table_mutex:
    /*
     * Release the table mutex
     */
    tx_mutex_put(&vfs_mutex);
    return status;
}

UINT vfs_read(VFS_FILE *file, char *ptr, int len) {
    /*
     * Wait for the mutex over our internal table...
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Release the table mutex
     */
    tx_mutex_put(&vfs_mutex);
    return TX_SUCCESS;
}

UINT vfs_write(VFS_FILE *file, char *ptr, int len) {
    /*
     * Wait for the mutex over our internal table...
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Release the table mutex
     */
    tx_mutex_put(&vfs_mutex);
    return TX_SUCCESS;
}

UINT vfs_close(VFS_FILE *file) {
    /*
     * Wait for the mutex over our internal table...
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Release the table mutex
     */
    tx_mutex_put(&vfs_mutex);
    return TX_SUCCESS;
}

UINT vfs_seek(VFS_FILE *file, int size, int dir) {
    /*
     * Wait for the mutex over our internal table...
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Release the table mutex
     */
    tx_mutex_put(&vfs_mutex);
    return TX_SUCCESS;
}

// ======================================================================
//                           PRIVATE FUNCTIONS
// ======================================================================

UINT _vfs_get_fd() {
    for (int i = 0; i < MAX_VFS_CONCURRENT_FILES; i++) {
        if (vfs_fd_table[i].type == VFS_MOUNT_NONE) {
            return i;
        }
    }

    return -1;
}

TX_MUTEX *_vfs_get_mutex(VFS_MOUNT_TYPE type) {
    switch (type) {
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
    case VFS_MOUNT_FLASH:
        return &vfs_flash_mutex;
    case VFS_MOUNT_SD:
        return &vfs_sd_mutex;
    default:
    case VFS_MOUNT_NONE:
        return NULL;
    }
}
