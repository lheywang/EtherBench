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
#include <string.h>

PCD_HandleTypeDef hpcd_USB_DRD_FS;

void MX_USB_PCD_Init(void) {
    /* USER CODE BEGIN USB_Init 1 */
    memset(&hpcd_USB_DRD_FS, 0, sizeof(hpcd_USB_DRD_FS));

    hpcd_USB_DRD_FS.Instance = USB_DRD_FS;
    hpcd_USB_DRD_FS.Init.dev_endpoints = 8;
    hpcd_USB_DRD_FS.Init.speed = USBD_FS_SPEED;
    hpcd_USB_DRD_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
    hpcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
    hpcd_USB_DRD_FS.Init.lpm_enable = DISABLE;
    hpcd_USB_DRD_FS.Init.battery_charging_enable = DISABLE;
    hpcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE; // Essentiel !
    hpcd_USB_DRD_FS.Init.bulk_doublebuffer_enable = DISABLE;
    hpcd_USB_DRD_FS.Init.iso_singlebuffer_enable = DISABLE;

    // L'appel à HAL_PCD_Init va automatiquement appeler HAL_PCD_MspInit ci-dessous !
    if (HAL_PCD_Init(&hpcd_USB_DRD_FS) != HAL_OK) {
        Error_Handler();
    }

    // Configuration de la RAM USB (PMA)
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x00, PCD_SNG_BUF, 0x40);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x80, PCD_SNG_BUF, 0x80);

    /* Armer l'interruption NVIC */
    HAL_NVIC_SetPriority(USB_DRD_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USB_DRD_FS_IRQn);
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *pcdHandle) {
    if (pcdHandle->Instance == USB_DRD_FS) {
        /* 1. Activer l'horloge de l'alimentation */
        // __HAL_RCC_PWR_CLK_ENABLE();

        /* 2. Activer VDDUSB et ATTENDRE QU'IL SOIT PRET */
        HAL_PWREx_EnableVddUSB();
        // VITAL : Attendre que la tension monte (10ms suffisent)
        HAL_Delay(10);

        /* 3. Activer le port GPIOA */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* 4. Activer l'horloge USB */
        __HAL_RCC_USB_CLK_ENABLE();

        /* 5. FORCER UN RESET MATÉRIEL DU CŒUR USB */
        __HAL_RCC_USB_FORCE_RESET();
        HAL_Delay(2);
        __HAL_RCC_USB_RELEASE_RESET();

        /* 6. Configurer les GPIOs */
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        // Essayons une vitesse normale. Parfois VERY_HIGH crée des rebonds (ringing) sur les PHY embarquées
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_USB;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}
