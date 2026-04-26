/**
 * @file    common.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the common features of the GD5F1GO4UBY1G flash.
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
extern XSPI_HandleTypeDef hospi1;   // From HAL
extern TX_SEMAPHORE flash_wip;      // From launcher
extern TX_SEMAPHORE flash_dma_done; // From launcher

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_wait_for_complete() {

    /*
     * Build the polling config, and wait for the end of operation.
     * This process will be done by the semaphore to be available, done from an ISR.
     */

    XSPI_RegularCmdTypeDef cmd = {0};

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_GET_FEATURES;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_8_BITS;
    cmd.Address = GD25_FEATURE_REG_STATUS_1;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 0;

    XSPI_AutoPollingTypeDef cfg = {0};

    cfg.MatchValue = 0x00;
    cfg.MatchMask = GD25_FEATURE_BIT_OIP;
    cfg.MatchMode = HAL_XSPI_MATCH_MODE_AND;
    cfg.IntervalTime = 0x40;
    cfg.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    if (HAL_XSPI_AutoPolling_IT(&hospi1, &cfg) != HAL_OK) {
        return LX_ERROR;
    }

    if (tx_semaphore_get(&flash_wip, 10000) != TX_SUCCESS) { // 10s
        return LX_ERROR;
    }

    /*
     * Then, fetch the result, and ensure the operation did ended up sucessfully.
     */
    uint8_t status_reg = 0;
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) == HAL_OK) {
        HAL_XSPI_Receive(&hospi1, &status_reg, HAL_MAX_DELAY);
        if ((status_reg & GD25_FEATURE_BIT_E_FAIL) ||
            (status_reg & GD25_FEATURE_BIT_P_FAIL)) {

            /*
             * In case of failure, just reset (to clear the flag).
             */
            GD5F1GO4UBY1G_reset();
            return LX_ERROR;
        }
    }

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_write_enable() {

    /*
     * First, build up the command
     */
    XSPI_RegularCmdTypeDef cmd = {0};

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_WRITE_ENABLE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_NONE;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DummyCycles = 0;

    /*
     * Run the command in polling mode, as this one is fast.
     */
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    /*
     * Start and auto polling to check that the WEL bit is set (ready).
     */
    cmd.Instruction = GD25_GET_FEATURES;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_8_BITS;
    cmd.Address = GD25_FEATURE_REG_STATUS_1;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;

    XSPI_AutoPollingTypeDef cfg = {0};

    cfg.MatchValue = GD25_FEATURE_BIT_WEL;
    cfg.MatchMask = GD25_FEATURE_BIT_WEL;
    cfg.MatchMode = HAL_XSPI_MATCH_MODE_AND;
    cfg.IntervalTime = 0x40;
    cfg.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }

    if (HAL_XSPI_AutoPolling_IT(&hospi1, &cfg) != HAL_OK) {
        return LX_ERROR;
    }

    if (tx_semaphore_get(&flash_wip, 10000) != TX_SUCCESS) { // 10s
        return LX_ERROR;
    }

    /*
     * Then, fetch the result, and ensure the operation did ended up sucessfully.
     */
    uint8_t status_reg = 0;
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) == HAL_OK) {
        HAL_XSPI_Receive(&hospi1, &status_reg, HAL_MAX_DELAY);
        if ((status_reg & GD25_FEATURE_BIT_WEL) == 0) {
            return LX_ERROR;
        }
    }

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_write_disable() {

    /*
     * First, build up the command
     */
    XSPI_RegularCmdTypeDef cmd = {0};

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_WRITE_DISABLE;
    cmd.AddressMode = HAL_XSPI_ADDRESS_NONE;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DummyCycles = 0;

    /*
     * Run the command in polling mode, as this one is fast.
     */
    if (HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK) {
        return LX_ERROR;
    }
    return LX_SUCCESS;
}

UCHAR GD5F1GO4UBY1G_Read_Register(UCHAR reg_addr) {
    XSPI_RegularCmdTypeDef cmd = {0};
    UCHAR reg_val = 0;

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_GET_FEATURES;
    cmd.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    cmd.AddressWidth = HAL_XSPI_ADDRESS_8_BITS;
    cmd.Address = reg_addr;
    cmd.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    cmd.DataMode = HAL_XSPI_DATA_1_LINE;
    cmd.DataLength = 1;
    cmd.DummyCycles = 0;

    HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
    HAL_XSPI_Receive(&hospi1, &reg_val, HAL_MAX_DELAY);

    return reg_val;
}

UINT GD5F1GO4UBY1G_reset() {

    XSPI_RegularCmdTypeDef cmd = {0};

    cmd.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    cmd.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25_RESET;
    cmd.AddressMode = HAL_XSPI_ADDRESS_NONE;
    cmd.DataMode = HAL_XSPI_DATA_NONE;
    cmd.DataLength = 0;
    cmd.DummyCycles = 0;

    HAL_XSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

    return LX_SUCCESS;
}
