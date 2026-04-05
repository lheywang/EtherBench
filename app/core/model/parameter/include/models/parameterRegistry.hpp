/**
 * @file    parameterRegistry.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Hold the registry of parameters
 * @version 0.1
 * @date    2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include "parameterStruct.hpp"

// Qt
#include <QMutex>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace EtherBench::Models {

// =============================================================
// ENUM
// =============================================================
// Registry config
enum class HardwareType { I2C, SPI, USART, CAN, CLOCK };
enum class InterfaceType { USB, ETH };
enum class AnalogType { ADC, DAC };

// =============================================================
// CLASS
// =============================================================
/**
 * @brief Hold the parameter map, as a flat array. Easier to access and handle.
 *
 */
class ParameterRegistry : public QObject {
    Q_OBJECT

  public:
    /*
     * Constructors and destructors
     */

    /**
     * @brief Return the handle to the parameter registry.
     *
     * @return ParameterRegistry&
     */
    static ParameterRegistry &instance();

    /**
     * @brief Add a new element to the current list
     *
     * @param key   The path of the new key ("/" indicate a shared path)
     * @param param The configuration of the new key
     */
    void registerParam(const QString &key, const Parameter param);

    QVariant value(const QString &key) const;
    bool setValue(const QString &key, const QVariant &val);

    /*
     * Init
     */
    /**
     * @brief Initialize the parameters as provided.
     */
    void initParams();

    /*
     * Key IO
     */
    /**
     * @brief Return a list of all known keys.
     *
     * @return QStringList
     */
    QStringList allKeys() const;

    /**
     * @brief Return the struct that correspond to a specific key.
     *
     * @param key
     * @return const Parameter&
     */
    const Parameter &get(const QString &key) const;

    /*
     * FileIO
     */
    /**
     * @brief Load the values from a file into the current key array.
     *
     * @param path The source file.
     * @return true Read went correct.
     * @return false Failed to read.
     */
    bool loadFromFile(QString path);

    /**
     * @brief Write the current config to a file.
     *
     * @param path The target file.
     * @return true Write went correct.
     * @return false Failed to write.
     */
    bool writeToFile(QString path);

  private:
    /*
     * Variables
     */
    QMap<QString, Parameter> m_parameters;
    QMutex m_mutex;
    bool m_dirty;

    /**
     * @brief Construct a new Parameter Registry object
     *
     * @param parent
     */
    explicit ParameterRegistry(QObject *parent = nullptr);

    /*
     * Private functions
     */

    /**
     * @brief Initialize a serial bus. Type specify which key are added.
     *
     * @param prefix The root of all settings.
     * @param type The type of added interface.
     */
    void addHardwareIO(QString prefix, HardwareType type);

    /**
     * @brief Initialize the analog part.
     *
     * @param prefix The root of all settings.
     * @param type The type of the added interface.
     */
    void addAnalogIO(QString prefix, AnalogType type);

    /**
     * @brief Initialize the programmer settings.
     *
     * @param prefix The root of all settings.
     */
    void addProgrammer(QString prefix);

    /**
     * @brief Initialize the board settings
     *
     * @param prefix The root of all settings.
     */
    void addBoard(QString prefix);

    /**
     * @brief Initialize the interface settings
     *
     * @param prefix The root of all settings.
     * @param type The type of interface
     */
    void addInterface(QString prefix, InterfaceType type);

    /**
     * @brief Initialize the path handling modules.
     *
     * @param prefix The root of all settings.
     */
    void addPaths(QString prefix);

    /*
     * Registering helpers
     */
    /*
     * Register a text parameter, cleaner than calling the whole
     * constructor.
     */
    void register_text(
        QString prefix,
        QString key,
        QString value,
        QString label,
        QString group,
        QString regex,
        QString description,
        ParamAttributes attr = ParamAttributes::READ_WRITE);

    void register_number(
        QString prefix,
        QString key,
        QString value,
        QString label,
        QString group,
        QVariant minimum,
        QVariant maximum,
        QString description,
        ParamAttributes attr = ParamAttributes::READ_WRITE);

    void register_selection(
        QString prefix,
        QString key,
        QString value,
        QString label,
        QString group,
        QStringList options,
        QString description,
        ParamAttributes attr = ParamAttributes::READ_WRITE);

    void register_bool(
        QString prefix,
        QString key,
        QString value,
        QString label,
        QString group,
        QString description,
        ParamAttributes attr = ParamAttributes::READ_WRITE);
};

} // namespace EtherBench::Models