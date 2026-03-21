/**
 * @file    HardwareProbeManager.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the base locking mechanism for the hardware probes as a manager class to handle them.
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
// HAL
#include "stm32h5xx_hal.h"
#include "stm32h5xx_ll_spi.h"
#include "stm32h5xx_ll_usart.h"

// RTOS
#include "tx_api.h"

// ======================================================================
//                               ENUMS
// ======================================================================
/*
 * Using mask enable to differentiate how we did initialize the probe, and thus, make the 
 * code standard. Like, I can pass only the SPIM handle, and some modes will be disabled.
 */
enum class HardwareProbeType {
    NONE = 0x00,
    ICSP = 0x01,
    JTAG = 0x02,
    cJTAG = 0x04,
    SWD = 0x08,
    SPI = 0x10,
    SWDO = 0x28 // SWD + SWO
};

/*
 * Define the direction of the transfer for each hardware probe type.
 */
enum class TransferDirection {
    TX_ONLY,
    RX_ONLY,
    TX_RX
};

// ======================================================================
//                               CLASS
// ======================================================================
class HardwareProbeManager {
    private:
        // Set the DMA trigger threadshold
        static constexpr uint32_t DMA_THRESHOLD = 256; // bits.

        static constexpr uint8_t PACKET_SIZE = 16; // bits. Unit size.
        static constexpr uint8_t MIN_PACKET_SIZE = 4; // bits. Minimum unit size for the SPI probe, as it can only handle 4-bit packets.

        // Mutex to ensure integrity of hardware configs
        TX_MUTEX peripheral_lock;

        // Store the current mode
        HardwareProbeType active_probe;
        uint32_t enabled_probes;

        // Peripherals handles
        SPI_HandleTypeDef* spim;
        SPI_HandleTypeDef* spis;
        UART_HandleTypeDef* serial;

    public:
        /*
         * Constructor
         */
        // Full featured
        explicit  HardwareProbeManager(SPI_HandleTypeDef* spim, SPI_HandleTypeDef* spis, UART_HandleTypeDef* serial);

        // Ligthweight constructors
        explicit HardwareProbeManager(SPI_HandleTypeDef* spim);
        explicit HardwareProbeManager(SPI_HandleTypeDef* spim, SPI_HandleTypeDef* spis);
        explicit HardwareProbeManager(SPI_HandleTypeDef* spim, UART_HandleTypeDef* serial);

        

        /*
         * Destructor
         */
        ~HardwareProbeManager();

        /*
         * Mutex API
         */
        bool lock();
        bool unlock();

        /*
         * Configuration API
         */
        bool configure(HardwareProbeType probe_type);
        bool reset();

        /*
         * XFER API
         */
        /**
         * Compute the ideal transfer parameters for a given bit count.
         * @param bit_count The total number of bits to transfer.
         * @param xfer_count Pointer to store the number of full transfers.
         * @param xfer_size Pointer to store the size of each full transfer.
         * @param last_xfer_size Pointer to store the size of the last transfer (bits number).
         */
        void get_xfer_size(uint32_t bit_count, uint32_t *xfer_count, uint32_t *xfer_size, uint32_t *last_xfer_size);

        void spi_master_xfer(   
            uint8_t* tx_buffer, 
            uint8_t *rx_buffer, 
            uint32_t packet_size, 
            uint32_t xfer_size, 
            TransferDirection direction
        );

        void spi_slave_xfer(
            uint8_t* tx_buffer, 
            uint8_t *rx_buffer, 
            uint32_t packet_size, 
            uint32_t xfer_size, 
            TransferDirection direction
        );

        void serial_receive(uint8_t* buffer, uint32_t *size);

        void reset_target();

        inline bool set_spi_speed(uint32_t bit_rate);

    private:
        inline void set_spi_size(uint32_t bit_count);
        inline void set_spim_direction(TransferDirection direction);
        
        /*
         * All the following function are calling the CubeMX init functions.
         * This ensure the user can change settings within the CubeMX,
         * and let all of that class handle the job, rather than maintaining
         * manual settings.
         */
        void configure_SPI();
        void configure_SWD();
        void configure_cJTAG();
        void configure_JTAG();
        void configure_SWDO();
        void configure_ICSP();

        void reset_SPI();
        void reset_SWD();
        void reset_cJTAG();
        void reset_JTAG();
        void reset_SWDO();
        void reset_ICSP();

};