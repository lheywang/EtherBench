/**
 * @file    hash.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "main.h"

extern HASH_HandleTypeDef hhash;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_HASH_Init(void);

#ifdef __cplusplus
}
#endif
