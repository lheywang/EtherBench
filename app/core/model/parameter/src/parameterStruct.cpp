/**
 * @file    parameterStruct.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief
 * @version 0.1
 * @date    2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <models/parameters/parameterStruct.hpp>

// Qt
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QVariant>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Models {

ParameterRegistry::ParameterRegistry(QObject *parent) : QObject(parent) {}

ParameterRegistry &ParameterRegistry::instance() {
    static ParameterRegistry inst;
    return inst;
}

void ParameterRegistry::registerParam(
    const QString &key,
    const QVariant &defaultValue,
    const QString &label,
    ParamType type) {
    Parameter p;
    p.key = key;
    p.value = defaultValue;
    p.label = label;
    p.type = type;
    m_parameters[key] = p;
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

} // namespace EtherBench::Models