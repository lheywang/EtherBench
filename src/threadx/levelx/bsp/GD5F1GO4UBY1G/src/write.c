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
#include "stm32h5xx_hal_xspi.h"

// LevelX
#include "lx_api.h"

// ThreadX
#include "tx_api.h"

// STD
#include <string.h>

// Extern
extern XSPI_HandleTypeDef hospi1;     // From HAL
extern DCACHE_HandleTypeDef hdcache1; // From HAL

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_generic_write(ULONG block,
                                 ULONG page,
                                 UCHAR *main_buffer,
                                 ULONG main_size,
                                 UCHAR *spare_buffer,
                                 ULONG spare_size) {

    /*
     * First, transfer the target page into the cache register
     */
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

    /*
     * Write the first elements for the buffer (as PROGRAM_LOAD --> Set all to 0xFF !)
     */
    if ((main_buffer != NULL) && (main_size > 0)) {

        cmd.DataLength = main_size;
        cmd.Address = 0;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;

        /*
         * If the size if greater than the DMA threshold, run with it. Otherwise, perform the standard reading method.
         */
        if (main_size > GD25_DMA_THRESHOLD) {

            /*
             * Ensure the data in RAM does match the one we have in cache...
             */
            HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)main_buffer, main_size);

            /*
             * Call here the DMA setup + semaphore get.
             */
            // Clean the semaphore...
            while (tx_semaphore_get(&flash_dma_done, TX_NO_WAIT) == TX_SUCCESS)
                ;

            // Run the transfer
            if (HAL_XSPI_Transmit_DMA(&hospi1, (uint8_t *)main_buffer) != HAL_OK)
                return LX_ERROR;
            if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
                return LX_ERROR;

        } else {

            if (HAL_XSPI_Transmit(&hospi1, (uint8_t *)main_buffer, HAL_MAX_DELAY) != HAL_OK)
                return LX_ERROR;
        }

        /*
         * Ensure the next command won't erase our buffer.
         */
        cmd.Instruction = GD25_LOAD_RANDOM_DATA_X4;
    }

    /*
     * Add the next elements of the buffer :
     */
    if ((spare_buffer != NULL) && (spare_size > 0)) {

        cmd.DataLength = spare_size;
        cmd.Address = GD25_PAGE_OOD_ADDR;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;

        /*
         * If the size if greater than the DMA threshold, run with it. Otherwise, perform the standard reading method.
         */
        if (spare_size > GD25_DMA_THRESHOLD) {

            /*
             * Ensure the data in RAM does match the one we have in cache...
             */
            HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)spare_buffer, spare_size);

            /*
             * Call here the DMA setup + semaphore get.
             */
            // Clean the semaphore...
            while (tx_semaphore_get(&flash_dma_done, TX_NO_WAIT) == TX_SUCCESS)
                ;

            // Run the transfer
            if (HAL_XSPI_Transmit_DMA(&hospi1, (uint8_t *)spare_buffer) != HAL_OK)
                return LX_ERROR;
            if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
                return LX_ERROR;

        } else {

            if (HAL_XSPI_Transmit(&hospi1, (uint8_t *)spare_buffer, HAL_MAX_DELAY) != HAL_OK)
                return LX_ERROR;
        }
    }

    /*
     * Then, enable the write operation
     */
    if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Then, ask the NAND to write the data into the array
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
     * Wait for finish..
     */
    return GD5F1GO4UBY1G_wait_for_complete();
}

UINT GD5F1GO4UBY1G_page_write(ULONG block, ULONG page, ULONG *source, ULONG words) {
    return GD5F1GO4UBY1G_generic_write(block, page, (UCHAR *)source, words * (sizeof(ULONG) / sizeof(UCHAR)), NULL, 0);
}

UINT GD5F1GO4UBY1G_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size) {
    return GD5F1GO4UBY1G_generic_write(block, page, NULL, 0, source, size);
}

UINT GD5F1GO4UBY1G_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages) {

    UINT status = LX_SUCCESS;
    UCHAR *src = main_buffer;
    UCHAR *spare = spare_buffer;

    for (ULONG i = 0; i < pages; i++) {

        ULONG current_main_size = (main_buffer != NULL) ? GD25_PAGE_SIZE : 0;
        ULONG current_spare_size = (spare_buffer != NULL) ? GD25_PAGE_OOB : 0;

        status = GD5F1GO4UBY1G_generic_write(block, page + i, src, current_main_size, spare, current_spare_size);
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
