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
#include "peripherals/octospi.h"

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

UINT GD5F1GO4UBY1G_set_protected_blocks(UCHAR status) {

    /*
     * Then, enable the write operation
     */
    if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Prepare the command
     */
    XSPI_RegularCmdTypeDef cmd = {0};
    cmd.Instruction = GD25_SET_FEATURES;
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_8_BITS;
    cmd.Address =  GD25_FEATURE_REG_PROTECTION;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 0;

    /*
     * Execute the command
     */
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;
    if (HAL_XSPI_Transmit(&hospi1, &status, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;

    /*
     * Wait for finish
     */
    GD5F1GO4UBY1G_wait_for_complete();

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_enable_quad() {

    /*
     * Then, enable the write operation
     */
    if (GD5F1GO4UBY1G_write_enable() != LX_SUCCESS)
        return LX_ERROR;

    /*
     * Prepare the command
     */
    XSPI_RegularCmdTypeDef cmd = {0};
    cmd.Instruction = GD25_SET_FEATURES;
    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_8_BITS;
    cmd.Address =  GD25_FEATURE_REG_FEATURE_1;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 0;

    /*
     * Execute the command
     */
    uint8_t reg = GD25_FEATURE_BIT_QE;
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;
    if (HAL_XSPI_Transmit(&hospi1, &reg, HAL_MAX_DELAY) != HAL_OK)
        return LX_ERROR;

    /*
     * Wait for finish
     */
    GD5F1GO4UBY1G_wait_for_complete();

    /*
     * Finally, enable the QSPI communication on the host side 
     */
    HAL_XSPI_InitAsQSPI(&hospi1);

    return LX_SUCCESS;
}
