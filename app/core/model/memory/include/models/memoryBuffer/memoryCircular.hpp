/**
 * @file    memoryFile.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement a file based memoryBuffer, to be able to edit and see binary files
 * locally.
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
#include <models/memoryBuffer/memoryBuffer.hpp>

// Qt
#include <QObject>
#include <QString>

// STD
#include <array>
#include <vector>

// =============================================================
// NAMESPACE
// =============================================================
namespace EtherBench::Models {

// =============================================================
// CONSTEXPR
// =============================================================
// Define the max size of this class
constexpr uint64_t MAX_CIRCULAR_SIZE = 1ULL << 25; // 32 MB of data.

// =============================================================
// CLASS
// =============================================================

/**
 * @brief Define the MemoryCircular class. A nice helper to ensure "infinite" logs over
 *        time, without ever filling your ram. The only drawback is that it's designed as
 *        fixed limit, and will overwrite previous data.
 *
 */
class MemoryCircular : public MemoryBuffer {

    Q_OBJECT

  public:
    /*
     * Constructor and destructors
     */
    explicit MemoryCircular(QObject *parent = nullptr);
    ~MemoryCircular() override;

    /*
     * Overrides
     */
    std::vector<uint8_t> get(uint64_t offset, uint64_t size) override;
    bool append(std::vector<uint8_t> &data) override;
    bool set(uint64_t offset, std::vector<uint8_t> &data) override;
    uint64_t size() override;
    uint8_t at(uint64_t offset) const override;

  private:
};

} // namespace EtherBench::Models
