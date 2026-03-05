/**
 * @file    parser_scpi.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define known scpi commands
 * @version 0.1
 * @date 2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDE
// ======================================================================
#include <stdint.h>

// ======================================================================
//                              FUNCTIONS
// ======================================================================

// Standard SCPI
int scpi_cls(char *args, void *context);
int scpi_ese_r(char *args, void *context);

#ifdef __cplusplus
}
#endif