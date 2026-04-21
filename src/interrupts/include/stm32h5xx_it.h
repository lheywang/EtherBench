/**
 * @file    stm32h5xx_it.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   ST's interrupts file
 * @version 0.1
 * @date    2026-04-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              FUNCTIONS
// ======================================================================
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void TIM6_IRQHandler(void);
void USART3_IRQHandler(void);
void USB_DRD_FS_IRQHandler(void);
void GPDMA2_Channel0_IRQHandler(void);
void FPU_IRQHandler(void);
void ICACHE_IRQHandler(void);
void ETH_IRQHandler(void);
void ETH_WKUP_IRQHandler(void);

#ifdef __cplusplus
}
#endif

