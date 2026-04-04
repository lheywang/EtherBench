/**
 * @file    parameterRegistry.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief
 * @version 0.1
 * @date 2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <models/parameterRegistry.hpp>

// Local libraries
#include <models/parameterStruct.hpp>

// Qt
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QVariant>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Models {

/*
 * Constructor and destructors
 */
ParameterRegistry::ParameterRegistry(QObject *parent) : QObject(parent) {}

/*
 * Instance access
 */
ParameterRegistry &ParameterRegistry::instance() {
    static ParameterRegistry inst;
    return inst;
}

/*
 * Basic IO
 */
void ParameterRegistry::registerParam(const QString &key, const Parameter param) {
    m_parameters[key] = param;
}

QVariant ParameterRegistry::value(const QString &key) const {
    return m_parameters.value(key).value;
}
bool ParameterRegistry::setValue(const QString &key, const QVariant &val) {
    if (m_parameters[key].isValid(val)) {
        m_parameters[key].value = val;
        return true;
    }
    return false;
}

QStringList ParameterRegistry::allKeys() const { return m_parameters.keys(); }
const Parameter &ParameterRegistry::get(const QString &key) const {
    auto it = m_parameters.constFind(key);

    if (it == m_parameters.constEnd()) {
        throw std::out_of_range(
            QString("Cannot find key in list : %1").arg(key).toStdString());
    }

    return it.value();
}

/*
 * Param init
 */
void ParameterRegistry::initParams() {

    // Register app version
    registerParam(
        "info/version",
        Parameter{
            .type = ParamType::Text,
            .key = "app version",
            .value = "1.0.0",
            .defaultValue = "0.0.0",
            .label = "App version",
            .options = {},
            .group = "",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Application versiion",
            .access = ParamAttributes::READ});

    // Register the common settings
    addInterface("device/interface/ethernet/", InterfaceType::ETH);
    addInterface("device/interface/usb/", InterfaceType::USB);
    registerParam(
        "device/interface/connection",
        Parameter{
            .type = ParamType::Selection,
            .key = "connection",
            .value = "Auto",
            .defaultValue = "Auto",
            .label = "Connection",
            .options = {"Auto", "IP", "USB"},
            .group = "device",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description =
                "Change the preferred connection method. When Auto, both are used.",
            .access = ParamAttributes::READ_WRITE});

    addPaths("paths/");

    // Register some board settings
    addBoard("probe/board/");
    addProgrammer("probe/programmer/");

    // Register the IO
    addAnalogIO("probe/analog/adc0/", AnalogType::ADC);
    addAnalogIO("probe/analog/adc1/", AnalogType::ADC);
    addAnalogIO("probe/analog/dac/", AnalogType::DAC);

    addHardwareIO("probe/interface/usart0/", HardwareType::USART);
    addHardwareIO("probe/interface/usart1/", HardwareType::USART);
    addHardwareIO("probe/interface/i2c/", HardwareType::I2C);
    addHardwareIO("probe/interface/spi/", HardwareType::SPI);
    addHardwareIO("probe/interface/can/", HardwareType::CAN);
    addHardwareIO("probe/interface/clock/", HardwareType::CLOCK);
}

