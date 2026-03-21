/**
 * @file    cJTAGProbe.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the cJTAG probing methods.
 * @version 0.1
 * @date    2026-03-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

// ======================================================================
//                              INCLUDE
// ======================================================================
// Local library
#include "Programmer/Probes/Probe.hpp"
#include "Programmer/HardwareProbeManager/HardwareProbeManager.hpp"

// STD
#include <cstdint>

// ======================================================================
//                               CLASS
// ======================================================================
class cJTAGProbe : public Probe {

    private:
        HardwareProbeManager* probe_manager;

    public:
        /*
         * Constructors & destructors
         */
        explicit cJTAGProbe(HardwareProbeManager* manager);

        /*
         * Overrides for the probe class
         */
        bool connect() override;
        bool disconnect() override; 
        uint32_t transfer(
            const uint8_t size,
            const uint8_t* request,
            uint8_t* response
        ) override; 
        bool set_clock_frequency(uint32_t frequency_hz) override;

        /*
         * Additional methods for cJTAGProbe
         */
};
