/**
 * @file    DAP_commands.hpp
 * @author  your name (you@domain.com)
 * @brief   Define the DAP commands that are usefull.
 *          Full documentation here :
 *          https://arm-software.github.io/CMSIS-DAP/latest/group__DAP__Commands__gr.html
 * @version 0.1
 * @date    2026-03-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              CONSTEXPR
// ======================================================================
/*
 * Markers
 */
constexpr char DAP_VENDOR[] = "";  // Empty. Will use the USB ones.
constexpr char DAP_PRODUCT[] = ""; // Empty. Will use the USB ones.
constexpr char DAP_SER_NUM[] = ""; // Empty. Will use the USB ones.

constexpr char DAP_FW_VER[] = "2.1.2";

constexpr char DAP_INFO_TARGET_VENDOR[] = "";
constexpr char DAP_INFO_TARGET_BOARD[] = "";
constexpr char DAP_INFO_TARGET_NAME[] = "";
constexpr char DAP_INFO_TARGET_VERSION[] = "";

/*
 * Defaults settings
 */
constexpr uint32_t DAP_DEFAULT_MODE = 0x01;        // SWD
constexpr uint32_t DAP_DEFAULT_CLOCK_HZ = 1000000; // 1 MHz

// ======================================================================
//                              ENUMS
// ======================================================================

/*
 * Global commands
 */
enum class DAP_COMMANDS {
    Info = 0x00,
    HostStatus = 0x01,
    Connect = 0x02,
    Disconnect = 0x03,
    TransferConfigure = 0x04,
    Transfer = 0x05,
    TransferBlock = 0x06,
    TransferAbort = 0x07,
    WriteAbort = 0x08,
    Delay = 0x09,
    ResetTarget = 0x0A,
    SWJ_Pins = 0x10,
    SWJ_Clock = 0x11,
    SWJ_Sequence = 0x12,
    SWD_Configure = 0x13,
    SWD_Sequence = 0x1D,
    JTAG_Sequence = 0x14,
    JTAG_Configure = 0x15,
    JTAG_IDCODE = 0x16,
    SWO_Transport = 0x17,
    SWO_Mode = 0x18,
    SWO_Baudrate = 0x19,
    SWO_Control = 0x1A,
    SWO_Status = 0x1B,
    SWO_ExtendedStatus = 0x1E,
    SWO_Data = 0x1C,
    UART_Transport = 0x1F,
    UART_Configure = 0x20,
    UART_Control = 0x22,
    UART_Status = 0x23,
    UART_Transfer = 0x21,
    QueueCommands = 0x7E,
    ExecuteCommands = 0x7F

    // TODO : Add SPI Support here, but it is not in the CMSIS-DAP specification, so we
    // need to implement it ourselves.
};

enum class DAP_RESULTS_CODES { OK = 0x00, ERROR = 0xFF };

/*
 * DAP_INFO Sub-commands
 */
enum class DAP_INFO_COMMANDS {
    VendorName = 0x01,
    ProductName = 0x02,
    SerialNumber = 0x03,
    CMSISVersion = 0x04,
    TargetVendor = 0x05,
    TargetBoard = 0x06,
    TargetName = 0x07,
    TargetVersion = 0x08,
    FirmwareVersion = 0x09,
    Capabilities = 0xF0,
    TimerParameters = 0xF1,
    UARTReceiveBufferSize = 0xFB,
    UARTTransmitBufferSize = 0xFC,
    SWOTraceBufferSize = 0xFD,
    PacketCount = 0xFE,
    PacketSize = 0xFF
};

enum class DAP_CAPABILITIES {
    SWD = 0x01,
    JTAG = 0x02,
    SWO_UART = 0x04,
    SWO_MANCHESTER = 0x08,
    ATOMIC_COMMANDS = 0x10,
    TEST_TIMER = 0x20,
    SWO_STREAMING = 0x40,
    UART = 0x80,
    USB_COM_PORT = 0x01
};

enum class DAP_STATUS_FLAGS { CONNECT = 0x00, RUNNING = 0x01 };

enum class DAP_CONNECT_FLAGS { DEFAULT = 0x00, SWD = 0x01, JTAG = 0x02 };