void ParameterRegistry::addHardwareIO(QString prefix, HardwareType type) {

    // Just add the correct keys
    switch (type) {

    case HardwareType::I2C: {
        registerParam(
            prefix + "mode",
            Parameter{
                .type = ParamType::Selection,
                .key = "mode",
                .value = "Standard",
                .defaultValue = "Standard",
                .label = "I2C Mode",
                .options = {"Standard", "Fast", "Fast plus"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the I2C operating mode.",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "address_width",
            Parameter{
                .type = ParamType::Selection,
                .key = "address_width",
                .value = "7 bits",
                .defaultValue = "7 bits",
                .label = "Address size",
                .options = {"7 bits", "10 bits"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the I2C address size",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "slave_address",
            Parameter{
                .type = ParamType::Number,
                .key = "slave_address",
                .value = "0x11",
                .defaultValue = "0x11",
                .label = "I2C Slave address",
                .options = {},
                .group = "interface",
                .minValue = 0x00,
                .maxValue = 0xFF,
                .regex = "",
                .description = "Change the slave I2C address. Used only when actively "
                               "reading from it. Make sure to not set invalid values, as "
                               "theses are possible (may be required), but not in the "
                               "spec (start from 0x10 and go to 0xF0).",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case HardwareType::SPI: {
        registerParam(
            prefix + "baudrate",
            Parameter{
                .type = ParamType::Number,
                .key = "baudrate",
                .value = "8000000",
                .defaultValue = "8000000",
                .label = "Baudrate",
                .options = {},
                .group = "interface",
                .minValue = 1000000,
                .maxValue = 31250000,
                .regex = "",
                .description = "Change the SPI Baudrate",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "mode",
            Parameter{
                .type = ParamType::Selection,
                .key = "mode",
                .value = "MODE 1",
                .defaultValue = "MODE 1",
                .label = "Mode",
                .options = {"MODE 0", "MODE 1", "MODE 2", "MODE 3"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the SPI Mode",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "size",
            Parameter{
                .type = ParamType::Number,
                .key = "size",
                .value = "8",
                .defaultValue = "8",
                .label = "Transfer size",
                .options = {},
                .group = "interface",
                .minValue = 4,
                .maxValue = 32,
                .regex = "",
                .description = "Change the SPI transfer size",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "data_direction",
            Parameter{
                .type = ParamType::Selection,
                .key = "sweep_speed",
                .value = "MSB",
                .defaultValue = "MSB",
                .label = "Data reading direction",
                .options = {"MSB", "LSB"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the data reading direction",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "data_format",
            Parameter{
                .type = ParamType::Selection,
                .key = "sweep_speed",
                .value = "Motorola",
                .defaultValue = "Motorola",
                .label = "Data format",
                .options = {"Motorola", "TI"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the SPI data format",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "slave_selection",
            Parameter{
                .type = ParamType::Bool,
                .key = "slave_selection",
                .value = "Enabled",
                .defaultValue = "Normal",
                .label = "Slave selection",
                .options = {},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Enable the slave select action.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case HardwareType::USART: {
        registerParam(
            prefix + "baudrate",
            Parameter{
                .type = ParamType::Number,
                .key = "baudrate",
                .value = "115200",
                .defaultValue = "115200",
                .label = "Baudrate",
                .options = {},
                .group = "interface",
                .minValue = 4800,
                .maxValue = 15000000,
                .regex = "",
                .description = "Change the used USART baudrate",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "parity",
            Parameter{
                .type = ParamType::Selection,
                .key = "parity",
                .value = "None",
                .defaultValue = "None",
                .label = "Parity mode",
                .options = {"None", "Odd", "Even"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the USART parity mode",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "stop_bits",
            Parameter{
                .type = ParamType::Number,
                .key = "stop_bits",
                .value = "1",
                .defaultValue = "1",
                .label = "Stop bits",
                .options = {},
                .group = "interface",
                .minValue = 1,
                .maxValue = 2,
                .regex = "",
                .description = "Change the number of stop bits",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "width",
            Parameter{
                .type = ParamType::Number,
                .key = "width",
                .value = "8",
                .defaultValue = "8",
                .label = "Data width",
                .options = {},
                .group = "interface",
                .minValue = 7,
                .maxValue = 9,
                .regex = "",
                .description = "Change the data size on the USART Bus",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "flow_control",
            Parameter{
                .type = ParamType::Selection,
                .key = "flow_control",
                .value = "None",
                .defaultValue = "None",
                .label = "Flow control",
                .options = {"None", "Hardware", "Software"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the flow control used on the USART bus.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case HardwareType::CAN: {
        registerParam(
            prefix + "frame_format",
            Parameter{
                .type = ParamType::Selection,
                .key = "frame_format",
                .value = "Classic",
                .defaultValue = "Classic",
                .label = "CAN Frame format",
                .options =
                    {"Classic",
                     "FD (with bitrate switch)",
                     "FD (without bitrate switch)"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the scanning speed of the integrated ADC. Slower "
                               "mean higher precision.",
                .access = ParamAttributes::READ_WRITE});

        registerParam(
            prefix + "mode",
            Parameter{
                .type = ParamType::Selection,
                .key = "mode",
                .value = "Normal",
                .defaultValue = "Normal",
                .label = "Sweep speed",
                .options =
                    {"Normal",
                     "Restricted",
                     "Bus monitoring",
                     "Internal loopback",
                     "External loopback"},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the CAN operating mode.",
                .access = ParamAttributes::READ_WRITE});

        registerParam(
            prefix + "quantum",
            Parameter{
                .type = ParamType::Number,
                .key = "quantum",
                .value = "64",
                .defaultValue = "64",
                .label = "Quantum size",
                .options = {},
                .group = "interface",
                .minValue = 1,
                .maxValue = 1024,
                .regex = "",
                .description = "Change the CAN quantum size",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case HardwareType::CLOCK: {
        registerParam(
            prefix + "enable",
            Parameter{
                .type = ParamType::Bool,
                .key = "enable",
                .value = "0",
                .defaultValue = "0",
                .label = "Enable clock output",
                .options = {},
                .group = "interface",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description =
                    "Enable the clock output. May be required for some devices.",
                .access = ParamAttributes::READ_WRITE});
        registerParam(
            prefix + "speed",
            Parameter{
                .type = ParamType::Selection,
                .key = "speed",
                .value = "8 MHz",
                .defaultValue = "8 MHz",
                .label = "Clock speed",
                .options =
                    {"32.768 kHz",
                     "50 kHz",
                     "100 kHz",
                     "125 kHz",
                     "250 kHz",
                     "500 kHz",
                     "1 MHz",
                     "2 MHz",
                     "4 MHz",
                     "8 MHz",
                     "10 MHz",
                     "12 MHz",
                     "16 MHz",
                     "20 MHz",
                     "25 MHz",
                     "30 MHz",
                     "32 MHz",
                     "40 MHz",
                     "48 MHz"},
                .group = "analog",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description =
                    "Set the clock output frequency, over a broad range of values.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    }
}

void ParameterRegistry::addAnalogIO(QString prefix, AnalogType type) {

    // Just add the correct keys
    switch (type) {

    case AnalogType::ADC: {
        registerParam(
            prefix + "sweepspeed",
            Parameter{
                .type = ParamType::Selection,
                .key = "sweep_speed",
                .value = "Normal",
                .defaultValue = "Normal",
                .label = "Sweep speed",
                .options = {"Slow", "Normal", "Fast", "Very Fast"},
                .group = "analog",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description = "Change the scanning speed of the integrated ADC. Slower "
                               "mean higher precision.",
                .access = ParamAttributes::READ_WRITE});

        registerParam(
            prefix + "resolution",
            Parameter{
                .type = ParamType::Selection,
                .key = "resolution",
                .value = "12",
                .defaultValue = "12",
                .label = "Resolution",
                .options =
                    {"6", "8", "10", "12", "14 (oversampling)", "16 (oversampling)"},
                .group = "analog",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "",
                .description =
                    "Change the resolution of the analog ADC. The lowest enable a faster "
                    "operation (at a reliable value, nothing block you from requesting "
                    "16 bits at very fast rate). The higher resolutions are done in "
                    "software, by averaging enough samples.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case AnalogType::DAC: {
        registerParam(
            prefix + "value",
            Parameter{
                .type = ParamType::Number,
                .key = "value",
                .value = "1.65",
                .defaultValue = "1.65",
                .label = "Value",
                .options = {},
                .group = "analog",
                .minValue = 0,
                .maxValue = 5.5,
                .regex = "",
                .description =
                    "Change the default, on boot DAC value. May be changed when running "
                    "a sequence, without propagating changes up to here.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    }
}

void ParameterRegistry::addProgrammer(QString prefix) {

    registerParam(
        prefix + "bus",
        Parameter{
            .type = ParamType::Selection,
            .key = "bus",
            .value = "SWD",
            .defaultValue = "SWD",
            .label = "Bus",
            .options = {"SWD", "JATG", "ICSP", "SPI"},
            .group = "programmer",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Change the default used programmer bus.",
            .access = ParamAttributes::READ_WRITE});

    registerParam(
        prefix + "speed",
        Parameter{
            .type = ParamType::Selection,
            .key = "speed",
            .value = "4000 kHz",
            .defaultValue = "4000 kHz",
            .label = "Speed",
            .options =
                {"100 kHz",
                 "250 kHz",
                 "500 kHz",
                 "1000 kHz",
                 "2000 kHz",
                 "4000 kHz",
                 "8000 kHz",
                 "10 000 kHz",
                 "12 000 kHz",
                 "15 000 kHz",
                 "20 000 kHz"},
            .group = "programmer",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Change the programmer speed. Higher speed are indeed faster, "
                           "but are more likely subject to interferences. This is the "
                           "first setting to tweak if the connection is not stable.",
            .access = ParamAttributes::READ_WRITE});

    registerParam(
        prefix + "reset",
        Parameter{
            .type = ParamType::Selection,
            .key = "reset",
            .value = "Connect under reset",
            .defaultValue = "Connect under reset",
            .label = "Connection method",
            .options = {"Connect under reset", "No reset", "Software reset"},
            .group = "programmer",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Change the programmer connection behavior.",
            .access = ParamAttributes::READ_WRITE});
}

void ParameterRegistry::addBoard(QString prefix) {

    registerParam(
        prefix + "voltage",
        Parameter{
            .type = ParamType::Selection,
            .key = "voltage",
            .value = "3.3V",
            .defaultValue = "3.3V",
            .label = "IO Voltage",
            .options = {"1.2V", "1.65V", "1.8V", "2.5V", "3.3V", "4V", "5V", "5.5V"},
            .group = "board",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Change the used IO voltage level. Enable a broad range of "
                           "devices to be wired without adapters.",
            .access = ParamAttributes::READ_WRITE});
}

void ParameterRegistry::addInterface(QString prefix, InterfaceType type) {

    // Just add the correct keys
    switch (type) {

    case InterfaceType::USB: {
        registerParam(
            prefix + "port",
            Parameter{
                .type = ParamType::Number,
                .key = "port",
                .value = "1",
                .defaultValue = "1",
                .label = "COM port",
                .options = {},
                .group = "device",
                .minValue = 0,
                .maxValue = 0xFF,
                .regex = "",
                .description = "Change the used COM port to communicate with the device.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    case InterfaceType::ETH: {
        registerParam(
            prefix + "address",
            Parameter{
                .type = ParamType::Text,
                .key = "address",
                .value = "192.168.1.10",
                .defaultValue = "192.168.1.10",
                .label = "IP address",
                .options = {"Slow", "Normal", "Fast", "Very Fast"},
                .group = "device",
                .minValue = 0,
                .maxValue = 0xFFFFFFFF,
                .regex = "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|["
                         "01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25["
                         "0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$",
                .description = "Change the default used IP address of the device. If not "
                               "found, and mode is AUTO, a querry over USB will be done.",
                .access = ParamAttributes::READ_WRITE});

        registerParam(
            prefix + "port",
            Parameter{
                .type = ParamType::Number,
                .key = "port",
                .value = "0",
                .defaultValue = "0",
                .label = "Port",
                .options = {},
                .group = "device",
                .minValue = 0,
                .maxValue = 65535,
                .regex = "",
                .description = "Change the used port for input streaming. Let 0 to leave "
                               "the OS choose it.",
                .access = ParamAttributes::READ_WRITE});
        break;
    }
    }
}

void ParameterRegistry::addPaths(QString prefix) {
    registerParam(
        prefix + "decoders",
        Parameter{
            .type = ParamType::Text,
            .key = "decoders",
            .value = "decoders/",
            .defaultValue = "decoders/",
            .label = "decoders",
            .options = {},
            .group = "path",
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = "Change the emplacement where we shall read the decoders. May "
                           "be usefull to share them over a network drive.",
            .access = ParamAttributes::READ_WRITE});
}

/*
 * File IO
 */
bool ParameterRegistry::loadFromFile(QString path) { return true; }

bool ParameterRegistry::writeToFile(QString path) { return true; }

} // namespace EtherBench::Models