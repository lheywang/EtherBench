/**
 * @file    spi.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   SPI init code
 * @version 0.1
 * @date    2026-03-11
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

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi3;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_SPI1_Init(void);
void MX_SPI3_Init(void);

#ifdef __cplusplus
}
#endif
