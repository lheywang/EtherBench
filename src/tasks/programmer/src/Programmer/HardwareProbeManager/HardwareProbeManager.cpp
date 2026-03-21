/**
 * @file    HardwareProbeManager.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the base locking mechanism for the hardware probes as a manager class to handle them.
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
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"

// HAL
#include "stm32h5xx_hal.h"
#include "stm32h5xx_ll_spi.h"
#include "stm32h5xx_ll_usart.h"

// RTOS
#include "tx_api.h"

// STD
#include <cmath>

// ======================================================================
//                            CLASS IMPL.
// ======================================================================

/*
 * CONSTRUCTOR & DESTRUCTOR
 */

HardwareProbeManager::HardwareProbeManager(SPI_HandleTypeDef* spim, SPI_HandleTypeDef* spis, UART_HandleTypeDef* serial){
    // Initialize the mutex
    char mutex_name[] = {"Peripheral Lock"};
    tx_mutex_create(&this->peripheral_lock, mutex_name, TX_NO_INHERIT);

    // Set the peripherals handles
    this->spim = spim;
    this->spis = spis;
    this->serial = serial;

    // Set the enabled probes bitmask
    this->enabled_probes = 0;

    this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::SPI);
    this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::SWD);
    this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::cJTAG);
    this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::ICSP);

    if (spis) {
        this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::JTAG);
    }
    if (serial) {
        this->enabled_probes |= static_cast<uint32_t>(HardwareProbeType::SWDO);
    }

    return;
}

HardwareProbeManager::HardwareProbeManager(SPI_HandleTypeDef* spim) : HardwareProbeManager(spim, nullptr, nullptr) {}

HardwareProbeManager::HardwareProbeManager(SPI_HandleTypeDef* spim, SPI_HandleTypeDef* spis) : HardwareProbeManager(spim, spis, nullptr) {}

HardwareProbeManager::HardwareProbeManager(SPI_HandleTypeDef* spim, UART_HandleTypeDef* serial) : HardwareProbeManager(spim, nullptr, serial){}

HardwareProbeManager::~HardwareProbeManager() {

    // First, reset everything : 
    this->reset();

    // Unlock the mutex
    this->unlock();
}

/*
 * MUTEX API
 */
bool HardwareProbeManager::lock() {
    tx_mutex_get(&this->peripheral_lock, TX_WAIT_FOREVER);
    return true;
}

bool HardwareProbeManager::unlock() {
    tx_mutex_put(&this->peripheral_lock);
    return true;
}

/*
 * CONFIGURATION API
 */

bool HardwareProbeManager::configure(HardwareProbeType probe_type) {

    /*
     * Check if there's something to do : 
     */
    if (this->active_probe == probe_type) {
        return true;
    }

    /* 
     * If not, check if the requested probe is enabled, and if so, 
     * configure it.
     */

    if ((static_cast<uint32_t>(probe_type) & this->enabled_probes) != static_cast<uint32_t>(probe_type)) {
        return false;
    }

    /*
     * Reset the current configuration, and set the new one.
     */
    this->reset();

    switch (probe_type) {

        case HardwareProbeType::SPI:
            this->configure_SPI();
            this->active_probe = HardwareProbeType::SPI;
            break;

        case HardwareProbeType::SWD:
            this->configure_SWD();      
            this->active_probe = HardwareProbeType::SWD;
            break;

        case HardwareProbeType::cJTAG:
            this->configure_cJTAG();
            this->active_probe = HardwareProbeType::cJTAG;
            break;

        case HardwareProbeType::JTAG:
            this->configure_JTAG();
            this->active_probe = HardwareProbeType::JTAG;
            break;

        case HardwareProbeType::SWDO:
            this->configure_SWDO();
            this->active_probe = HardwareProbeType::SWDO;
            break;

        case HardwareProbeType::ICSP:
            this->configure_ICSP();
            this->active_probe = HardwareProbeType::ICSP;
            break;

        default:
            return false;
    }

    return true;
}

bool HardwareProbeManager::reset() {

    switch (this->active_probe) {

        case HardwareProbeType::SPI:
            this->reset_SPI();
            break;

        case HardwareProbeType::SWD: 
            this->reset_SWD();
            break;  
            
        case HardwareProbeType::cJTAG:
            this->reset_cJTAG();
            break;  

        case HardwareProbeType::JTAG:
            this->reset_JTAG();
            break;  

        case HardwareProbeType::SWDO:       
            this->reset_SWDO();
            break;  

        case HardwareProbeType::ICSP:
            this->reset_ICSP();     

        default:
            break;  
    }

    return true;
}

/*
 * XFER API
 */

void HardwareProbeManager::get_xfer_size(uint32_t bit_count, uint32_t *xfer_count, uint32_t *xfer_size, uint32_t *last_xfer_size) {

    /*
     * First, get some parameters, with a modulo and a division.
     *
     * This will give us the number of full packets, and a remainder
     * that must be send as a last transfer.
     */
    *last_xfer_size = bit_count % PACKET_SIZE; 
    *xfer_count = (uint32_t)((bit_count - *last_xfer_size) / PACKET_SIZE);
    *xfer_size = PACKET_SIZE;

    /*
     * Ensure no transfers are going to be smaller than the minimum size 
     * the SPI peripheral can handle.
     */
    if (*last_xfer_size < MIN_PACKET_SIZE) {
        if (*xfer_count > 0) {
            *xfer_count -= 1;
            *last_xfer_size += PACKET_SIZE;
        }
    }
       
    return;
}

void HardwareProbeManager::spi_master_xfer(   
            uint8_t* tx_buffer, 
            uint8_t *rx_buffer, 
            uint32_t packet_size, 
            uint32_t xfer_size, 
            TransferDirection direction
        ) {

        }

void HardwareProbeManager::spi_slave_xfer(
            uint8_t* tx_buffer, 
            uint8_t *rx_buffer, 
            uint32_t packet_size, 
            uint32_t xfer_size, 
            TransferDirection direction
        ) {

        }

void HardwareProbeManager::serial_receive(uint8_t* buffer, uint32_t *size) {

}

inline void HardwareProbeManager::set_spi_size(uint32_t bit_count) {
    return;
}

inline void HardwareProbeManager::set_spim_direction(TransferDirection direction) {

}

inline bool HardwareProbeManager::set_spi_speed(uint32_t bit_rate)
{
    
}

void HardwareProbeManager::configure_SPI(){

}
void HardwareProbeManager::configure_SWD(){

}
void HardwareProbeManager::configure_cJTAG(){

}
void HardwareProbeManager::configure_JTAG()
{

}
void HardwareProbeManager::configure_SWDO(){

}
void HardwareProbeManager::configure_ICSP(){

}