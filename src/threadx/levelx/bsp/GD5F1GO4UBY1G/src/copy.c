/**
 * @file    copy.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the copy features of the GD5F1GO4UBY1G flash.
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

UINT GD5F1GO4UBY1G_page_copy(ULONG src_block, ULONG src_page, ULONG dest_block, ULONG dest_page, ULONG pages, UCHAR *buffer) {

    TX_PARAMETER_NOT_USED(buffer);

    XSPI_RegularCmdTypeDef cmd = {0};

    for (int current_page = 0; current_page < pages; current_page += 1)
    {
        uint32_t src_addr = (src_block * GD25_BLOCK_PAGES) + src_page + current_page;
        uint32_t dest_addr = (dest_block * GD25_BLOCK_PAGES) + dest_page + current_page;

        /*
         * First, load the data from the cache
         */
        cmd.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
        cmd.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
        cmd.Instruction        = GD25_READ_TO_CACHE;
        cmd.AddressMode        = HAL_XSPI_ADDRESS_1_LINE;
        cmd.AddressWidth       = HAL_XSPI_ADDRESS_24_BITS;
        cmd.Address            = src_addr;
        cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
        cmd.DataMode           = HAL_XSPI_DATA_NONE;
        cmd.DummyCycles        = 0;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) return LX_ERROR;
        if (GD5F1GO4UBY1G_wait_for_complete() != LX_SUCCESS) return LX_ERROR;

        /*
         * Enable writes
         */
        if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS) return LX_ERROR;

        /*
         * Then, write to the flash
         */
        cmd.Instruction        = GD25_PROGRAM_EXECUTE;
        cmd.Address            = dest_addr;

        if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) return LX_ERROR;
        if (GD5F1GO4UBY1G_wait_for_complete() != LX_SUCCESS) return LX_ERROR;
    }

    return LX_SUCCESS;
}
