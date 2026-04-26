/**
 * @file    status.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the status features of the GD5F1GO4UBY1G flash.
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

UINT GD5F1GO4UBY1G_block_status_get(ULONG block, UCHAR *bad_block_byte) {
    XSPI_RegularCmdTypeDef cmd = {0};
    uint32_t row_addr = (block * GD25_BLOCK_PAGES);

    /*
     * First, load this page into the cache
     */
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_READ_TO_CACHE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    cmd.Address = row_addr;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;
    if (GD5F1GO4UBY1G_wait_for_complete() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Then, read the first byte from the the OOB area
     */
    cmd.Instruction = GD25_READ_FROM_CACHE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.Address = (uint16_t)GD25_PAGE_OOD_ADDR;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 8;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;
    if (HAL_XSPI_Receive(&hospi1, bad_block_byte, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_block_status_set(ULONG block, UCHAR bad_block_byte) {
    XSPI_RegularCmdTypeDef cmd = {0};
    uint32_t row_addr = (block * GD25_BLOCK_PAGES);

    /*
     * First, load the page into the cache
     */
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_PROGRAM_LOAD;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_16_BITS;
    cmd.Address = GD25_PAGE_OOD_ADDR;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;
    if (HAL_XSPI_Transmit(&hospi1, &bad_block_byte, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;

    /*
     * Then, enable the write operation
     */
    if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Finally, start the write process, and wait for it's finish.
     */
    cmd.Instruction = GD25_PROGRAM_EXECUTE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    cmd.Address = row_addr;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DataLength = 0;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;

    return GD5F1GO4UBY1G_wait_for_complete();
}
