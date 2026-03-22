/**
 * @file    Programmer.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the global class for the programmer tool.
 * @version 0.1
 * @date 2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              INCLUDE
// ======================================================================
// Local library
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"
#include "Programmer/Probes/Probe.hpp"


#include "Programmer/Probes/ICSPProbe/ICSPProbe.hpp"
#include "Programmer/Probes/JTAGProbe/JTAGProbe.hpp"
#include "Programmer/Probes/SPIProbe/SPIProbe.hpp"
#include "Programmer/Probes/SWDProbe/SWDProbe.hpp"
#include "Programmer/Probes/cJTAGProbe/cJTAGProbe.hpp"


// HAL
#include "stm32h5xx_hal.h"

// STD
#include <cstdint>

// ======================================================================
//                               CLASS
// ======================================================================
class Programmer {

  private:
    HardwareProbeManager probe_manager;

    cJTAGProbe cTJTAG_probe;
    ICSPProbe ICSP_probe;
    JTAGProbe JTAG_probe;
    SPIProbe SPI_probe;
    SWDProbe SWD_probe;

    Probe *current_probe;

    uint32_t clock_frequency_hz;
    bool target_connected;

  public:
    /*
     * Constructors & destructors
     */
    Programmer(
        SPI_HandleTypeDef *spim_handle,
        SPI_HandleTypeDef *spis_handle,
        UART_HandleTypeDef *uart_handle);

    Programmer(SPI_HandleTypeDef *spim_handle);

    Programmer(SPI_HandleTypeDef *spim_handle, SPI_HandleTypeDef *spis_handle);

    Programmer(SPI_HandleTypeDef *spim_handle, UART_HandleTypeDef *uart_handle);

    ~Programmer();

    /*
     * Programmer operations
     */
    /**
     * @brief   Process incoming commands.
     * Does support the CMSIS stacked commands feature, to use more
     * efficiently use the communication channel between the host
     * and the programmer.
     *
     * @param request The incoming command
     * @param request_len The length of the incoming command
     * @param response The response buffer
     *
     * @return The length of the response
     */
    uint32_t
    process_commands(const uint8_t *request, uint32_t request_len, uint8_t *response);

  private:
    uint32_t
    process_dap_command(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t handle_info(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_host_status(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_connect(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_disconnect(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_write_abort(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_delay(const uint8_t *request, uint32_t request_len, uint8_t *response);

    uint32_t
    handle_reset_target(const uint8_t *request, uint32_t request_len, uint8_t *response);
};