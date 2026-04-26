/**
 * @file    isr.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the interrupt features of the flash
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

void flash_command_complete() { tx_semaphore_put(&flash_wip); }

void flash_tx_complete() { tx_semaphore_put(&flash_dma_done); }

void flash_rx_complete() { tx_semaphore_put(&flash_dma_done); }

extern void flash_polling_complete() { tx_semaphore_put(&flash_wip); }
