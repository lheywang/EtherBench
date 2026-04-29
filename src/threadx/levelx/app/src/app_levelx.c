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
#define LOG_MODULE "NAND"

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_levelx.h"

// Local libraries
#include "ll_vfs.h"
#include "logger.h"

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

/**
 * @brief Try to open a volume. If a fail did occur, try for format it before reopenning.
 *        This enable the openning of FLASH volumes without issues, even if this is the
 * first time.
 *
 * @param volume A pointer to an LX_NAND_FLASH structure to be openned.
 * @param name The name that shall be applied to the volume.
 * @param funcptr The init driver function.
 * @param cache The cache to be used for that volume.
 * @param cache_size The cache size.
 *
 * @return UINT
 */
UINT open_levelx_nand_volume(LX_NAND_FLASH *volume,
                             char *name,
                             UINT (*funcptr)(LX_NAND_FLASH *),
                             ULONG *cache,
                             size_t cache_size);

UINT app_levelx_thread_entry(ULONG arg) {

    /*
     * Open the lx engine
     */
    lx_nand_flash_initialize();

    /*
     * Reset the flash (ensure default settings are loaded)
     */
    GD5F1GO4UBY1G_reset();

    /*
     * Debug : Read some registers
     */
#ifdef DEBUG_NAND
    UCHAR reg_A0 = GD5F1GO4UBY1G_Read_Register(0xA0);
    UCHAR reg_B0 = GD5F1GO4UBY1G_Read_Register(0xB0);
    UCHAR reg_C0 = GD5F1GO4UBY1G_Read_Register(0xC0);
    UCHAR reg_D0 = GD5F1GO4UBY1G_Read_Register(0xD0);
    UCHAR reg_F0 = GD5F1GO4UBY1G_Read_Register(0xF0);
    LOG("Registers (A0, B0, C0, D0, F0) = %x | %x | %x | %x | %x", reg_A0, reg_B0, reg_C0, reg_D0, reg_F0);
#endif

    /*
     * Disable the block protection to NONE.
     */
    GD5F1GO4UBY1G_set_protected_blocks(0x00);

    /*
     * Enable the QUAD SPI for maximal performance
     */
    GD5F1GO4UBY1G_enable_quad();

    /*
     * Debug : Read some registers
     */
#ifdef DEBUG_NAND
    reg_A0 = GD5F1GO4UBY1G_Read_Register(0xA0);
    reg_B0 = GD5F1GO4UBY1G_Read_Register(0xB0);
    reg_C0 = GD5F1GO4UBY1G_Read_Register(0xC0);
    reg_D0 = GD5F1GO4UBY1G_Read_Register(0xD0);
    reg_F0 = GD5F1GO4UBY1G_Read_Register(0xF0);
    LOG("Registers (A0, B0, C0, D0, F0) = %x | %x | %x | %x | %x", reg_A0, reg_B0, reg_C0, reg_D0, reg_F0);
#endif

    /*
     * If enable, reset the NAND to it's zero state. This shall not be enabled in prod, as
     * this will clear ALL bad blocks. Thus, writes loss ARE POSSIBLE.
     */
#ifdef RESCUE_NAND
#warning "[NAND] Rescue mode is enabled. Do not leave that in prod !!!"
    GD5F1GO4UBY1G_rescue();
#endif

    /*
     * Add the different partitions. If a fail occur, store the flag on a side,
     * clear it, and try to format the array.
     */
    /*
     * SETTINGS MEMORY
     */
    UINT status = 0x00;
    status |=
        open_levelx_nand_volume(&NAND_settings, "SETTINGS", &settings_init, settings_cache, sizeof(settings_cache));
    status |= open_levelx_nand_volume(&NAND_filex, "FILEX", &flash_init, filex_cache, sizeof(filex_cache));
    status |= open_levelx_nand_volume(
        &NAND_backtrace, "BACKTRACE", &backtrace_init, backtrace_cache, sizeof(backtrace_cache));

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
     * Configure the OOB channel
     */
    nand->lx_nand_flash_spare_data1_offset = 2;  // 2 bytes for the bad block marker
    nand->lx_nand_flash_spare_data1_length = 60; // 60 bytes for the LevelX spare buffer

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = settings_page_read;
    nand->lx_nand_flash_driver_write = settings_page_write;
    nand->lx_nand_flash_driver_pages_read = settings_pages_read;
    nand->lx_nand_flash_driver_pages_write = settings_pages_write;
    nand->lx_nand_flash_driver_pages_copy = settings_page_copy;
    nand->lx_nand_flash_driver_block_erase = settings_block_erase;

    nand->lx_nand_flash_driver_block_erased_verify = settings_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = settings_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = settings_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = settings_block_status_set;
    nand->lx_nand_flash_driver_extra_bytes_get = settings_extra_bytes_get;
    nand->lx_nand_flash_driver_extra_bytes_set = settings_extra_bytes_set;

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
     * Configure the OOB channel
     */
    nand->lx_nand_flash_spare_data1_offset = 2;  // 2 bytes for the bad block marker
    nand->lx_nand_flash_spare_data1_length = 60; // 60 bytes for the LevelX spare buffer

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = flash_page_read;
    nand->lx_nand_flash_driver_write = flash_page_write;
    nand->lx_nand_flash_driver_pages_read = flash_pages_read;
    nand->lx_nand_flash_driver_pages_write = flash_pages_write;
    nand->lx_nand_flash_driver_pages_copy = flash_page_copy;
    nand->lx_nand_flash_driver_block_erase = flash_block_erase;

    nand->lx_nand_flash_driver_block_erased_verify = flash_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = flash_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = flash_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = flash_block_status_set;
    nand->lx_nand_flash_driver_extra_bytes_get = flash_extra_bytes_get;
    nand->lx_nand_flash_driver_extra_bytes_set = flash_extra_bytes_set;

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
     * Configure the OOB channel
     */
    nand->lx_nand_flash_spare_data1_offset = 2;  // 2 bytes for the bad block marker
    nand->lx_nand_flash_spare_data1_length = 60; // 60 bytes for the LevelX spare buffer

    /*
     * Configure the callbacks
     */
    nand->lx_nand_flash_driver_read = backtrace_page_read;
    nand->lx_nand_flash_driver_write = backtrace_page_write;
    nand->lx_nand_flash_driver_pages_read = backtrace_pages_read;
    nand->lx_nand_flash_driver_pages_write = backtrace_pages_write;
    nand->lx_nand_flash_driver_pages_copy = backtrace_page_copy;
    nand->lx_nand_flash_driver_block_erase = backtrace_block_erase;

    nand->lx_nand_flash_driver_block_erased_verify = backtrace_block_erase_verify;
    nand->lx_nand_flash_driver_page_erased_verify = backtrace_page_erase_verify;
    nand->lx_nand_flash_driver_block_status_get = backtrace_block_status_get;
    nand->lx_nand_flash_driver_block_status_set = backtrace_block_status_set;
    nand->lx_nand_flash_driver_extra_bytes_get = backtrace_extra_bytes_get;
    nand->lx_nand_flash_driver_extra_bytes_set = backtrace_extra_bytes_set;

    return LX_SUCCESS;
}

