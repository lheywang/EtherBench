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
#define LOG_MODULE "VFS"
#include "logger.h"

// ThreadX
#include "tx_api.h"

// FileX
#include "fx_api.h"

// LevelX
#include "lx_api.h"

// STD
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// ======================================================================
//                            PRIVATE DEFINES
// ======================================================================
// As the VFS table rely on path to be identified, let's just sum all the
// chars within the path to known that's going to be used.
#define SETTINGS_ID       "/settings/sector"
#define SETTINGS_ID_SIZE  (sizeof(SETTINGS_ID) - 1)
#define BACKTRACE_ID      "/backtrace/sector"
#define BACKTRACE_ID_SIZE (sizeof(BACKTRACE_ID) - 1)
#define SD_ID             "/sd/"
#define SD_ID_SIZE        (sizeof(SD_ID) - 1)
#define FLASH_ID          "/flash/"
#define FLASH_ID_SIZE     (sizeof(FLASH_ID) - 1)

// ======================================================================
//                              VARIABLES
// ======================================================================
// Mutexes, one for each access. Thus, combined access are permitted.
static TX_MUTEX vfs_sd_mutex;
static TX_MUTEX vfs_flash_mutex;
static TX_MUTEX vfs_mutex;

// VFS table
VFS_FILE vfs_fd_table[MAX_VFS_CONCURRENT_FILES];

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
 * @brief Return the correct mutex for the requested operation.
 *        Can be the mutex that target the SD or the FLASH.
 *
 * @param type[in] The VFS table type.
 *
 * @return TX_MUTEX*
 */
TX_MUTEX *_vfs_get_mutex(VFS_MOUNT_TYPE type);

/**
 * @brief Identify and build the convenient structure for the file.
 *
 * @param path  The target path.
 * @param relative_path_out The current pointer to the provided path.
 * @return VFS_FILE
 */
VFS_FILE _vfs_get_config(char *path, char **relative_path_out);

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

UINT vfs_open(VFS_FILE *file, char *path, int flags, ...) {
    UINT status = TX_SUCCESS;

    /*
     * Update the VFS table within our safe area.
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);
    char *relative_path = NULL;
    *file = _vfs_get_config(path, &relative_path);
    tx_mutex_put(&vfs_mutex);

    /*
     * Now, we can perform the IO operation as requested, within our safe area.
     */
    TX_MUTEX *hw_mutex = _vfs_get_mutex(file->type);
    if (hw_mutex == NULL) {
        errno = EIO;
        return TX_PTR_ERROR;
    }
    tx_mutex_get(hw_mutex, TX_WAIT_FOREVER);

    switch (file->type) {

        /*
         * File not openned.
         */
    case VFS_MOUNT_NONE:
        errno = EIO;
        status = TX_PTR_ERROR;
        break;

    /*
     * LevelX does not care about openning the file system, so, just return.
     */
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
        break;

    /*
     * FileX must handle the openning file.
     */
    case VFS_MOUNT_SD:
    case VFS_MOUNT_FLASH:
        status = fx_file_open(file->media_ptr, &file->backend.file, relative_path, flags);
        break;

    default:
        break;
    }
    tx_mutex_put(hw_mutex);

    return status;
}

UINT vfs_read(VFS_FILE *file, char *ptr, int len) {
    UINT status = TX_SUCCESS;

    /*
     * Now, we can perform the IO operation as requested, within our safe area.
     */
    TX_MUTEX *hw_mutex = _vfs_get_mutex(file->type);
    if (hw_mutex == NULL) {
        errno = EIO;
        return TX_PTR_ERROR;
    }
    tx_mutex_get(hw_mutex, TX_WAIT_FOREVER);

    switch (file->type) {

        /*
         * File not openned.
         */
    case VFS_MOUNT_NONE:
        errno = EIO;
        status = TX_PTR_ERROR;
        break;

    /*
     * LevelX does not care about openning the file system, so, just return.
     */
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
        status = lx_nand_flash_sector_read(file->flash_ptr, file->backend.sector, ptr);
        break;

    /*
     * FileX must handle the openning file.
     */
    case VFS_MOUNT_SD:
    case VFS_MOUNT_FLASH:
        ULONG read_len = 0;
        status = fx_file_read(&file->backend.file, ptr, len, &read_len);
        break;

    default:
        break;
    }

    tx_mutex_put(hw_mutex);
    return status;
}

UINT vfs_write(VFS_FILE *file, char *ptr, int len) {
    UINT status = TX_SUCCESS;

    /*
     * Now, we can perform the IO operation as requested, within our safe area.
     */
    TX_MUTEX *hw_mutex = _vfs_get_mutex(file->type);
    if (hw_mutex == NULL) {
        errno = EIO;
        return TX_PTR_ERROR;
    }
    tx_mutex_get(hw_mutex, TX_WAIT_FOREVER);

    switch (file->type) {

        /*
         * File not openned.
         */
    case VFS_MOUNT_NONE:
        errno = EIO;
        status = TX_PTR_ERROR;
        break;

    /*
     * LevelX does not care about openning the file system, so, just return.
     */
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
        status = lx_nand_flash_sector_write(file->flash_ptr, file->backend.sector, ptr);
        break;

    /*
     * FileX must handle the openning file.
     */
    case VFS_MOUNT_SD:
    case VFS_MOUNT_FLASH:
        status = fx_file_write(&file->backend.file, ptr, len);
        break;

    default:
        break;
    }

    tx_mutex_put(hw_mutex);
    return status;
}

