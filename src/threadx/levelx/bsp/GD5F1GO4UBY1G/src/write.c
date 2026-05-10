/**
 * @file    write.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the write features of the GD5F1GO4UBY1G flash.
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
#include "GD5F1GO4UBY1G.h"

// Local libraries
#include "commands.h"

// HAL
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_dcache.h"
#include "stm32h5xx_hal_dma.h"
#include "stm32h5xx_hal_dma_ex.h"
#include "stm32h5xx_hal_xspi.h"

// LevelX
#include "lx_api.h"

// ThreadX
#define LOG_MODULE "NAND_WRITE"
#include "logger.h"
#include "tx_api.h"

// STD
#include <string.h>

// Extern
extern XSPI_HandleTypeDef hospi1;                 // From HAL
extern DCACHE_HandleTypeDef hdcache1;             // From HAL
extern DMA_QListTypeDef dma_xfer_tx;              // from common.c
extern DMA_HandleTypeDef handle_GPDMA1_octospiTX; // from hal/init/octospi.c
extern DMA_HandleTypeDef handle_GPDMA1_octospiRX; // from hal/init/octospi.c

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_generic_write(ULONG block,
                                 ULONG page,
                                 UCHAR *main_buffer,
                                 ULONG main_size,
                                 UCHAR *spare_buffer,
                                 ULONG spare_size,
                                 ULONG spare_offset) {

    /*
     * First, transfer the target page into the cache register
     */
    ULONG xfer_size = ((main_buffer) ? main_size : 0) + ((spare_buffer) ? spare_size : 0);

    XSPI_RegularCmdTypeDef cmd = {0};
    uint32_t row_addr = (block * GD25_BLOCK_PAGES) + page;

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_PROGRAM_LOAD_X4;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_4_LINES;
    cmd.DummyCycles = 0;
    cmd.DataLength = xfer_size;
    cmd.Address = (main_buffer != NULL) ? 0 : (GD25_PAGE_OOD_ADDR + spare_offset);

    /*
     * Build the new buffer
     */
    memset((void *)buffer, 0xFF, sizeof(buffer));
    if (main_buffer) {
        memcpy((uint8_t *)buffer, main_buffer, main_size);
    }
    if (spare_buffer) {
        memcpy((uint8_t *)buffer + main_size + spare_offset, spare_buffer, spare_size);
    }

    /*
     * Wait for the memory IO to finish
     */
    HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)buffer, sizeof(buffer));
    __DSB();

    /*
     * Launch the transfer if we need more than the DMA threshold
     */

    if (xfer_size > GD25_DMA_THRESHOLD) {

        /*
         * Clean the semaphore, to ensure we restart from 0.
         */
        while (tx_semaphore_get(&flash_dma_done, TX_NO_WAIT) == TX_SUCCESS)
            ;

        /*
         * Start the transfer
         */
        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;
        if (HAL_XSPI_Transmit_DMA(&hospi1, (uint8_t *)buffer) != HAL_OK)
            return LX_ERROR;

        /*
         * Wait for the transfer to finish, and then, exit. We poll for the last bytes, should not be long.
         */
        if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
            return LX_ERROR;

    } else {

        /*
         * Transfer from the local buffer
         */
        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;
        if (HAL_XSPI_Transmit(&hospi1, (uint8_t *)buffer, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;
    }

    /*
     * Then, enable the write operation
     */
    if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Ask the NAND to write the data into the array
     */
    cmd.Instruction = GD25_PROGRAM_EXECUTE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    cmd.Address = row_addr;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DataLength = 0;
    cmd.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    /*
     * Wait for finish before exiting.
     */
    return GD5F1GO4UBY1G_wait_for_complete();
}

UINT GD5F1GO4UBY1G_page_write(ULONG block, ULONG page, ULONG *source, ULONG words) {
    return GD5F1GO4UBY1G_generic_write(
        block, page, (UCHAR *)source, words * (sizeof(ULONG) / sizeof(UCHAR)), NULL, 0, 0);
}

UINT GD5F1GO4UBY1G_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size) {
    return GD5F1GO4UBY1G_generic_write(block, page, NULL, 0, source, size, 0);
}

UINT GD5F1GO4UBY1G_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages) {

    UINT status = LX_SUCCESS;
    UCHAR *src = main_buffer;
    UCHAR *spare = spare_buffer;

    for (ULONG i = 0; i < pages; i++) {

        ULONG current_main_size = (main_buffer != NULL) ? GD25_PAGE_SIZE : 0;
        ULONG current_spare_size = (spare_buffer != NULL) ? GD25_PAGE_OOB : 0;

        status = GD5F1GO4UBY1G_generic_write(block, page + i, src, current_main_size, spare, current_spare_size, 0);
        if (status != LX_SUCCESS) {
            break;
        }

        if (src != NULL) {
            src += GD25_PAGE_SIZE;
        }
        if (spare != NULL) {
            spare += GD25_PAGE_OOB;
        }
    }

    return status;
}
