/**
 * @file    cJTAGProbe.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the cJTAG probing methods.
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
#include "Programmer/Probes/cJTAGProbe/cJTAGProbe.hpp"

// Local library
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"

// ======================================================================
//                               CLASS
// ======================================================================
/*
 * Constructors & destructors
 */
cJTAGProbe::cJTAGProbe(HardwareProbeManager *manager) {
    this->probe_manager = manager;
    return;
}

/*
 * Overrides for the probe class
 */
bool cJTAGProbe::connect() { return true; }

bool cJTAGProbe::disconnect() { return true; }

uint32_t
cJTAGProbe::transfer(const uint8_t size, const uint8_t *request, uint8_t *response) {
    return true;
}

bool cJTAGProbe::set_clock_frequency(uint32_t frequency_hz) {
    return this->probe_manager->set_spi_speed(frequency_hz);
}