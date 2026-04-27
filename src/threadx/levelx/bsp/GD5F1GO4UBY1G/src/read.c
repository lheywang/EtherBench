/**
 * @file    read.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the read features of the GD5F1GO4UBY1G flash.
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

UINT GD5F1GO4UBY1G_generic_read(ULONG block,
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
    cmd.Instruction = GD25_READ_TO_CACHE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    cmd.Address = row_addr;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DataLength = 0;
    cmd.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    if (GD5F1GO4UBY1G_wait_for_complete() != LX_SUCCESS) {
        return LX_ERROR;
    }

    /*
     * Then, read the required bytes
     */
    cmd.Instruction = GD25_READ_FROM_CACHE_QIO;
    cmd.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.DataMode = HAL_XSPI_DATA_4_LINES;
    cmd.DummyCycles = 2;

    if ((main_buffer != NULL) && (main_size > 0)) {
        cmd.Address = 0x0000;
        cmd.DataLength = main_size;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;

        /*
         * If the size if greater than the DMA threshold, run with it. Otherwise, perform the standard reading method.
         */
        if (main_size > GD25_DMA_THRESHOLD) {
            /*
             * Call here the DMA setup + semaphore get.
             */
            if (HAL_XSPI_Receive_DMA(&hospi1, (uint8_t *)main_buffer) != HAL_OK)
                return LX_ERROR;
            if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
                return LX_ERROR;

            /*
             * Ensure the data we got is nice.
             */
            HAL_DCACHE_InvalidateByAddr(&hdcache1, (uint32_t *)main_buffer, main_size);

        } else {
            if (HAL_XSPI_Receive(&hospi1, (uint8_t *)main_buffer, HAL_MAX_DELAY) != HAL_OK)
                return LX_ERROR;
        }
    }

    if ((spare_buffer != NULL) && (spare_size > 0)) {

        cmd.Address = GD25_PAGE_OOD_ADDR;
        cmd.DataLength = spare_size;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;

        /*
         * If the size if greater than the DMA threshold, run with it. Otherwise, perform the standard reading method.
         */
        if (spare_size > GD25_DMA_THRESHOLD) {
            /*
             * Call here the DMA setup + semaphore get.
             */
            if (HAL_XSPI_Receive_DMA(&hospi1, (uint8_t *)spare_buffer) != HAL_OK)
                return LX_ERROR;
            if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
                return LX_ERROR;

            /*
             * Ensure the data we got is nice.
             */
            HAL_DCACHE_InvalidateByAddr(&hdcache1, (uint32_t *)spare_buffer, spare_size);

        } else {

            if (HAL_XSPI_Receive(&hospi1, (uint8_t *)spare_buffer, HAL_MAX_DELAY) != HAL_OK)
                return LX_ERROR;
        }
    }

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    return GD5F1GO4UBY1G_generic_read(
        block, page, (UCHAR *)destination, words * (sizeof(ULONG) / sizeof(UCHAR)), NULL, 0);
}

UINT GD5F1GO4UBY1G_extra_bytes_get(ULONG block, ULONG page, UCHAR *destination, UINT size) {
    return GD5F1GO4UBY1G_generic_read(block, page, NULL, 0, destination, size);
}

UINT GD5F1GO4UBY1G_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages) {

    UINT status = LX_SUCCESS;
    ULONG *dest = (ULONG *)main_buffer;
    ULONG *spare = (ULONG *)spare_buffer;

    for (ULONG i = 0; i < pages; i++) {
        status = GD5F1GO4UBY1G_generic_read(block,
                                            page + i,
                                            (UCHAR *)dest,
                                            GD25_PAGE_SIZE * (sizeof(ULONG) / sizeof(UCHAR)),
                                            (UCHAR *)spare,
                                            GD25_PAGE_OOB * (sizeof(ULONG) / sizeof(UCHAR)));
        if (status != LX_SUCCESS) {
            break;
        }

        dest += GD25_PAGE_SIZE;
        spare += GD25_PAGE_OOB;
    }

    return status;
}
