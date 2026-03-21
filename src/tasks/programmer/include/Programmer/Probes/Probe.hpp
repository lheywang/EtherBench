/**
 * @file    Probe.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the minimal function to be used for a probe.
 * @version 0.1
 * @date    2026-03-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

// ======================================================================
//                               INCLUDE
// ======================================================================
// STD
#include <cstdint>

// ======================================================================
//                               CLASS
// ======================================================================

/**
 * @brief Purely software interface for a probe, which defines the minimal function to be used for a probe.
 * 
 */
class Probe {

    public:
        /**
         * @brief Destroy the IProbeProtocol object
         */
        virtual ~Probe() = default;

        /**
         * @brief   Execute the connection process to the target device.
         * 
         * @return true     Target is connected.
         * @return false    Target is not connected.
         */
        virtual bool connect() = 0;

        /**
         * @brief   Execute the disconnection process to the target device.
         * 
         * @return true     Target is disconnected.
         * @return false    Target is not disconnected.
         */
        virtual bool disconnect() = 0;  

        /**
         * @brief   Perform a data transfer to the target device.
         * 
         * @param size      The size of the request data.
         * @param request   The data to be sent to the target device.
         * @param response  The buffer to store the response data from the target device.
         * @return uint32_t The number of received bytes.
         */
        virtual uint32_t transfer(
            const uint8_t size,
            const uint8_t* request,
            uint8_t* response
        ) = 0;

        /**
         * @brief   Set the clock frequency of the probe for communication with the target device.
         * 
         * @param frequency_hz  The desired clock frequency in hertz (Hz) for the probe's communication with the target device.
         */
        virtual bool set_clock_frequency(
            uint32_t frequency_hz
        ) = 0;
};
