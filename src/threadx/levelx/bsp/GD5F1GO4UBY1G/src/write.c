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
#include "tx_api.h"

// STD
#include <string.h>

// Extern
extern XSPI_HandleTypeDef hospi1;                 // From HAL
extern DCACHE_HandleTypeDef hdcache1;             // From HAL
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
                                 ULONG spare_size) {

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
    cmd.Address = (main_buffer != NULL) ? 0 : GD25_PAGE_OOD_ADDR;

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
         * Ensure that all the data is into the RAM.
         */
        if (main_buffer)
            HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)main_buffer, main_size);
        if (spare_buffer)
            HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)spare_buffer, spare_size);

        /*
         * Build the linked list for the DMA
         */
        if (STM32H563_prepare_dma_xfer(main_buffer, main_size, spare_buffer, spare_size, true) != LX_SUCCESS)
            return LX_ERROR;
        if (HAL_DMAEx_List_LinkQ(&handle_GPDMA1_octospiTX, &dma_xfer) != HAL_OK)
            return LX_ERROR;

        /*
         * Start the transfer
         */
        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;
        if (HAL_XSPI_Transmit_DMA(&hospi1, main_buffer) != HAL_OK)
            return LX_ERROR;

        if (tx_semaphore_get(&flash_dma_done, TX_WAIT_FOREVER) != TX_SUCCESS)
            return LX_ERROR;

    } else {

        /*
         * Build the buffer
         */
        uint8_t buf[GD25_DMA_THRESHOLD + 2] = {0};

        if (main_buffer) {
            memcpy(buf, main_buffer, main_size);
        }
        if (spare_buffer) {
            memcpy(buf + main_size, spare_buffer, spare_size);
        }

        /*
         * Transfer from the local buffer
         */
        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
            return LX_ERROR;

        MODIFY_REG(hospi1.Instance->CR, XSPI_CR_FMODE, 0x0UL);
        hospi1.State = HAL_XSPI_STATE_BUSY_TX;
        HAL_XSPI_ENABLE_IT(&hospi1, HAL_XSPI_IT_TE);

        HAL_DMAEx_List_Start_IT(&handle_GPDMA1_octospiTX);

        WRITE_REG(hospi1.Instance->AR, hospi1.Instance->AR);
        SET_BIT(hospi1.Instance->CR, OCTOSPI_CR_DMAEN);
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
