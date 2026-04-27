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
    return GD5F1GO4UBY1G_generic_read(block, 0, NULL, 0, bad_block_byte, 1);
}

UINT GD5F1GO4UBY1G_block_status_set(ULONG block, UCHAR bad_block_byte) {
    return GD5F1GO4UBY1G_generic_write(block, 0, NULL, 0, &bad_block_byte, 1);
}
