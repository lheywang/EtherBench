/**
 * @file    fx_levelx_driver.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Logic glue from LevelX to FileX
 * @version 0.1
 * @date    2026-04-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                             INCLUDES
// ======================================================================
// FileX
#include "fx_api.h"

// LevelX
#include "lx_api.h"

// ======================================================================
//                             FUNCTIONS
// ======================================================================
/**
 * @brief Implement the basic LevelX virtual driver.
 *
 * @param   media_ptr The accessed ressource
 * @return  VOID
 */
VOID fx_levelx_nand_driver(FX_MEDIA *media_ptr);