/**
 * @file    dataCast.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the methods used to convert the data between the raw uint8_t byte
 *          input, and the different formats.
 * @version 0.1
 * @date    2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include <services/dataCastTypes.hpp>

// Qt
#include <QString>
#include <vector>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Services {

class dataCast {

  public:
    bool cast(std::vector<uint8_t> input, dataCastResult &output);

  private:
    dataCast() = delete;
};

} // namespace EtherBench::Services