UINT open_levelx_nand_volume(LX_NAND_FLASH *volume,
                             char *name,
                             UINT (*funcptr)(LX_NAND_FLASH *),
                             ULONG *cache,
                             size_t cache_size) {

    /*
     * First open try
     */
    UINT status = 0x00;
    status |= lx_nand_flash_open(volume, name, funcptr, cache, cache_size);

    /*
     * Check if the volume was openned. If not, let's try a format before retrying...
     */
    if (status) {
        LOG("Volume : %s failed to open. Trying a format ...", name);

        /*
         * Format attempt...
         */
        status = lx_nand_flash_format(volume, name, funcptr, cache, cache_size);

        if (status != LX_SUCCESS) {
            LOG("Volume : %s format failed. Volume may not be working correctly. Error code = 0x%x", name, status);
        } else {
            LOG("Volume : %s format suceeded. Trying a reopen now ...", name);
        }

        /*
         * Retry the openning procedure
         */
        status = lx_nand_flash_open(volume, name, funcptr, cache, cache_size);
    }

    if (status == LX_SUCCESS) {
        LOG("Volume : %s openned. Ready for IO operations.", name);
    } else {
        LOG("Volume : %s is NOT openned. Any IO operation will STALL. Stop code = 0x%x", name, status);
    }

    return status;
}