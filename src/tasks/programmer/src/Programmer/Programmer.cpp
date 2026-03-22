/**
 * @file    Programmer.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the global class for the programmer tool.
 * @version 0.1
 * @date    2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
// Header
#include "Programmer/Programmer.hpp"

// Local library
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"
#include "Programmer/Probes/Probe.hpp"


#include "Programmer/Probes/ICSPProbe/ICSPProbe.hpp"
#include "Programmer/Probes/JTAGProbe/JTAGProbe.hpp"
#include "Programmer/Probes/SPIProbe/SPIProbe.hpp"
#include "Programmer/Probes/SWDProbe/SWDProbe.hpp"
#include "Programmer/Probes/cJTAGProbe/cJTAGProbe.hpp"


#include "Programmer/DAP_commands.hpp"

// HAL
#include "stm32h5xx_hal.h"

// STD
#include <cstdint>

// ======================================================================
//                               CLASS
// ======================================================================
/*
 * Constructors & destructors
 */
Programmer::Programmer(
    SPI_HandleTypeDef *spim_handle,
    SPI_HandleTypeDef *spis_handle,
    UART_HandleTypeDef *uart_handle)
    : probe_manager(spim_handle, spis_handle, uart_handle),
      cTJTAG_probe(&this->probe_manager), ICSP_probe(&this->probe_manager),
      JTAG_probe(&this->probe_manager), SPI_probe(&this->probe_manager),
      SWD_probe(&this->probe_manager) {
    this->current_probe = nullptr;
    this->clock_frequency_hz = 0;
    this->target_connected = false;
    return;
};

Programmer::Programmer(SPI_HandleTypeDef *spim_handle)
    : Programmer(spim_handle, nullptr, nullptr) {};

Programmer::Programmer(SPI_HandleTypeDef *spim_handle, SPI_HandleTypeDef *spis_handle)
    : Programmer(spim_handle, spis_handle, nullptr) {};

Programmer::Programmer(SPI_HandleTypeDef *spim_handle, UART_HandleTypeDef *uart_handle)
    : Programmer(spim_handle, nullptr, uart_handle) {};

Programmer::~Programmer() {
    this->probe_manager.reset();
    return;
}

/*
 * Programmer operations
 */
uint32_t Programmer::process_commands(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
};

uint32_t Programmer::process_dap_command(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    // Ensure we fetched enough data
    if (request_len == 0) {
        return 0;
    }

    DAP_COMMANDS command_id = static_cast<DAP_COMMANDS>(request[0]);

    switch (command_id) {

    /*
     * Handle standard DAP commands
     */
    case DAP_COMMANDS::Info:
        this->handle_info(request, request_len, response);
        break;
    case DAP_COMMANDS::HostStatus:
        this->handle_host_status(request, request_len, response);
        break;
    case DAP_COMMANDS::Connect:
        this->handle_connect(request, request_len, response);
        break;
    case DAP_COMMANDS::Disconnect:
        this->handle_disconnect(request, request_len, response);
        break;
    case DAP_COMMANDS::WriteAbort:
        this->handle_write_abort(request, request_len, response);
        break;
    case DAP_COMMANDS::Delay:
        this->handle_delay(request, request_len, response);
        break;
    case DAP_COMMANDS::ResetTarget:
        this->handle_reset_target(request, request_len, response);
        break;

    case DAP_COMMANDS::TransferConfigure:
        break;
    case DAP_COMMANDS::Transfer:
        break;
    case DAP_COMMANDS::TransferBlock:
        break;
    case DAP_COMMANDS::TransferAbort:
        break;

    case DAP_COMMANDS::SWJ_Pins:
        break;
    case DAP_COMMANDS::SWJ_Clock:
        break;
    case DAP_COMMANDS::SWJ_Sequence:
        break;
    case DAP_COMMANDS::SWD_Configure:
        break;
    case DAP_COMMANDS::SWD_Sequence:
        break;
    case DAP_COMMANDS::JTAG_Sequence:
        break;
    case DAP_COMMANDS::JTAG_Configure:
        break;
    case DAP_COMMANDS::JTAG_IDCODE:
        break;
    case DAP_COMMANDS::SWO_Transport:
        break;
    case DAP_COMMANDS::SWO_Mode:
        break;
    case DAP_COMMANDS::SWO_Baudrate:
        break;
    case DAP_COMMANDS::SWO_Control:
        break;
    case DAP_COMMANDS::SWO_Status:
        break;
    case DAP_COMMANDS::SWO_ExtendedStatus:
        break;
    case DAP_COMMANDS::SWO_Data:
        break;
    case DAP_COMMANDS::UART_Transport:
        break;
    case DAP_COMMANDS::UART_Configure:
        break;
    case DAP_COMMANDS::UART_Control:
        break;
    case DAP_COMMANDS::UART_Status:
        break;
    case DAP_COMMANDS::UART_Transfer:
        break;
    case DAP_COMMANDS::QueueCommands:
        break;
    case DAP_COMMANDS::ExecuteCommands:
        break;
    }

    return 0;
}

uint32_t
Programmer::handle_info(const uint8_t *request, uint32_t request_len, uint8_t *response) {

}

uint32_t Programmer::handle_host_status(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}

uint32_t Programmer::handle_connect(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}

uint32_t Programmer::handle_disconnect(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}

uint32_t Programmer::handle_write_abort(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}

uint32_t Programmer::handle_delay(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}

uint32_t Programmer::handle_reset_target(
    const uint8_t *request, uint32_t request_len, uint8_t *response) {
    return 0;
}
