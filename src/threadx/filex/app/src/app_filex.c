/**
 * @file    app_filex.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   The base fileX file.
 * @version 0.1
 * @date    2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

// Just a quick logger config
#define LOG_MODULE "FILEX_APP"
// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_filex.h"

// Libraries
#include "app_levelx.h"
#include "logger.h"

// Drivers
#include "fx_levelx_driver.h"

// ThreadX
#include "tx_api.h"
#include "tx_handler.h"

// FileX
#include "fx_api.h"
#include "fx_stm32_custom_driver.h"
#include "fx_stm32_sd_driver.h"

// LevelX
#include "lx_api.h"

// ======================================================================
//                              DEFINES
// ======================================================================

// Internal thread
TX_THREAD fx_app_thread;

// Temp memories
uint32_t
    __aligned(32) fx_sd_media_memory[FX_STM32_SD_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)];
uint8_t __aligned(32) fx_flash_media_memory[GD25_PAGE_SIZE];

// Thread memory
uint32_t __aligned(32) fx_stack[FX_APP_THREAD_STACK_SIZE];

// Disks
FX_MEDIA sdio_disk;
FX_MEDIA flash_disk;

// Sd card info
HAL_SD_CardInfoTypeDef *pCardInfoSD;

// Externs
extern SD_HandleTypeDef hsd1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================
void fx_app_thread_entry(ULONG thread_input);

/**
 * @brief  Application FileX Initialization.
 * @param memory_ptr: memory pointer
 * @retval int
 */
UINT MX_FileX_Init() {

    /*
     * Initialize both LevelX and FileX components
     */
    app_levelx_thread_entry(0x00);
    fx_system_initialize();

    /* Create the main thread.  */
    UINT ret;
    ret = tx_thread_create(
        &fx_app_thread,
        FX_APP_THREAD_NAME,
        fx_app_thread_entry,
        0,
        fx_stack,
        FX_APP_THREAD_STACK_SIZE,
        FX_APP_THREAD_PRIO,
        FX_APP_PREEMPTION_THRESHOLD,
        FX_APP_THREAD_TIME_SLICE,
        FX_APP_THREAD_AUTO_START);

    /* Check main thread creation */
    if (ret != FX_SUCCESS) {
        return TX_THREAD_ERROR;
    }

    return ret;
}

void fx_app_thread_entry(ULONG thread_input) {

    UINT sd_status = FX_SUCCESS;
    UINT flash_status = FX_SUCCESS;

    /*
     * Wait, if the SD hasn't booted yet...
     */
    tx_thread_sleep(25);

    /*
     * Ensure the card has the correct infos
     */
    HAL_SD_CardInfoTypeDef card_info;
    if (HAL_SD_GetCardInfo(&hsd1, &card_info) != HAL_OK) {
        LOG("Unable to read card infos.");
        Tx_Error_Handler(SD_HW_INIT_FAILED);
    }

    uint32_t block_count = card_info.BlockNbr;
    LOG("Detected SD card with %lu blocks.", block_count);
    if (block_count == 0) {
        Tx_Error_Handler(SD_HW_INIT_FAILED);
    }

    /*
     * First, try to open the SD card :
     */
    sd_status = fx_media_open(
        &sdio_disk,
        FX_SD_VOLUME_NAME,
        fx_stm32_sd_driver,
        (VOID *)FX_NULL,
        (VOID *)fx_sd_media_memory,
        sizeof(fx_sd_media_memory));

    /*
     * If it failed, format it as FAT32.
     */
    if (sd_status != FX_SUCCESS) {
        LOG("Failed to open the SD card. Will format it ...");
        sd_status = fx_media_format(
            &sdio_disk,                      // SD_Disk pointer
            fx_stm32_sd_driver,              // Driver entry
            (VOID *)FX_NULL,                 // Device info pointer
            (UCHAR *)fx_sd_media_memory,     // Media buffer pointer
            sizeof(fx_sd_media_memory),      // Media buffer size
            FX_SD_VOLUME_NAME,               // Volume Name
            FX_SD_NUMBER_OF_FATS,            // Number of FATs
            0,                               // Directory Entries
            FX_SD_HIDDEN_SECTORS,            // Hidden sectors
            block_count,                     // Total sectors
            FX_STM32_SD_DEFAULT_SECTOR_SIZE, // Sector size
            64,                              // Sectors per cluster
            1,                               // Heads
            1                                // Sectors per track
        );

        /* Check the format sd_status */
        if (sd_status != FX_SUCCESS) {
            LOG("Failed to format the SD card.");
            Tx_Error_Handler(SD_HW_FMT_FAILED);
        }

        /* Open the SD disk driver */
        sd_status = fx_media_open(
            &sdio_disk,
            FX_SD_VOLUME_NAME,
            fx_stm32_sd_driver,
            (VOID *)FX_NULL,
            (VOID *)fx_sd_media_memory,
            sizeof(fx_sd_media_memory));
    }

    /* Check the media open sd_status */
    if (sd_status != FX_SUCCESS) {
        LOG("SD was openneded");
    }

    /*
     * Then, try to open the Flash area
     */
    flash_status = fx_media_open(
        &flash_disk,
        "QSPI_NAND",
        fx_levelx_nand_driver,
        &NAND_filex,
        fx_flash_media_memory,
        sizeof(fx_flash_media_memory));

    /*
     * If failed, try to format it
     */
    if (flash_status != FX_SUCCESS) {

        ULONG total_logical_sectors = NAND_filex.lx_nand_flash_total_pages;
        flash_status = fx_media_format(
            &flash_disk,
            fx_levelx_nand_driver,
            &NAND_filex,
            fx_flash_media_memory,
            sizeof(fx_flash_media_memory),
            "QSPI_NAND",
            1,                     /* FAT count */
            256,                   /* Directory Entries */
            0,                     /* Hidden sectors */
            total_logical_sectors, /* Total Sectors */
            GD25_PAGE_SIZE,        /* Sector size */
            1,                     /* Sectors */
            1,                     /* Heads */
            1                      /* Sectors per track*/
        );

        if (flash_status == FX_SUCCESS) {
            flash_status = fx_media_open(
                &flash_disk,
                "QSPI_NAND",
                fx_levelx_nand_driver,
                &NAND_filex,
                fx_flash_media_memory,
                sizeof(fx_flash_media_memory));
        } else {
            Tx_Error_Handler(FLASH_HW_FMT_FAILED);
        }
    }

    while (1) {
        tx_thread_sleep(100);
    }
}
