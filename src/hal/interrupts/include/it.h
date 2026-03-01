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

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
