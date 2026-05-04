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
#include "stm32h5xx_hal_dma.h"
#include "stm32h5xx_hal_dma_ex.h"
#include "stm32h5xx_hal_xspi.h"

// LevelX
#include "lx_api.h"

// ThreadX
#include "tx_api.h"

// STD
#include <stdbool.h>
#include <string.h>

// Extern
extern XSPI_HandleTypeDef hospi1;                 // From HAL
extern DCACHE_HandleTypeDef hdcache1;             // From HAL
extern TX_SEMAPHORE flash_wip;                    // From launcher
extern TX_SEMAPHORE flash_dma_done;               // From launcher
extern DMA_HandleTypeDef handle_GPDMA1_octospiTX; // from hal/init/octospi.c
extern DMA_HandleTypeDef handle_GPDMA1_octospiRX; // from hal/init/octospi.c

// ======================================================================
//                              VARIABLES
// ======================================================================
DMA_NodeTypeDef __aligned(32) master_xfer;
DMA_NodeTypeDef __aligned(32) slave_xfer;
DMA_QListTypeDef __aligned(32) dma_xfer;

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

    // Clean the semaphore...
    while (tx_semaphore_get(&flash_wip, TX_NO_WAIT) == TX_SUCCESS)
        ;

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
        if ((status_reg & GD25_FEATURE_BIT_E_FAIL) || (status_reg & GD25_FEATURE_BIT_P_FAIL)) {

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

UINT STM32H563_prepare_dma_xfer(UCHAR *main_buffer, ULONG main_size, UCHAR *spare_buffer, ULONG spare_size, bool isTx) {

    /*
     * Clearing the list
     */
    if (HAL_DMAEx_List_ResetQ(&dma_xfer) != HAL_OK)
        return LX_ERROR;

    /*
     * First, configure the common node to be passed to the GPDMA :
     */
    DMA_NodeConfTypeDef node_config = {0};

    // General settings about the DMA.
    node_config.NodeType = DMA_GPDMA_LINEAR_NODE;
    node_config.Init.Request = GPDMA1_REQUEST_OCTOSPI1;

    if (isTx) {
        node_config.Init.Direction = DMA_MEMORY_TO_PERIPH;
    } else {
        node_config.Init.Direction = DMA_PERIPH_TO_MEMORY;
    }

    node_config.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    node_config.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;

    /*
     * Set the burst sizes. Fixed to 1, otherwise non-round transfers will fail.
     */
    node_config.Init.SrcBurstLength = 1;
    node_config.Init.DestBurstLength = 1;

    node_config.Init.Mode = DMA_NORMAL;

    if (isTx) {
        node_config.Init.SrcInc = DMA_SINC_INCREMENTED;
        node_config.Init.DestInc = DMA_DINC_FIXED;
    } else {
        node_config.Init.SrcInc = DMA_SINC_FIXED;
        node_config.Init.DestInc = DMA_DINC_INCREMENTED;
    }

    // As the datasheet recommand !
    if (isTx) {
        node_config.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT1;
    } else {
        node_config.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT1 | DMA_DEST_ALLOCATED_PORT0;
    }

    /*
     * Build the first node. For the main buffer.
     */
    if (main_buffer) {
        node_config.DataSize = main_size;

        if (spare_buffer) {
            node_config.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
        } else {
            node_config.Init.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;
        }

        if (isTx) {
            node_config.SrcAddress = (uint32_t)main_buffer;
            node_config.DstAddress = (uint32_t)&OCTOSPI1->DR;
        } else {
            node_config.SrcAddress = (uint32_t)&OCTOSPI1->DR;
            node_config.DstAddress = (uint32_t)main_buffer;
        }

        if (HAL_DMAEx_List_BuildNode(&node_config, &master_xfer) != HAL_OK)
            return LX_ERROR;

        if ((main_buffer) && (main_size > 0)) {
            if (HAL_DMAEx_List_InsertNode_Tail(&dma_xfer, &master_xfer) != HAL_OK)
                return LX_ERROR;
        }

        /*
         * Push the variable into RAM.
         */
        HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)&master_xfer, sizeof(DMA_NodeTypeDef));
    }

    /*
     * Build the second node. For the spare buffer.
     */
    if (spare_buffer) {

        node_config.DataSize = spare_size;
        node_config.Init.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;

        if (isTx) {
            node_config.SrcAddress = (uint32_t)spare_buffer;
            node_config.DstAddress = (uint32_t)&OCTOSPI1->DR;
        } else {
            node_config.SrcAddress = (uint32_t)&OCTOSPI1->DR;
            node_config.DstAddress = (uint32_t)spare_buffer;
        }

        if (HAL_DMAEx_List_BuildNode(&node_config, &slave_xfer) != HAL_OK)
            return LX_ERROR;

        if ((spare_buffer) && (spare_size > 0)) {
            if (HAL_DMAEx_List_InsertNode_Tail(&dma_xfer, &slave_xfer) != HAL_OK)
                return LX_ERROR;
        }

        /*
         * Push the variable into the RAM.
         */
        HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)&slave_xfer, sizeof(DMA_NodeTypeDef));
    }

    /*
     * Push the whole transfer into the RAM.
     */
    HAL_DCACHE_CleanByAddr(&hdcache1, (uint32_t *)&dma_xfer, sizeof(DMA_QListTypeDef));

    if (isTx) {
        if (HAL_DMAEx_List_LinkQ(&handle_GPDMA1_octospiTX, &dma_xfer) != HAL_OK)
            return LX_ERROR;
    } else {
        if (HAL_DMAEx_List_LinkQ(&handle_GPDMA1_octospiRX, &dma_xfer) != HAL_OK)
            return LX_ERROR;
    }

    return LX_SUCCESS;
}
