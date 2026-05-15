/**
 * @file    vfs_settings.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the settings page we're using to configure the device.
 * @version 0.1
 * @date    2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "vfs_backtrace.h"

// HAL
#include "stm32h5xx.h"

// STD
#include <stdint.h>

// ======================================================================
//                              STRUCTURE
// ======================================================================
/**
 * @brief This structure hold the entire device config, into the 2048
 *        bytes page. Placed on the logical sector 0, by LevelX. May
 *        refer to more advanced configs internally.
 *
 * @return typedef struct
 */
typedef struct __attribute__((packed)) {

    /**
     * @brief Version field. Hold the data about ourselves.
     *
     */
    union {
        uint8_t array[4];
        struct __attribute__((packed)) {
            uint8_t major;    ///< Major version.
            uint8_t minor;    ///< Minor version.
            uint8_t patch;    ///< Patch version.
            uint8_t hardware; ///< Major hardware version, if applicable.
        };
    } software_version;

    /**
     * @brief Hardware field. Hold the data about the serial number.
     *
     */
    union {
        uint8_t array[16]; ///<  Fast access to the whole string.
        struct __attribute__((packed)) {
            char name[4];       ///< constant string name.
            uint8_t version[4]; ///< Hardware version, in the M.m.p.pp format. M is a letter.
            uint64_t timestamp; ///< Fabrication timestamp.
        };
    } hardware_version;

    /*
     * Insert the 'real' config here
     */
    struct __attribute__((packed)) {

        /**
         * @brief Board configuration, such as leds and IO voltage mode.
         *
         */
        struct __attribute__((packed)) {
            uint32_t board_voltage; ///< Selected board voltage.
            uint32_t led_mode;      ///< Selected led mode
            uint32_t protections;   ///< Shall we disable the power supply on short circuit ?
        } board;

        /**
         * @brief Programmer configuration. Define the interactions.
         *
         */
        struct __attribute__((packed)) {
            uint32_t mode;   ///< Programmer operation mode.
            uint32_t bus;    ///< Programmer preferred bus.
            uint32_t speed;  ///< Programmer speed.
            uint32_t method; ///< Programmer connection method.
        } programmer;

        /**
         * @brief Analog configuration, for both of the ADC and the DAC.
         *
         */
        struct __attribute__((packed)) {

            struct __attribute__((packed)) {
                uint32_t speed_speed; ///< The ADC sweep speed, in Hz.
                uint32_t resolution;  ///< The ADC resolution, in bits.
            } adc[2];

            struct __attribute__((packed)) {
                uint32_t value; ///< The default dac output.
            } dac;

        } analog;

        /**
         * @brief Digital configuration, for the different buses.
         *
         */
        struct __attribute__((packed)) {

            struct __attribute__((packed)) {

                uint32_t baudrate;     ///< USART Baudrate.
                uint32_t parity;       ///< USART parity enabled.
                uint32_t stop_bits;    ///< USART number of stop bits.
                uint32_t data_width;   ///< USART data width.
                uint32_t flow_control; ///< Shall we use flow control.

            } usart[2];

            struct __attribute__((packed)) {

                uint32_t mode;         ///< I2C Mode (7B or 10B)
                uint32_t prefix_width; ///< I2C address size.
                uint32_t slave_addr;   ///< I2C Slave address.

            } i2c;

            struct __attribute__((packed)) {

                uint32_t baudrate;     ///< SPI Baudrate.
                uint32_t mode;         ///< SPI Operation mode.
                uint32_t xfer_size;    ///< SPI Transfer size, from 4 to 32 bits.
                uint32_t direction;    ///< SPI Data direction (MSB or LSB)
                uint32_t format;       ///< SPI Frame format.
                uint32_t slave_select; ///< Shall we use the slave select bits ?

            } spi;

            struct __attribute__((packed)) {

                uint32_t frame_format; ///< CAN Frame format.
                uint32_t mode;         ///< CAN operation mode. Specific to this STM32 MCU
                uint32_t quantum;      ///< Quantum size of the CAN bus.

            } can;

            struct __attribute__((packed)) {

                uint32_t enable;    ///< Enable the clock operation.
                uint32_t frequency; ///< Target clock frequency. Can be different if the divider could not be found.

            } clock;

        } digital;

        /**
         * @brief Network configuration, for the fallback IP.
         *
         */
        struct __attribute__((packed)) {

            uint32_t dhcp;        ///< Shall we use the DHCP ?
            uint8_t ip[4];        ///< What IP to use (as fallback if DHCP).
            uint8_t mask[4];      ///< What mask to use (as fallback if DHCP).
            uint16_t stream_port; ///< Preferred stream port for the data logging.
            uint8_t mac[8];       ///< Used MAC address.

        } network;

    } config;

    /**
     * @brief Store the config about linking to other config pages.
     *
     */
    struct __attribute__((packed)) {

        uint32_t advanced_config_page; ///< Second configuration page, if at all.

    } links;

    /*
     * Backtrace statuses
     */
    struct __attribute__((packed)) {
        uint32_t entry[MAX_BACKTRACE_ENTRY]; ///< An array of entries to the backtrace.
    } backtrace_entry;

    uint32_t checksum; ///< checksum to ensure the page is well formed.

} SETTINGS_0;