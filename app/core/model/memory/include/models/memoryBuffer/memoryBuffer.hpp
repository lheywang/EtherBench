/**
 * @file    memoryBuffer.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the base memoryBuffer to be used.
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
// Qt
#include <QObject>
#include <QReadWriteLock>
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

class MemoryBuffer : public QObject {

    Q_OBJECT

  public:
    /*
     * Constructor and destructors
     */
    explicit MemoryBuffer(QObject *parent = nullptr);
    virtual ~MemoryBuffer() = default;

    /*
     * Essential io functions, to be overriden by the child class
     */
    /**
     * @brief Return a selection of some bytes
     *
     * @param offset The absolute offset in the buffer.
     * @param size The number of bytes we need to fetch.
     *
     * @warning The function could return all of it's data. The value is capped to 4 GB,
     * but... still huge.
     *
     * @return std::vector<uint8_t> The data
     */
    virtual std::vector<uint8_t> get(uint64_t offset, uint64_t size) = 0;

    /**
     * @brief Return a single byte of data
     *
     * @param offset The absolute offset in the buffer.
     *
     * @return uint8_t
     */
    virtual uint8_t at(uint64_t offset) const = 0;

    /**
     * @brief Append some data at the end of the current buffer.
     *
     * @param data The data to be added.
     *
     * @return true Data was correctly added.
     * @return false Data was not correctly added.
     */
    virtual bool append(std::vector<uint8_t> &data) = 0;

    /**
     * @brief Set some data over a known range. If the data isn't known, it'll be
     *        allocated.
     *
     * @param offset The starting offset to be set.
     * @param data The data to be configured.
     *
     * @warning The function could allocate up to the max size. The value is capped to 4
     * GB, but... still huge.
     *
     * @return true The data was set (or allocated).
     * @return false The data was not set.
     */
    virtual bool set(uint64_t offset, std::vector<uint8_t> &data) = 0;

    /**
     * @brief Return the current number of bytes in the buffer.
     *
     * @return uint32_t
     */
    virtual uint64_t size() = 0;

    /*
     * Utilities
     */
    /**
     * @brief Erase a block of memory (set to 0x00). Internally call the @ref set
     * function.
     *
     * @param offset The starting offset of memory.
     * @param size The number of bytes to be erased.
     *
     * @return true The bytes where erased.
     * @return false The bytes could not be erased.
     */
    bool erase(uint64_t offset, uint64_t size);

    /*
     * File IO functions. Theses aren't overriden, to ensure a coherency, if the case we
     * change the header or something like that.
     */
    /**
     * @brief
     *
     * @param path
     */
    virtual void loadFromFile(QString path);

    /**
     * @brief
     *
     * @param path
     */
    virtual void writeToFile(QString path);

  private:
    /*
     * Variables
     */
    mutable QReadWriteLock m_lock;
};
} // namespace EtherBench::Models
