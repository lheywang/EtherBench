/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32h5xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_it.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ETH_HandleTypeDef heth;
extern DMA_HandleTypeDef handle_GPDMA2_Channel0;
extern UART_HandleTypeDef huart3;
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;
extern TIM_HandleTypeDef htim6;
extern SD_HandleTypeDef hsd1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {}

/******************************************************************************/
/* STM32H5xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h5xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles Flash non-secure global interrupt.
 */
void FLASH_IRQHandler(void) { HAL_FLASH_IRQHandler(); }

/**
 * @brief This function handles RCC non-secure global interrupt.
 */
void RCC_IRQHandler(void) {}

/**
 * @brief This function handles TIM6 global interrupt.
 */
void TIM6_IRQHandler(void) { HAL_TIM_IRQHandler(&htim6); }

/**
 * @brief This function handles USART3 global interrupt.
 */
void USART3_IRQHandler(void) { HAL_UART_IRQHandler(&huart3); }

/**
 * @brief This function handles USB FS global interrupt.
 */
void USB_DRD_FS_IRQHandler(void) { HAL_PCD_IRQHandler(&hpcd_USB_DRD_FS); }

/**
 * @brief This function handles GPDMA2 Channel 0 global interrupt.
 */
void GPDMA2_Channel0_IRQHandler(void) {
    // HAL_DMA_IRQHandler(&handle_GPDMA2_Channel0);
}

/**
 * @brief This function handles FPU global interrupt.
 */
void FPU_IRQHandler(void) {}

/**
 * @brief This function handles Instruction cache global interrupt.
 */
void ICACHE_IRQHandler(void) { HAL_ICACHE_IRQHandler(); }

/**
 * @brief This function handles Ethernet global interrupt.
 */
void ETH_IRQHandler(void) { HAL_ETH_IRQHandler(&heth); }

/**
 * @brief This function handles Ethernet Wakeup global interrupt.
 */
void ETH_WKUP_IRQHandler(void) { HAL_ETH_IRQHandler(&heth); }

/**
 * @brief Handle SDMMC1 global interrupt.
 */
void SDMMC1_IRQHandler(void) { HAL_SD_IRQHandler(&hsd1); }
