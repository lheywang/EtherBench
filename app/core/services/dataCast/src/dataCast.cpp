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
#include <services/dataCastUnion.hpp>

// Qt
#include <QString>

// STD
#include <string>
#include <vector>

// =============================================================
// CLASS
// =============================================================

namespace EtherBench::Services {

dataCast::dataCast() {
    memset(&result, 0x00, sizeof(result));
    memset(&caster, 0x00, sizeof(caster));
    byte_size = 0;
    current_endianness = CasterEndianness::LITTLE_ENDIAN;
}

dataCast::~dataCast() {}

dataCastResult *dataCast::cast(std::vector<uint8_t> input, CasterEndianness endianness) {
    /*
     * First, configure the caster. Thus, we copy the memory
     */
    byte_size = std::min(input.size(), static_cast<unsigned long long>(32));
    memcpy(&caster.in, input.data(), byte_size);

    /*
     * Then, call the different structs :
     */
    current_endianness = endianness;

    // Little endian result
    result.convertedAsLe =
        (current_endianness == CasterEndianness::LITTLE_ENDIAN) ? true : false;

    // Raw data (first byte only)
    result.binary = vec2binary();
    result.octal = vec2octal();

    // Text
    result.ascii = vec2ascii(); // All data converted !
    result.utf8 = vec2utf8();
    result.utf16 = vec2utf16();

    // Standard integer types
    result.u8 = vec2u8();
    result.i8 = vec2i8();
    result.u16 = vec2u16();
    result.i16 = vec2i16();
    result.u24 = vec2u24();
    result.i24 = vec2i24();
    result.u32 = vec2u32();
    result.i32 = vec2i32();
    result.u64 = vec2u64();
    result.i64 = vec2i64();
    result.u128 = vec2u128();
    result.i128 = vec2i128();

    // Standard float types
    // QString f16;
    // QString f16b;
    result.f32 = vec2f32();
    result.f64 = vec2f64();
    // QString f128;

    // Others data types
    result.ts32 = vec2ts32();
    result.ts64 = vec2ts64();

    /*
     * Exit and return the struct.
     */
    return &result;
}

dataCastResult *dataCast::last_cast() { return &result; }

QString dataCast::vec2binary() { return ""; }
QString dataCast::vec2octal() { return ""; }
QString dataCast::vec2ascii() { return ""; }
QString dataCast::vec2utf8() { return ""; }
QString dataCast::vec2utf16() { return ""; }
QString dataCast::vec2u8() { return ""; }
QString dataCast::vec2i8() { return ""; }
QString dataCast::vec2u16() { return ""; }
QString dataCast::vec2i16() { return ""; }
QString dataCast::vec2u24() { return ""; }
QString dataCast::vec2i24() { return ""; }
QString dataCast::vec2u32() { return ""; }
QString dataCast::vec2i32() { return ""; }
QString dataCast::vec2u64() { return ""; }
QString dataCast::vec2i64() { return ""; }
QString dataCast::vec2u128() { return ""; }
QString dataCast::vec2i128() { return ""; }
QString dataCast::vec2f32() { return ""; }
QString dataCast::vec2f64() { return ""; }
QString dataCast::vec2ts32() { return ""; }
QString dataCast::vec2ts64() { return ""; }

} // namespace EtherBench::Services