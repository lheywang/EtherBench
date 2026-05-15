/**
 * @file    vfs.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the elements of the VFS to be used over FileX/LevelX system.
 *          This file shall not be included as it, as the calls are routed over
 *          the standard library, thus, over _open, _write, and it's cousins.
 * @version 0.1
 * @date    2026-05-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries

// ThreadX
#include "tx_api.h"

// FileX
#include "fx_api.h"

// LevelX
#include "lx_api.h"

// STD
#include <stdarg.h>

// ======================================================================
//                              DEFINES
// ======================================================================
// Parameters
#define MAX_VFS_CONCURRENT_FILES 16 ///< Max number of files open in the same time.
#define VFS_FD_OFFSET 3 ///< The offset of the file descriptor. 3 is the first file, as 0-1-2 are STD reserved.

// File descriptors
#define VFS_FD_STDIN  0 ///< Standard POSIX STDIN value.
#define VFS_FD_STDOUT 1 ///< Standard POSIX STDOUT value.
#define VFS_FD_STDERR 2 ///< Standard POSIX STDOUT value.

// Standard configs
#define VFS_SETTINGS_USED_SECTOR 1 ///< Use the first sector for our config.

// ======================================================================
//                              ENUMS
// ======================================================================
/**
 * @brief   Define the types that can be assigned for a file. Used to track
 *          the permissions, and the mutex associates with all of them.
 */
typedef enum {
    VFS_MOUNT_NONE,
    VFS_MOUNT_SD,
    VFS_MOUNT_FLASH,
    VFS_MOUNT_SETTINGS,
    VFS_MOUNT_BACKTRACE,
} VFS_MOUNT_TYPE;

// ======================================================================
//                              STRUCTS
// ======================================================================
/**
 * @brief   Define how a file is handled in the RAM of the MCU.
 *
 */
typedef struct {
    VFS_MOUNT_TYPE type;

    union {
        FX_FILE file;
        ULONG sector;
    } backend;

    FX_MEDIA *media_ptr;
    LX_NAND_FLASH *flash_ptr;
    ULONG pos;
} VFS_FILE;

// ======================================================================
//                              VARIABLES
// ======================================================================
extern VFS_FILE vfs_fd_table[MAX_VFS_CONCURRENT_FILES];

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief Seek for an available file descriptor for openning.
 *        return the corresponding ID.
 *
 * @return UINT
 */
UINT vfs_get_fd();

/**
 * @brief Initialize the VFS subsystem. Must be called before any operation
 *        related to the later one are performed. Otherwise, crap data, such
 *        as unitialized data may be used, which will end up in a crash.
 *
 *        Called by the entry before any operation, so, shall be done.
 *
 * @return UINT
 */
UINT vfs_init();

/**
 * @brief Open a file on the right system, without any user operation.
 *
 * @warning For the raw accesses (/settings and /backtrace), only files where the
 *          name refer a sector (/settings/sector12) are valid. All others will
 *          return an error code.
 *
 * @param path[in]  The path to be openned.
 * @param flags[in] The options for the openning.
 * @param ...[in] The arguments to be passed additionnaly. Parsed, but unused.
 *
 * @return UINT
 */
UINT vfs_open(VFS_FILE *file, char *path, int flags, ...);

/**
 * @brief Read data from a file on the right system, without any user operation.
 *
 * @param file[in] The file to be read, as a *VFS object.
 * @param ptr[out] The data buffer that is passed to push the readback.
 * @param len[in] The number of bytes that must be read.
 *
 * @return UINT
 */
UINT vfs_read(VFS_FILE *file, char *ptr, int len);

/**
 * @brief Write data to a file, on the right system, without any user operation.
 *
 * @param file[in] The file to be wrote, as a *VFS object.
 * @param ptr[in] The data buffer that is passed for the write.
 * @param len[in] The number of bytes that must be read.
 *
 * @return UINT
 */
UINT vfs_write(VFS_FILE *file, char *ptr, int len);

/**
 * @brief Close an openned file, on the right logic system.
 *
 * @param file[in] The file to be closed, as a *VFS object.
 *
 * @return UINT
 */
UINT vfs_close(VFS_FILE *file);

/**
 * @brief Move the cursor on the file.
 *
 * @param file[in] The file to be searched, as a *VFS object.
 * @param size[in] The number of bytes to be moved.
 * @param dir[in] The direction of the seek operation.
 *
 * @return UINT
 */
UINT vfs_seek(VFS_FILE *file, int size, int dir);