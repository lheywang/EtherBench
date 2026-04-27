/**
 * @file    erase.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the erase features of the GD5F1GO4UBY1G flash.
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
#include "GD5F1GO4UBY1G.h"

// Local libraries
#include "commands.h"
#include "logger.h"

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

UINT GD5F1GO4UBY1G_rescue() {

    XSPI_RegularCmdTypeDef cmd = {0};
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DummyCycles = 0;

    for (uint32_t block = 0; block < 1024; block++) {
        GD5F1GO4UBY1G_write_enable();

        cmd.Instruction = 0xD8;
        cmd.Address = block * GD25_BLOCK_PAGES;
        HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

        UINT status = GD5F1GO4UBY1G_wait_for_complete();
        if (status) {
            LOG("Block %d marked as BAD.", block);
        }
    }

    return LX_SUCCESS;
}
