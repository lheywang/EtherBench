/**
 * @file    dataCast.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define how we do cast the data.
 * @version 0.1
 * @date    2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <services/dataCast.hpp>
#include <services/dataCastTypes.hpp>

// Qt
#include <QString>

// STD
#include <vector>

// =============================================================
// CLASS
// =============================================================

namespace EtherBench::Services {

bool dataCast::cast(std::vector<uint8_t> input, dataCastResult &output) { return true; }

} // namespace EtherBench::Services