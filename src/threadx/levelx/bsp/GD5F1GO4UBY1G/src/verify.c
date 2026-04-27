/**
 * @file    verify.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the verification features of the GD5F1GO4UBY1G flash.
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

UINT GD5F1GO4UBY1G_block_erase_verify(ULONG block) {
    if (GD5F1GO4UBY1G_page_erase_verify(block, 0) != LX_SUCCESS) {
        return LX_ERROR;
    }

    if (GD5F1GO4UBY1G_page_erase_verify(block, GD25_BLOCK_PAGES - 1) != LX_SUCCESS) {
        return LX_ERROR;
    }

    return LX_SUCCESS;
}

UINT GD5F1GO4UBY1G_page_erase_verify(ULONG block, ULONG page) {
    ULONG page_buffer[GD25_PAGE_SIZE / sizeof(ULONG)];

    /*
     * Read the whole page
     */
    if (GD5F1GO4UBY1G_page_read(block, page, page_buffer, GD25_PAGE_SIZE / sizeof(ULONG)) != LX_SUCCESS) {
        return LX_ERROR;
    }

    /*
     * Iterate over the whole buffer (512 words), and check if they're equal, or not.
     */
    for (uint32_t i = 0; i < (GD25_PAGE_SIZE / sizeof(ULONG)); i++) {
        if (page_buffer[i] != 0xFFFFFFFF) {
            return LX_ERROR;
        }
    }

    return LX_SUCCESS;
}