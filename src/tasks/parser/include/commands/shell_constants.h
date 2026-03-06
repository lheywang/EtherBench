/**
 * @file    shell_constants.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define standard shell constants, to be parsed allong the other arguments
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              DEFINES
// ======================================================================
// BUSES
#define SHELL_HARDWARE_BASE 10
#define SHELL_I2C (SHELL_HARDWARE_BASE + 0)
#define SHELL_SPI (SHELL_HARDWARE_BASE + 1)
#define SHELL_UART (SHELL_HARDWARE_BASE + 2)
#define SHELL_CAN (SHELL_HARDWARE_BASE + 3)
#define SHELL_VOLTAGE (SHELL_HARDWARE_BASE + 4)
#define SHELL_TEMPERATURE (SHELL_HARDWARE_BASE + 5)

// PROGRAMMATION
#define SHELL_PROG_BASE 20
#define SHELL_CONNECT (SHELL_PROG_BASE + 0)
#define SHELL_DETECT (SHELL_PROG_BASE + 1)
#define SHELL_VERIFY (SHELL_PROG_BASE + 2)
#define SHELL_STATUS (SHELL_PROG_BASE + 3)
#define SHELL_DEVICE (SHELL_PROG_BASE + 4)
#define SHELL_DUMP (SHELL_PROG_BASE + 6)

// LOGGER
#define SHELL_LOGGER_BASE 40
#define SHELL_LOGGER_SUBSCRIBE (SHELL_LOGGER_BASE + 0)
#define SHELL_LOGGER_UNSUBSCRIBE (SHELL_LOGGER_BASE + 1)

// GENERIC ACTIONS
#define SHELL_GENERIC_BASE 100
#define SHELL_LOAD (SHELL_GENERIC_BASE + 0)
#define SHELL_SET (SHELL_GENERIC_BASE + 1)
#define SHELL_RESET (SHELL_GENERIC_BASE + 2)
#define SHELL_NEW (SHELL_GENERIC_BASE + 3)
#define SHELL_ADD (SHELL_GENERIC_BASE + 4)
#define SHELL_READ (SHELL_GENERIC_BASE + 5)
#define SHELL_WRITE (SHELL_GENERIC_BASE + 6)
#define SHELL_RUN (SHELL_GENERIC_BASE + 7)
#define SHELL_GET (SHELL_GENERIC_BASE + 8)

#ifdef __cplusplus
}
#endif