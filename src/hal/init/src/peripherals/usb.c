/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usb.c
 * @brief   This file provides code for the configuration
 *          of the USB instances.
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
#include "usb.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

PCD_HandleTypeDef hpcd_USB_DRD_FS;

/* USB init function */

void MX_USB_PCD_Init(void) {

  /* USER CODE BEGIN USB_Init 0 */
  // Init the USB alternate functions
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_USB; // Very important!
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hpcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hpcd_USB_DRD_FS.Init.speed = USBD_FS_SPEED;
  hpcd_USB_DRD_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.bulk_doublebuffer_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.iso_singlebuffer_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_DRD_FS) != HAL_OK) {
    Error_Handler();
  }

  // Existing (keep these)
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x00, PCD_SNG_BUF, 0x18);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x80, PCD_SNG_BUF, 0x58);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x81, PCD_SNG_BUF,
                      0x98); // CDC1 interrupt IN
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x02, PCD_SNG_BUF,
                      0xD8); // CDC1 data OUT
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x82, PCD_SNG_BUF,
                      0x118); // CDC1 data IN

  // Add these for CDC2 (terminal)
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x83, PCD_SNG_BUF,
                      0x158); // CDC2 interrupt IN
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x04, PCD_SNG_BUF,
                      0x198); // CDC2 data OUT
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x84, PCD_SNG_BUF,
                      0x1D8); // CDC2 data IN

  // Add these for MSC
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x05, PCD_SNG_BUF, 0x218); // MSC OUT
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x85, PCD_SNG_BUF, 0x258); // MSC IN

  // Add these for CMSIS-DAP
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x06, PCD_SNG_BUF, 0x298); // CMSIS OUT
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x86, PCD_SNG_BUF, 0x2D8); // CMSIS IN

  /* USER CODE BEGIN USB_Init 2 */
  HAL_NVIC_SetPriority(USB_DRD_FS_IRQn, 15, 0); // USB needs very high priority!
  HAL_NVIC_EnableIRQ(USB_DRD_FS_IRQn);

  /* USER CODE END USB_Init 2 */
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *pcdHandle) {

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (pcdHandle->Instance == USB_DRD_FS) {
    /* USER CODE BEGIN USB_DRD_FS_MspInit 0 */

    /* USER CODE END USB_DRD_FS_MspInit 0 */

    /** Initializes the peripherals clock
     */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
      Error_Handler();
    }

    /* Enable VDDUSB */
    HAL_PWREx_EnableVddUSB();
    /* USB_DRD_FS clock enable */
    __HAL_RCC_USB_CLK_ENABLE();
    /* USER CODE BEGIN USB_DRD_FS_MspInit 1 */
    HAL_Delay(20);
    /* USER CODE END USB_DRD_FS_MspInit 1 */
  }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *pcdHandle) {

  if (pcdHandle->Instance == USB_DRD_FS) {
    /* USER CODE BEGIN USB_DRD_FS_MspDeInit 0 */

    /* USER CODE END USB_DRD_FS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB_CLK_DISABLE();
    /* USER CODE BEGIN USB_DRD_FS_MspDeInit 1 */

    /* USER CODE END USB_DRD_FS_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
