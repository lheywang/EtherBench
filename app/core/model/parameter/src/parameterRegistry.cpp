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
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QMutexLocker>
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
ParameterRegistry::ParameterRegistry(QObject *parent) : QObject(parent) { initParams(); }

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
        m_dirty = true;
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

void ParameterRegistry::resetToDefault() {

    for (auto it = m_parameters.begin(); it != m_parameters.end(); ++it) {
        it.value().value = it.value().defaultValue;
    }

    writeToFile("settings.ebs", true);
    m_dirty = false;
    qInfo() << "Resetted all settings to the default value";
}

/*
 * Param init
 */
void ParameterRegistry::initParams() {

    /*
     * APP
     */
    register_text(
        "device/info/",
        "version",
        "1.0.0",
        "App version",
        "info",
        "",
        "Application version",
        ParamAttributes::READ);

    // Register the common settings
    addInterface("device/interface/ethernet/", InterfaceType::ETH);
    addInterface("device/interface/usb/", InterfaceType::USB);

    register_selection(
        "device/interface/",
        "connection",
        "Auto",
        "Connection method",
        "device",
        {"Auto", "IP", "USB"},
        "Change the preferred connection method. When Auto, both are used.");

    addPaths("device/paths/");

    // Register memory settings
    addMemory("device/memory/");

    // Register some board settings
    addBoard("probe/board/");
    addProgrammer("probe/programmer/");

    /*
     * PROBE
     */
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
        register_selection(
            prefix,
            "mode",
            "Standard",
            "I2C Mode",
            "interface",
            {"Standard", "Fast", "Fast plus"},
            "Change the I2C operating mode.");

        register_selection(
            prefix,
            "address_width",
            "7 bits",
            "Address size",
            "interface",
            {"7 bits", "10 bits"},
            "Change the I2C address size");

        register_number(
            prefix,
            "slave_address",
            "0x11",
            "I2C Slave address",
            "interface",
            0x00,
            0xFF,
            "Change the slave I2C address. Used only when actively "
            "reading from it. Make sure to not set invalid values, as "
            "theses are possible (may be required), but not in the "
            "spec (start from 0x10 and go to 0xF0).");
        break;
    }
    case HardwareType::SPI: {
        register_number(
            prefix,
            "baudrate",
            "8000000",
            "Baudrate",
            "interface",
            1000000,
            31250000,
            "Change the SPI Baudrate");

        register_selection(
            prefix,
            "mode",
            "MODE 1",
            "Mode",
            "interface",
            {"MODE 0", "MODE 1", "MODE 2", "MODE 3"},
            "Change the SPI Mode");

        register_number(
            prefix,
            "size",
            "8",
            "Transfer size",
            "interface",
            4,
            32,
            "Change the SPI transfer size");

        register_selection(
            prefix,
            "data_direction",
            "MSB",
            "Data reading direction",
            "interface",
            {"MSB", "LSB"},
            "Change the data reading direction");

        register_selection(
            prefix,
            "data_format",
            "Motorola",
            "Data format",
            "interface",
            {"Motorola", "TI"},
            "Change the SPI data format");

        register_bool(
            prefix,
            "slave_selection",
            "True",
            "Slave select",
            "interface",
            "Enable the slave select action.");

        break;
    }
    case HardwareType::USART: {

        register_number(
            prefix,
            "baudrate",
            "115200",
            "Baudrate",
            "interface",
            4800,
            15000000,
            "Change the used USART baudrate");

        register_selection(
            prefix,
            "parity",
            "None",
            "Parity",
            "interface",
            {"None", "Odd", "Even"},
            "Change the USART parity mode");

        register_selection(
            prefix,
            "stop_bits",
            "1",
            "Stop bits",
            "interface",
            {"1", "2"},
            "Change the number of stop bits");

        register_selection(
            prefix,
            "width",
            "8",
            "Data width",
            "interface",
            {"7", "8", "9"},
            "Change the data size on the USART Bus");

        register_selection(
            prefix,
            "flow_control",
            "None",
            "Flow control",
            "interface",
            {"None", "Hardware", "Software"},
            "Change the flow control used on the USART bus.");

        break;
    }
    case HardwareType::CAN: {

        register_selection(
            prefix,
            "frame_format",
            "Classic",
            "CAN Frame format",
            "interface",
            {"Classic", "FD (with bitrate switch)", "FD (without bitrate switch)"},
            "Change the CAN frame format.");

        register_selection(
            prefix,
            "mode",
            "Normal",
            "CAN operation mode",
            "interface",
            {"Normal",
             "Restricted",
             "Bus monitoring",
             "Internal loopback",
             "External loopback"},
            "Change the CAN operating mode.");

        register_number(
            prefix,
            "quantum",
            "64",
            "Quantum size",
            "interface",
            1,
            1024,
            "Change the CAN quantum size");

        break;
    }
    case HardwareType::CLOCK: {

        register_bool(
            prefix,
            "enable",
            "False",
            "Enable clock output",
            "interface",
            "Enable the clock output. May be required for some devices.");

        register_selection(
            prefix,
            "speed",
            "8 MHz",
            "Clock speed",
            "interface",
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
            "Set the clock output frequency, over a broad range of values.");

        break;
    }
    }
}

