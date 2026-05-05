/**
 * @file    stm32h5xx_it.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   ST Interrupt file
 * @version 0.1
 * @date    2026-04-21
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
#include "stm32h5xx_it.h"
#include "main.h"

extern ETH_HandleTypeDef heth;
extern DMA_HandleTypeDef handle_GPDMA2_Channel0;
extern UART_HandleTypeDef huart3;
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;
extern TIM_HandleTypeDef htim6;
extern SD_HandleTypeDef hsd1;
extern XSPI_HandleTypeDef hospi1;
extern DMA_HandleTypeDef hdma_usart3_tx;          // From HAL
extern XSPI_HandleTypeDef hospi1;                 // From HAL
extern DMA_HandleTypeDef handle_GPDMA1_octospiTX; // From HAL
extern DMA_HandleTypeDef handle_GPDMA1_octospiRX; // From HAL

// ======================================================================
//                              CORTEX HANDLERS
// ======================================================================
void NMI_Handler(void) {
    while (1) {
    }
}

void HardFault_Handler(void) {
    while (1) {
    }
}

void MemManage_Handler(void) {
    while (1) {
    }
}

void BusFault_Handler(void) {
    while (1) {
    }
}

void UsageFault_Handler(void) {
    while (1) {
    }
}

void DebugMon_Handler(void) {}

// ======================================================================
//                         DEFAULT PERIPHERALS
// ======================================================================

void FLASH_IRQHandler(void) { HAL_FLASH_IRQHandler(); }

void RCC_IRQHandler(void) {}

void TIM6_IRQHandler(void) { HAL_TIM_IRQHandler(&htim6); }

void USART3_IRQHandler(void) { HAL_UART_IRQHandler(&huart3); }

void USB_DRD_FS_IRQHandler(void) { HAL_PCD_IRQHandler(&hpcd_USB_DRD_FS); }

void FPU_IRQHandler(void) {}

void ICACHE_IRQHandler(void) { HAL_ICACHE_IRQHandler(); }

void ETH_IRQHandler(void) { HAL_ETH_IRQHandler(&heth); }

void ETH_WKUP_IRQHandler(void) { HAL_ETH_IRQHandler(&heth); }

void SDMMC1_IRQHandler(void) { HAL_SD_IRQHandler(&hsd1); }

void OCTOSPI1_IRQHandler(void) { HAL_XSPI_IRQHandler(&hospi1); }

void GPDMA1_Channel0_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart3_tx); }

void GPDMA1_Channel4_IRQHandler(void) { HAL_DMA_IRQHandler(&handle_GPDMA1_octospiTX); }

void GPDMA1_Channel5_IRQHandler(void) { HAL_DMA_IRQHandler(&handle_GPDMA1_octospiRX); }