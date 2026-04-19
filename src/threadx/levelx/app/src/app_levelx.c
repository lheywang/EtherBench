/**
 * @file    app_levelx.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the basic init of the level X system
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_levelx.h"

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
LX_NAND_FLASH NAND_settings;
LX_NAND_FLASH NAND_filex;
LX_NAND_FLASH NAND_backtrace;

static ULONG settings_cache[GET_BUFFER_SIZE(SETTINGS_PARTITION_SIZE) / sizeof(ULONG)];
static ULONG backtrace_cache[GET_BUFFER_SIZE(BACKTRACE_PARTITION_SIZE) / sizeof(ULONG)];
static ULONG filex_cache[GET_BUFFER_SIZE(FLASH_PARTITION_SIZE) / sizeof(ULONG)];

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT app_levelx_thread_entry(ULONG arg) {

    /*
     * Open the lx engine
     */
    lx_nand_flash_initialize();

    /*
     * Add the different partitions
     */
    UINT status = 0x00;
    status |= lx_nand_flash_open(
        &NAND_settings,
        "SETTINGS",
        settings_init,
        settings_cache,
        sizeof(settings_cache));

    status |= lx_nand_flash_open(
        &NAND_filex, "FILEX", flash_init, filex_cache, sizeof(filex_cache));

    status |= lx_nand_flash_open(
        &NAND_backtrace,
        "BACKTRACE",
        backtrace_init,
        backtrace_cache,
        sizeof(backtrace_cache));

    return status;
}

UINT settings_init(LX_NAND_FLASH *nand) {

    /*
     * Set the partitions parameters
     */
    nand->lx_nand_flash_total_blocks = SETTINGS_PARTITION_SIZE;
    nand->lx_nand_flash_words_per_page = (GD25_PAGE_SIZE / sizeof(ULONG));
    nand->lx_nand_flash_pages_per_block = GD25_BLOCK_PAGES;

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = settings_page_read;
    nand->lx_nand_flash_driver_write = settings_page_write;
    nand->lx_nand_flash_driver_block_erase = settings_block_erase;
    nand->lx_nand_flash_driver_block_erased_verify = settings_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = settings_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = settings_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = settings_block_status_set;

    return LX_SUCCESS;
}

UINT flash_init(LX_NAND_FLASH *nand) {

    /*
     * Set the partitions parameters
     */
    nand->lx_nand_flash_total_blocks = FLASH_PARTITION_SIZE;
    nand->lx_nand_flash_words_per_page = (GD25_PAGE_SIZE / sizeof(ULONG));
    nand->lx_nand_flash_pages_per_block = GD25_BLOCK_PAGES;

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = flash_page_read;
    nand->lx_nand_flash_driver_write = flash_page_write;
    nand->lx_nand_flash_driver_block_erase = flash_block_erase;
    nand->lx_nand_flash_driver_block_erased_verify = flash_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = flash_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = flash_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = flash_block_status_set;

    return LX_SUCCESS;
}

UINT backtrace_init(LX_NAND_FLASH *nand) {

    /*
     * Set the partitions parameters
     */
    nand->lx_nand_flash_total_blocks = BACKTRACE_PARTITION_SIZE;
    nand->lx_nand_flash_words_per_page = (GD25_PAGE_SIZE / sizeof(ULONG));
    nand->lx_nand_flash_pages_per_block = GD25_BLOCK_PAGES;

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = backtrace_page_read;
    nand->lx_nand_flash_driver_write = backtrace_page_write;
    nand->lx_nand_flash_driver_block_erase = backtrace_block_erase;
    nand->lx_nand_flash_driver_block_erased_verify = backtrace_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = backtrace_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = backtrace_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = backtrace_block_status_set;

    return LX_SUCCESS;
}