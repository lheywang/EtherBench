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

    /*
     * Special functions
     */
    uint64_t head();

  private:
    /*
     * Variables
     */
    uint64_t buffer_size;
    uint64_t max_buffer_size;
    uint64_t max_page_count;
    uint64_t head_pos;
    uint64_t writes;

    std::vector<std::array<uint8_t, ALLOC_SIZE> *> buffer;

    /*
     * Functions
     */
    bool allocatePage();
};

} // namespace EtherBench::Models
