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
#include <QByteArray>
#include <QDataStream>
#include <QStringList>

// STD
#include <vector>

namespace EtherBench::Services {

// =============================================================
// CLASS
// =============================================================

class dataCast {

  public:
    /*
     * Constructor and destructors
     */
    dataCast();
    ~dataCast();

    /*
     * Actions functions
     */

    /**
     * @brief Perform the casting from a vector of bytes into a struct of all the strings,
     * ready to be printed !
     *
     * @param input The input vector of bytes.
     * @param endianness Does we need to perform an endianess swap ?
     */
    dataCastResult cast(
        std::vector<uint8_t> input,
        QDataStream::ByteOrder endianness = QDataStream::LittleEndian);

    dataCastResult *last_cast();

  private:
    /*
     * Private templates and utility
     */
    template <typename T>
    QStringList vec2type(const QByteArray &data, QDataStream::ByteOrder order) {
        QStringList list;
        QDataStream ds(data);
        ds.setByteOrder(order);

        int count = data.size() / sizeof(T);
        for (int i = 0; i < count; ++i) {
            T val;
            ds >> val;
            list << QString::number(val);
        }
        return list;
    }

    uint32_t
    raw24bval(uint8_t byte0, uint8_t byte1, uint8_t byte2, QDataStream::ByteOrder order);

    /*
     * Private caster helpers
     */
    QStringList vec2binary(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2octal(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2ascii(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2utf8(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2utf16(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2u24(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2i24(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2u128(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2i128(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2ts32(const QByteArray &data, QDataStream::ByteOrder order);
    QStringList vec2ts64(const QByteArray &data, QDataStream::ByteOrder order);

    /*
     * Private variables
     */
    dataCastResult result;
    size_t byte_size;
};

} // namespace EtherBench::Services