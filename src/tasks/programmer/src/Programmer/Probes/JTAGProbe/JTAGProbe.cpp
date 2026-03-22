/**
 * @file    JTAGProbe.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the JTAG probing methods.
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
#include "Programmer/Probes/JTAGProbe/JTAGProbe.hpp"

// Local library
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"

// ======================================================================
//                               CLASS
// ======================================================================
/*
 * Constructors & destructors
 */
JTAGProbe::JTAGProbe(HardwareProbeManager *manager) {
    this->probe_manager = manager;
    return;
}

/*
 * Overrides for the probe class
 */
bool JTAGProbe::connect() { return true; }

bool JTAGProbe::disconnect() { return true; }

uint32_t
JTAGProbe::transfer(const uint8_t size, const uint8_t *request, uint8_t *response) {
    return true;
}

bool JTAGProbe::set_clock_frequency(uint32_t frequency_hz) {
    return this->probe_manager->set_spi_speed(frequency_hz);
}