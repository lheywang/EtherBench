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
#include "stm32h5xx_hal_xspi.h"

// LevelX
#include "lx_api.h"

// ThreadX
#include "tx_api.h"

// STD
#include <string.h>

// Extern
extern XSPI_HandleTypeDef hospi1; // From HAL

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    XSPI_RegularCmdTypeDef cmd = {0};

    uint32_t row_addr = (block * GD25_BLOCK_PAGES) + page;

    /*
     * First, transfer the target page into the cache register
     */
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_READ_TO_CACHE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.Address = row_addr;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    if (GD5F1GO4UBY1G_wait_for_complete() != LX_SUCCESS) {
        return LX_ERROR;
    }

    /*
     * Second step, read from the cache into the local RAM.
     */
    cmd.Instruction = GD25_READ_FROM_CACHE_QIO;
    cmd.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.Address = 0x0000;
    cmd.DataMode = HAL_XSPI_DATA_4_LINES;
    cmd.DataLength = words * sizeof(ULONG);
    cmd.DummyCycles = 2;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    if (HAL_XSPI_Receive(&hospi1, (uint8_t *)destination, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages) {

    TX_PARAMETER_NOT_USED(spare_buffer);

    UINT status = LX_SUCCESS;
    ULONG *dest = (ULONG *)main_buffer;


    for (ULONG i = 0; i < pages; i++) {        
        status = GD5F1GO4UBY1G_page_read(block, page + i, dest, GD25_PAGE_SIZE);
        if (status != LX_SUCCESS) {
            break;
        }
        
        dest += GD25_PAGE_SIZE; 
    }
    
    return status;
}
