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
int scpi_ese(char *args, void *context);
int scpi_esr_r(char *args, void *context);
int scpi_idn_r(char *args, void *context);
int scpi_opc_r(char *args, void *context);
int scpi_opc(char *args, void *context);
int scpi_opt(char *args, void *context);
int scpi_rst(char *args, void *context);
int scpi_sre_r(char *args, void *context);
int scpi_sre(char *args, void *context);
int scpi_stb_r(char *args, void *context);
int scpi_tst_r(char *args, void *context);
int scpi_wai(char *args, void *context);

// Custom commands
int scpi_actions_get_r(char *args, void *context);
int scpi_actions_set(char *args, void *context);
int scpi_actions_reset(char *args, void *context);

int scpi_analog_input_r(char *args, void *context);
int scpi_analog_output(char *args, void *context);
int scpi_analog_temp_r(char *args, void *context);

int scpi_conf_load(char *args, void *context);
int scpi_conf_volt_r(char *args, void *context);
int scpi_conf_volt(char *args, void *context);

int scpi_file_cd(char *args, void *context);
int scpi_file_load(char *args, void *context);
int scpi_file_ls(char *args, void *context);
int scpi_file_mkdir(char *args, void *context);
int scpi_file_pwd(char *args, void *context);

int scpi_hard_can_r(char *args, void *context);
int scpi_hard_can(char *args, void *context);
int scpi_hard_i2c_r(char *args, void *context);
int scpi_hard_i2c(char *args, void *context);
int scpi_hard_spi_r(char *args, void *context);
int scpi_hard_spi(char *args, void *context);
int scpi_hard_usart_r(char *args, void *context);
int scpi_hard_usart(char *args, void *context);

int scpi_log_subscribe(char *args, void *context);
int scpi_log_unsubscribe(char *args, void *context);
int scpi_log_list(char *args, void *context);

int scpi_prog_connect(char *args, void *context);
int scpi_prog_detect(char *args, void *context);
int scpi_prog_device(char *args, void *context);
int scpi_prog_dump(char *args, void *context);
int scpi_prog_flash(char *args, void *context);
int scpi_prog_read(char *args, void *context);
int scpi_prog_status(char *args, void *context);
int scpi_prog_verify(char *args, void *context);

int scpi_scan_can_r(char *args, void *context);
int scpi_scan_i2c_r(char *args, void *context);
int scpi_scan_spi_r(char *args, void *context);
int scpi_scan_usart_r(char *args, void *context);

int scpi_seq_add(char *args, void *context);
int scpi_seq_get_r(char *args, void *context);
int scpi_seq_new(char *args, void *context);
int scpi_seq_run(char *args, void *context);

int scpi_spy_can(char *args, void *context);
int scpi_spy_i2c(char *args, void *context);
int scpi_spy_spi(char *args, void *context);
int scpi_spy_usart(char *args, void *context);

#ifdef __cplusplus
}
#endif