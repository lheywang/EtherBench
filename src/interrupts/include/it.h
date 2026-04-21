/**
 * @file    it.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Interrupt handler that isn't linked to the HAL, but can't be privatized to
 * 			a single file as they may be shared.
 *
 * @version 0.1
 * @date    2026-03-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once


// ======================================================================
//                              FUNCTIONS
// ======================================================================
// For the logger task
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

// For the QSPI Driver
void HAL_XSPI_CmdCpltCallback(XSPI_HandleTypeDef *hxspi);
void HAL_XSPI_TxCpltCallback(XSPI_HandleTypeDef *hxspi);
void HAL_XSPI_RxCpltCallback(XSPI_HandleTypeDef *hxspi);
