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
// Local libraries
#include "commands.h"

// LevelX
#include "lx_api.h"

// ThreadX
#include "tx_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    (void)(block);
    (void)(page);
    (void)(destination);
    (void)(words);
    return LX_ERROR;
}
