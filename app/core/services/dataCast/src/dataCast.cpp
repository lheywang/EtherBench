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

// Local libraries
#include <services/dataCastTypes.hpp>

// Qt
#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QStringList>
#include <QTimeZone>

// STD
#include <string>
#include <vector>

// =============================================================
// CLASS
// =============================================================

namespace EtherBench::Services {

dataCast::dataCast() {

    /*
     * Clear the struct
     */
    result.convertedAsLe = false;

    result.binary = {""};
    result.octal = {""};
    result.ascii = {""};
    result.utf8 = {""};
    result.utf16 = {""};
    result.u8 = {""};
    result.i8 = {""};
    result.u16 = {""};
    result.i16 = {""};
    result.u24 = {""};
    result.i24 = {""};
    result.u32 = {""};
    result.i32 = {""};
    result.u64 = {""};
    result.i64 = {""};
    result.u128 = {""};
    result.i128 = {""};
    result.f32 = {""};
    result.f64 = {""};
    result.ts32 = {""};
    result.ts64 = {""};

    /*
     * Others fields
     */
    byte_size = 0;
}

dataCast::~dataCast() {}

dataCastResult
dataCast::cast(std::vector<uint8_t> input, QDataStream::ByteOrder endianness) {

    /*
     * Call the different structs :
     */

    // Little endian result
    result.convertedAsLe = (endianness == QDataStream::LittleEndian) ? true : false;

    // Raw data (first byte only)
    result.binary = vec2binary(QByteArray(input), endianness);
    result.octal = vec2octal(QByteArray(input), endianness);

    // Text
    result.ascii = vec2ascii(QByteArray(input), endianness); // All data converted !
    result.utf8 = vec2utf8(QByteArray(input), endianness);
    result.utf16 = vec2utf16(QByteArray(input), endianness);

    // Standard integer types
    result.u8 = vec2type<quint8>(QByteArray(input), endianness);
    result.i8 = vec2type<qint8>(QByteArray(input), endianness);
    result.u16 = vec2type<quint16>(QByteArray(input), endianness);
    result.i16 = vec2type<qint16>(QByteArray(input), endianness);
    result.u24 = vec2u24(QByteArray(input), endianness);
    result.i24 = vec2i24(QByteArray(input), endianness);
    result.u32 = vec2type<quint32>(QByteArray(input), endianness);
    result.i32 = vec2type<qint32>(QByteArray(input), endianness);
    result.u64 = vec2type<quint64>(QByteArray(input), endianness);
    result.i64 = vec2type<qint64>(QByteArray(input), endianness);
    result.u128 = vec2u128(QByteArray(input), endianness);
    result.i128 = vec2i128(QByteArray(input), endianness);

    // Standard float types
    // QStringList f16;
    // QStringList f16b;
    result.f32 = vec2type<float>(QByteArray(input), endianness);
    result.f64 = vec2type<double>(QByteArray(input), endianness);
    // QStringList f128;

    // Others data types
    result.ts32 = vec2ts32(QByteArray(input), endianness);
    result.ts64 = vec2ts64(QByteArray(input), endianness);

    /*
     * Exit and return the struct.
     */
    return result;
}

dataCastResult *dataCast::last_cast() { return &result; }

QStringList dataCast::vec2binary(const QByteArray &data, QDataStream::ByteOrder order) {
    Q_UNUSED(order);
    QStringList list;
    for (int i = 0; i < data.size() && i < 8; ++i) {
        list << QString("%1").arg((uint8_t)data[i], 8, 2, QChar('0'));
    }
    return list;
}

QStringList dataCast::vec2octal(const QByteArray &data, QDataStream::ByteOrder order) {
    Q_UNUSED(order);
    QStringList list;
    for (int i = 0; i < data.size() && i < 8; ++i) {
        list << QString("0%1").arg((uint8_t)data[i], 3, 8, QChar('0'));
    }
    return list;
}

QStringList dataCast::vec2ascii(const QByteArray &data, QDataStream::ByteOrder order) {
    Q_UNUSED(order);
    QString result = "";
    for (char c : data) {
        if (c >= 32 && c <= 126)
            result += c;
        else
            result += '.';
    }
    return {result};
}

QStringList dataCast::vec2utf8(const QByteArray &data, QDataStream::ByteOrder order) {
    Q_UNUSED(order);
    return {QString::fromUtf8(data)};
}

QStringList dataCast::vec2utf16(const QByteArray &data, QDataStream::ByteOrder order) {
    if (data.size() < 2)
        return {};

    if (order == QDataStream::BigEndian) {
        return {QString::fromUtf16(
            reinterpret_cast<const char16_t *>(data.data()), data.size() / 2)};
    } else {
        return {QString::fromWCharArray(
            reinterpret_cast<const wchar_t *>(data.data()),
            data.size() / sizeof(wchar_t))};
    }
}

uint32_t
raw24bval(uint8_t byte0, uint8_t byte1, uint8_t byte2, QDataStream::ByteOrder order) {
    int32_t val = 0;
    if (order == QDataStream::LittleEndian) {
        val = byte0 | (byte1 << 8) | (byte2 << 16);

    } else {
        val = (byte0 << 16) | (byte1 << 8) | byte2;
    }

    return val;
}

QStringList dataCast::vec2u24(const QByteArray &data, QDataStream::ByteOrder order) {

    QStringList list;

    for (int i = 0; i + 2 < data.size(); i += 3) {
        list << QString::number(raw24bval(data[i], data[i + 1], data[i + 2], order));
    }
    return list;
}

QStringList dataCast::vec2i24(const QByteArray &data, QDataStream::ByteOrder order) {

    QStringList list;

    for (int i = 0; i + 2 < data.size(); i += 3) {
        int val = raw24bval(data[i], data[i + 1], data[i + 2], order);
        if (val & 0x00800000)
            val |= 0xFF000000;
        list << QString::number(val);
    }
    return list;
}

QStringList dataCast::vec2u128(const QByteArray &data, QDataStream::ByteOrder order) {
    QStringList results;
    QDataStream ds(data);
    ds.setByteOrder(order);

    for (int i = 0; i + 15 < data.size(); i += 16) {
        quint64 part1, part2;
        ds >> part1;
        ds >> part2;

        /*
         * The endianess is done at two places : When we pull the data out of the stream,
         * and if needed the two global parts.
         *
         * This effectively does perform a full swap.
         */
        quint64 high, low;
        if (order == QDataStream::LittleEndian) {
            low = part1;
            high = part2;
        } else {
            high = part1;
            low = part2;
        }

        QString hex = QString("0x%1%2")
                          .arg(high, 16, 16, QChar('0'))
                          .arg(low, 16, 16, QChar('0'))
                          .toUpper();
        results << hex;
    }
    return results;
}

QStringList dataCast::vec2i128(const QByteArray &data, QDataStream::ByteOrder order) {
    return vec2u128(data, order); // HEX is forced for that number, so, unsigned.
}

QStringList dataCast::vec2ts32(const QByteArray &data, QDataStream::ByteOrder order) {

    if (data.size() < 4)
        return {};

    QStringList list;

    QDataStream ds(data);
    ds.setByteOrder(order);

    for (int i = 0; i + 3 < data.size(); i += 4) {
        quint32 secs;
        ds >> secs;

        QDateTime time = QDateTime();
        time.setSecsSinceEpoch(secs);

        QString str = time.toString("yyyy-MM-dd HH:mm:ss 'UTC'");
        list << str;
    }

    return list;
}

QStringList dataCast::vec2ts64(const QByteArray &data, QDataStream::ByteOrder order) {
    if (data.size() < 8)
        return {};

    QStringList list;

    QDataStream ds(data);
    ds.setByteOrder(order);

    for (int i = 0; i + 7 < data.size(); i += 8) {
        quint64 secs;
        ds >> secs;

        QDateTime time = QDateTime();
        time.setSecsSinceEpoch(secs);

        QString str = time.toString("yyyy-MM-dd HH:mm:ss.zzz 'UTC'");
        list << str;
    }
}

} // namespace EtherBench::Services