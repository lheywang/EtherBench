/**
 * @file    memoryPool.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Hold the memory pool class, and handle the standard IO over it.
 * @version 0.1
 * @date    2026-04-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include <models/memoryBuffer/memoryBuffer.hpp>
#include <models/memoryBuffer/memoryCircular.hpp>
#include <models/memoryBuffer/memoryFile.hpp>
#include <models/memoryBuffer/memoryRam.hpp>

// Qt
#include <QObject>
#include <QString>

// STD
#include <array>
#include <vector>

namespace EtherBench::Models {

// =============================================================
// CONSTEXPR
// =============================================================

// =============================================================
// CLASS
// =============================================================
class MemoryPool : public QObject {

  public:
  private:
};

} // namespace EtherBench::Models