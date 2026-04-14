/**
 * @file    masterCasterTypes.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the shared types of the casts results
 * @version 0.1
 * @date    2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Qt
#include <QString>
#include <QStringList>
#include <QVariant>

// STD
#include <vector>

namespace EtherBench::Models {
// =============================================================
// STRUCTS
// =============================================================
/**
 * @brief Define a basic result key, stored as a key : value/for/example, and a value
 *        : 12. Will be used when creating the treeview results !
 *
 */
struct CastResult {
    QString key;
    QString value;
};

/**
 * @brief Define a complex struct, fetched after the "end of cast" signal is emitted.
 *
 * Store basic informations (conversionEndianess, and mainMessage), to be used, but, also
 * a vector of CastResult structs. Theses store the individual keys !
 */
struct CastData {

    QString conversionEndianness;
    QString mainMessage;

    std::vector<CastResult> results;
};

} // namespace EtherBench::Models