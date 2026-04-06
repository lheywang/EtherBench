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
// Parameter config
enum class ParamType { Text, Number, Bool, Selection };
enum class ParamAttributes { READ_WRITE, READ, WRITE };

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
    QString key;                      //! The key name of the parameter.
    QVariant value;                   //! The actual value of the parameter.
    QVariant defaultValue;            //! The default loaded value.
    QString label;                    //! The label of the text prompt near it.
    QStringList options; //! The list of options, only used for ParamType::Selection
    QString group;       //! the related group. Unused for now.
    QVariant minValue;   //! The minimal value to be set.
    QVariant maxValue;   //! The maximal value to be set.
    QString regex;       //! A regex expression to validate (or not) the input field.
    QString description; //! When hovering the settings.
    ParamAttributes access = ParamAttributes::READ_WRITE; //! Define access rights.

    /*
     * Utility function
     */
    bool isValid(const QVariant &newValue) const {

        // If we're read only --> Set to false. User can't edit.
        if (access == ParamAttributes::READ)
            return false;

        // Apply selection based on filters
        switch (type) {
        case ParamType::Number: {
            double val = newValue.toDouble();

            if ((minValue.isValid()) && (maxValue.isValid()))
                return (val >= minValue.toDouble()) && (val <= maxValue.toDouble());

            return true;
            break;
        }

        case ParamType::Selection: {
            return options.contains(newValue.toString());
            break;
        }

        default:
            break;
        }

        // If nothing worked, apply the regex.
        if (!regex.isEmpty()) {
            QRegularExpression re(regex);
            return re.match(newValue.toString()).hasMatch();
        }

        // Default return
        return true;
    }
};

} // namespace EtherBench::Models