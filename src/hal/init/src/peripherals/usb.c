/**
 * @file    usb.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   USB Init code
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "usb.h"
#include <string.h>

PCD_HandleTypeDef hpcd_USB_DRD_FS;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_USB_PCD_Init(void) {
    memset(&hpcd_USB_DRD_FS, 0, sizeof(hpcd_USB_DRD_FS));
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

    /* NVIC setup */
    HAL_NVIC_SetPriority(USB_DRD_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USB_DRD_FS_IRQn);
    return;
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *pcdHandle) {
    if (pcdHandle->Instance == USB_DRD_FS) {

        HAL_PWREx_EnableVddUSB();
        HAL_Delay(10);

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USB_CLK_ENABLE();
        __HAL_RCC_USB_FORCE_RESET();
        HAL_Delay(2);
        __HAL_RCC_USB_RELEASE_RESET();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_USB;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    return;
}
