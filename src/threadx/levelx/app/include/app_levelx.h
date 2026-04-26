/**
 * @file    app_levelx.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the basic set of commands for the levelx application.
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "ll_vfs.h"

// ThreadX
#include "tx_api.h"

// LevelX
#include "lx_api.h"

// ======================================================================
//                              VARIABLES
// ======================================================================
// Global instances
extern LX_NAND_FLASH NAND_settings;
extern LX_NAND_FLASH NAND_filex;
extern LX_NAND_FLASH NAND_backtrace;

// ======================================================================
//                              HELPER MACROS
// ======================================================================

/**
 * @brief Return how much uint8_t we shall allocate, depending on the pages sizes.
 *        8 bytes per pages are required, plus one byte per physical block.
 *
 */
#define GET_BUFFER_SIZE(block_count)                                                     \
    (LX_NAND_FLASH_SECTOR_MAPPING_CACHE_SIZE * 8 + block_count)

// ======================================================================
//                               DEFINES
// ======================================================================
/**
 * @brief Erase all blocks, to perform an hard reset
 * 
 */
// #define RESCUE_NAND

/**
 * @brief Reads some registers for debugging.
 * 
 */
// #define DEBUG_NAND

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief Perform the init of the levelX. Does not create any task.
 *
 * @param arg
 */
UINT app_levelx_thread_entry(ULONG arg);

/**
 * @brief Initialize the settings NAND area.
 *
 * @param nand
 * @return UINT
 */
UINT settings_init(LX_NAND_FLASH *nand);

/**
 * @brief Initialize the flash NAND area.
 *
 * @param nand
 * @return UINT
 */
UINT flash_init(LX_NAND_FLASH *nand);

/**
 * @brief Initialize the backtrace NAND area.
 *
 * @param nand
 * @return UINT
 */
UINT backtrace_init(LX_NAND_FLASH *nand);