void ParameterRegistry::addAnalogIO(QString prefix, AnalogType type) {

    // Just add the correct keys
    switch (type) {

    case AnalogType::ADC: {

        register_selection(
            prefix,
            "sweepspeed",
            "Normal",
            "Sweep speed",
            "analog",
            {"Slow", "Normal", "Fast", "Very Fast"},
            "Change the scanning speed of the integrated ADC. Slower "
            "mean higher precision.");

        register_selection(
            prefix,
            "resolution",
            "12 bits",
            "Resolution",
            "analog",
            {"6", "8", "10", "12", "14 (oversampling)", "16 (oversampling)"},
            "Change the resolution of the analog ADC. The lowest enable a faster "
            "operation (at a reliable value, nothing block you from requesting "
            "16 bits at very fast rate). The higher resolutions are done in "
            "software, by averaging enough samples.");

        break;
    }
    case AnalogType::DAC: {

        register_number(
            prefix,
            "value",
            "1.65",
            "Value",
            "analog",
            0,
            5.5,
            "Change the default, on boot DAC value. May be changed when running "
            "a sequence, without propagating changes up to here.");

        break;
    }
    }
}

void ParameterRegistry::addProgrammer(QString prefix) {

    register_selection(
        prefix,
        "bus",
        "SWD",
        "Bus",
        "programmer",
        {"SWD", "JATG", "ICSP", "SPI"},
        "Change the default used programmer bus.");

    register_selection(
        prefix,
        "speed",
        "4000 kHz",
        "Speed",
        "programmer",
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
        "Change the programmer speed. Higher speed are indeed faster, "
        "but are more likely subject to interferences. This is the "
        "first setting to tweak if the connection is not stable.");

    register_selection(
        prefix,
        "reset",
        "Connect under reset",
        "Connection method",
        "programmer",
        {"Connect under reset", "No reset", "Software reset"},
        "Change the programmer connection behavior.");
}

void ParameterRegistry::addBoard(QString prefix) {

    register_selection(
        prefix,
        "voltage",
        "3.3V",
        "IO Voltage level",
        "board",
        {"1.2V", "1.65V", "1.8V", "2.5V", "3.3V", "4V", "5V", "5.5V"},
        "Change the used IO voltage level. Enable a broad range of "
        "devices to be wired without adapters.");
}

