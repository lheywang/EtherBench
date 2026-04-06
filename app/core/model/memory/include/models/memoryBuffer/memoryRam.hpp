/**
 * @file    memoryRam.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief
 * @version 0.1
 * @date 2026-04-05
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
// INCLUDES
// =============================================================
namespace EtherBench::Models {

// =============================================================
// CONSTEXPR
// =============================================================
// Define the unit size of allocated blocks
constexpr uint64_t ALLOC_SIZE = 1ULL << 12; // About 4 kB of data.

// =============================================================
// CLASS
// =============================================================

/**
 * @brief The default memory handler. Use pages of @ref ALLOC_SIZE bytes as unit size.
 *        Only limited by your computer ram. Ensure we can store basically anything, while
 *        ensuring a usage at an @ref ALLOC_SIZE near.
 *
 */
class MemoryRam : public MemoryBuffer {

    Q_OBJECT

  public:
    /*
     * Constructor and destructors
     */
    explicit MemoryRam(QObject *parent = nullptr);
    ~MemoryRam() override;

    /*
     * Overrides
     */
    std::vector<uint8_t> get(uint64_t offset, uint64_t size) override;
    bool append(std::vector<uint8_t> &data) override;
    bool set(uint64_t offset, std::vector<uint8_t> &data) override;
    uint64_t size() override;
    uint8_t at(uint64_t offset) const override;

  private:
    /*
     * Variables
     */
    std::vector<std::array<uint8_t, ALLOC_SIZE> *> buffer;
    uint64_t buffer_size;

    /*
     * Functions
     */
    bool allocatePage();
};

} // namespace EtherBench::Models