UINT vfs_close(VFS_FILE *file) {
    UINT status = TX_SUCCESS;

    /*
     * Now, we can perform the IO operation as requested, within our safe area.
     */
    TX_MUTEX *hw_mutex = _vfs_get_mutex(file->type);
    if (hw_mutex == NULL) {
        errno = EIO;
        return TX_PTR_ERROR;
    }
    tx_mutex_get(hw_mutex, TX_WAIT_FOREVER);

    switch (file->type) {

        /*
         * File not openned.
         */
    case VFS_MOUNT_NONE:
        errno = EIO;
        status = TX_PTR_ERROR;
        break;

    /*
     * LevelX does not care about openning the file system, so, just return.
     */
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
        status = lx_nand_flash_sector_release(file->flash_ptr, file->backend.sector);
        break;

    /*
     * FileX must handle the openning file.
     */
    case VFS_MOUNT_SD:
    case VFS_MOUNT_FLASH:
        status = fx_file_close(&file->backend.file);
        break;

    default:
        break;
    }
    tx_mutex_put(hw_mutex);

    /*
     * Empty the VFS table within our safe area.
     */
    tx_mutex_get(&vfs_mutex, TX_WAIT_FOREVER);

    /*
     * Reset the union
     */
    switch (file->type) {
    case VFS_MOUNT_BACKTRACE:
    case VFS_MOUNT_SETTINGS:
        file->backend.sector = 0;
        break;
    case VFS_MOUNT_FLASH:
    case VFS_MOUNT_SD:
        memset(&file->backend.file, 0x00, sizeof(TX_FILE));
        break;
    default:
        break;
    }

    /*
     * Reset the other settings
     */
    file->type = VFS_MOUNT_NONE;
    file->flash_ptr = NULL;
    file->media_ptr = NULL;
    file->pos = 0;
    tx_mutex_put(&vfs_mutex);

    return status;
}

UINT vfs_seek(VFS_FILE *file, int size, int dir) {

    UINT status = TX_SUCCESS;
    ULONG offset = 0;

    TX_MUTEX *hw_mutex = _vfs_get_mutex(file->type);
    if (hw_mutex == NULL) {
        errno = EIO;
        return TX_PTR_ERROR;
    }
    tx_mutex_get(hw_mutex, TX_WAIT_FOREVER);

    switch (file->type) {
    case VFS_MOUNT_NONE:

    case VFS_MOUNT_SETTINGS:
    case VFS_MOUNT_BACKTRACE:
        /*
         * Operation is not supported.
         */
        status = ENOTSUP;
        break;

    case VFS_MOUNT_FLASH:
    case VFS_MOUNT_SD:
        /*
         * First, translate from the relative offset to the absolute one
         */
        switch (dir) {
        case SEEK_SET:
            offset = size;
            break;
        case SEEK_CUR:
            offset = file->backend.file.fx_file_current_file_offset + size;
            break;
        case SEEK_END:
            offset = file->backend.file.fx_file_current_file_size + size;
            break;
        default:
            status = EINVAL;
            break;
        }

        /*
         * Seek on the file
         */
        status = fx_file_seek(&file->backend.file, offset);

        break;
    }

    tx_mutex_put(hw_mutex);
    return status;
}

UINT vfs_get_fd() {
    for (int i = 0; i < MAX_VFS_CONCURRENT_FILES; i++) {
        if (vfs_fd_table[i].type == VFS_MOUNT_NONE) {
            return i;
        }
    }
    return -1;
}

// ======================================================================
//                           PRIVATE FUNCTIONS
// ======================================================================

TX_MUTEX *_vfs_get_mutex(VFS_MOUNT_TYPE type) {
    /*
     * Return the matching mutex for the correct type of mount.
     * Ensure we can perform two different types of IO, at the same time.
     */
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

VFS_FILE _vfs_get_config(char *path, char **relative_path_out) {
    /*
     * Load default values
     */
    VFS_FILE ret = {
        .type = VFS_MOUNT_NONE,
        .backend = {.file = {0}},
        .flash_ptr = NULL,
        .media_ptr = NULL,
        .pos = 0,
    };

    *relative_path_out = NULL;

    /*
     * Is the file path on the SD?
     */
    if (strncmp(path, SD_ID, SD_ID_SIZE) == 0) {
        ret.type = VFS_MOUNT_SD;
        ret.media_ptr = &sdio_disk;
        *relative_path_out = path + SD_ID_SIZE;
    }

    /*
     * Perhaps it's on the flash ?
     */
    else if (strncmp(path, FLASH_ID, FLASH_ID_SIZE) == 0) {
        ret.type = VFS_MOUNT_FLASH;
        ret.media_ptr = &flash_disk;
        *relative_path_out = path + FLASH_ID_SIZE;
    }

    /*
     * Or maybe on the settings partition ?
     */
    else if (strncmp(path, SETTINGS_ID, SETTINGS_ID_SIZE) == 0) {

        /*
         * Scan for the sector we'll access.
         */
        if (sscanf(path + SETTINGS_ID_SIZE, "%lu", &ret.backend.sector) == 1) {
            ret.type = VFS_MOUNT_SETTINGS;
            ret.flash_ptr = &NAND_settings;
        }
    }

    /*
     * Or, a backtrace ?
     */
    else if (strncmp(path, BACKTRACE_ID, BACKTRACE_ID_SIZE) == 0) {

        /*
         * Scan for the sector we'll access.
         */
        if (sscanf(path + BACKTRACE_ID_SIZE, "%lu", &ret.backend.sector) == 1) {
            ret.type = VFS_MOUNT_BACKTRACE;
            ret.flash_ptr = &NAND_backtrace;
        }
    }

    return ret;
}