void ParameterRegistry::addInterface(QString prefix, InterfaceType type) {

    // Just add the correct keys
    switch (type) {

    case InterfaceType::USB: {

        register_number(
            prefix,
            "port",
            "1",
            "COM / tty",
            "device",
            1,
            255,
            "Change the used COM port to communicate with the device.");
        break;
    }
    case InterfaceType::ETH: {

        register_text(
            prefix,
            "address",
            "192.168.1.10",
            "IP address (of device)",
            "device",
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|["
            "01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25["
            "0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$",
            "Change the default used IP address of the device. If not "
            "found, and mode is AUTO, a querry over USB will be done.");

        register_text(
            prefix,
            "target",
            "0.0.0.0",
            "IP address (stream target)",
            "device",
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|["
            "01]?[0-9][0-9]?).(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?).(25["
            "0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$",
            "Change the streaming destination of the device. By default (0.0.0.0), it's "
            "the current device IP. May be usefull to process / logs over the network to "
            "another device.");

        register_number(
            prefix,
            "port",
            "0",
            "Port",
            "device",
            0,
            65535,
            "Change the used port for input streaming. Let 0 to leave "
            "the OS choose it.");

        break;
    }
    }
}

void ParameterRegistry::addPaths(QString prefix) {

    register_text(
        prefix,
        "decoders",
        "decoders/",
        "Decoder path",
        "paths",
        "",
        "Change the emplacement where we shall read the decoders. May "
        "be usefull to share them over a network drive.");
}

void ParameterRegistry::addMemory(QString prefix) {

    QStringList options = {"Classic buffer", "Circular buffer", "File buffer"};
    QStringList defaults = {
        "Classic buffer",
        "Classic buffer",
        "Classic buffer",
        "Classic buffer",
        "Circular buffer",
        "Circular buffer",
        "File buffer",
        "File buffer"};

    int id = 1;
    for (auto &value : defaults) {
        register_selection(
            prefix,
            "slot" + QString::number(id),
            value,
            "Slot " + QString::number(id) + " memory type",
            "memory",
            options,
            "Configure the memory type for the buffer X. Classic can hold up to 16 EB "
            "(yes, really). Ideal for logging before further exploration. Circular has a "
            "fixed size of about 32 MB, which is way smaller. Ideal for fast logging, "
            "but be aware that it'll be overwritten with time. File buffer is different, "
            "it isn't designed for fast logging, but rather open a file into a slot, and "
            "use it as reference for further operations, such as comparaison. Write "
            "operations are supported, but this may induce latencies on slower storages "
            "types.");
        id += 1;
    }

    register_selection(
        prefix,
        "circ_size",
        "1 MB",
        "Circular buffer size (bytes)",
        "memory",
        {"1 MB",
         "2 MB",
         "4 MB",
         "8 MB",
         "16 MB",
         "32 MB",
         "64 MB",
         "128 MB",
         "256 MB",
         "512 MB"},
        "Change the buffer size used within the circular buffers. Warning : This "
        "settings is only updated after a program restart, cannot be changed in live.");
}

/*
 * File IO
 */
bool ParameterRegistry::loadFromFile(QString path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "Unable to open config file :" << path;
        return false;
    }

    QByteArray data = file.readAll();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (doc.isNull()) {
        qCritical()
            << "Failed to parse config. Ensure the syntax is a valid JSON one ... :"
            << error.errorString();
        return false;
    }

    QJsonObject root = doc.object();
    QMutexLocker locker(&m_mutex);

    for (auto it = root.begin(); it != root.end(); ++it) {
        QString key = it.key();

        if (m_parameters.contains(key)) {
            QVariant newValue = it.value().toVariant();

            m_parameters[key].value = newValue;
            qDebug() << "Loaded parameter (" << key << ") : " << newValue;

        } else {
            qWarning() << "Unknown key in file (was ignored):" << key;
        }
    }

    m_dirty = false;
    qInfo() << "Loaded settings from file";

    return true;
}

bool ParameterRegistry::writeToFile(QString path, bool forceWrite) {

    // if nothing was modified...
    if ((m_dirty == false) && (forceWrite == false))
        return true;

    QJsonObject root;
    QMutexLocker locker(&m_mutex);

    for (auto it = m_parameters.begin(); it != m_parameters.end(); ++it) {
        if (it.value().value != it.value().defaultValue) {
            root.insert(it.key(), QJsonValue::fromVariant(it.value().value));
        }
    }

    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));

    m_dirty = false; // As we performed the write, changes are updated.
    return true;
}

/*
 * Register helpers
 */
void ParameterRegistry::register_text(
    QString prefix,
    QString key,
    QString value,
    QString label,
    QString group,
    QString regex,
    QString description,
    ParamAttributes attr) {
    registerParam(
        prefix + key,
        Parameter{
            .type = ParamType::Text,
            .key = key,
            .value = value,
            .defaultValue = value,
            .label = label,
            .options = {},
            .group = group,
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = regex,
            .description = description,
            .access = attr});
}

void ParameterRegistry::register_number(
    QString prefix,
    QString key,
    QString value,
    QString label,
    QString group,
    QVariant minimum,
    QVariant maximum,
    QString description,
    ParamAttributes attr) {
    registerParam(
        prefix + key,
        Parameter{
            .type = ParamType::Number,
            .key = key,
            .value = value,
            .defaultValue = value,
            .label = label,
            .options = {},
            .group = group,
            .minValue = minimum,
            .maxValue = maximum,
            .regex = "",
            .description = description,
            .access = attr});
}

void ParameterRegistry::register_selection(
    QString prefix,
    QString key,
    QString value,
    QString label,
    QString group,
    QStringList options,
    QString description,
    ParamAttributes attr) {
    registerParam(
        prefix + key,
        Parameter{
            .type = ParamType::Selection,
            .key = key,
            .value = value,
            .defaultValue = value,
            .label = label,
            .options = options,
            .group = group,
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = description,
            .access = attr});
}

void ParameterRegistry::register_bool(
    QString prefix,
    QString key,
    QString value,
    QString label,
    QString group,
    QString description,
    ParamAttributes attr) {
    registerParam(
        prefix + key,
        Parameter{
            .type = ParamType::Bool,
            .key = key,
            .value = value,
            .defaultValue = value,
            .label = label,
            .options = {},
            .group = group,
            .minValue = 0,
            .maxValue = 0xFFFFFFFF,
            .regex = "",
            .description = description,
            .access = attr});
}

} // namespace EtherBench::Models