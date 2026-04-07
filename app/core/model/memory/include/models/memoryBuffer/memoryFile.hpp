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
#include <QFile>
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
// Define how much memory we shall add each time
constexpr uint64_t
get_new_buffer_size(uint64_t currentSize, uint64_t request = (1ULL << 20)) {
    return currentSize + request;
}

// =============================================================
// CLASS
// =============================================================

/**
 * @brief Define the MemoryFile class, which assure the standard file IO editor.
 *
 * @warning While it's design made the usage of file IO efficient, this class isn't
 *          designed to handle as fast as other the operations such as append / set.
 *
 */
class MemoryFile : public MemoryBuffer {

    Q_OBJECT

  public:
    /*
     * Constructor and destructors
     */
    explicit MemoryFile(QObject *parent = nullptr);
    explicit MemoryFile(QString filePath = "", QObject *parent = nullptr);
    ~MemoryFile() override;

    /*
     * Overrides
     */
    std::vector<uint8_t> get(uint64_t offset, uint64_t size) override;
    bool append(std::vector<uint8_t> &data) override;
    bool set(uint64_t offset, std::vector<uint8_t> &data) override;
    uint64_t size() override;
    uint8_t at(uint64_t offset) const override;

    /*
     * Additional overides
     */
    void loadFromFile(QString path) override;
    void writeToFile(QString path = "") override;

  private:
    /*
     * Variables
     */
    QFile memfile;
    QString filename;

    uint8_t *buffer;
    uint64_t buffer_size;
    uint64_t head;

    /*
     * Functions
     */
    bool resize(uint64_t request);
    bool unmap();
};

} // namespace EtherBench::Models
