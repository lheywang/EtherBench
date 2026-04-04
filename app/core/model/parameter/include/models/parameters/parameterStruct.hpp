/**
 * @file    parameterStruct.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the parameter model, to store some config values.
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
// Qt
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace EtherBench::Models {

// =============================================================
// ENUMS
// =============================================================
enum class ParamType { Text, Number, Bool, Selection };

// =============================================================
// STRUCTS
// =============================================================
/**
 * @brief Store a setting within and it's associated config.
 *
 */
struct Parameter {

    ParamType type = ParamType::Text; //! Define the type of the stored setting. Will
                                      //! ensure a consistent edit page.

    QString key;    //! The key name of the parameter.
    QVariant value; //! The actual value of the parameter.

    QString label;       //! The label of the text prompt near it.
    QStringList options; //! The list of options, only used for ParamType::Selection

    QString group;

    QVariant minValue; // The minimal value to be set. Unused if -1.
    QVariant maxValue; // The maximal value to be set. Unused if -1.
    QString regex;

    /*
     * Utility function
     */
    bool isValid(const QVariant &newValue) const {
        if (type == ParamType::Number) {
            int val = newValue.toInt();

            if ((minValue.isValid()) && (maxValue.isValid()))
                return (val >= minValue.toInt()) && (val <= maxValue.toInt());

            return true;
        }
        if (type == ParamType::Selection) {
            return options.contains(newValue.toString());
        }
        if (!regex.isEmpty()) {
            QRegularExpression re(regex);
            return re.match(newValue.toString()).hasMatch();
        }
        return true;
    }
};

class ParameterRegistry : public QObject {
    Q_OBJECT

  public:
    explicit ParameterRegistry(QObject *parent = nullptr);
    static ParameterRegistry &instance();

    void registerParam(
        const QString &key,
        const QVariant &defaultValue,
        const QString &label,
        ParamType type = ParamType::Text);

    QVariant value(const QString &key) const;
    bool setValue(const QString &key, const QVariant &val);

    QStringList allKeys() const;
    const Parameter &get(const QString &key) const;

  private:
    QMap<QString, Parameter> m_parameters;
};

} // namespace EtherBench::Models