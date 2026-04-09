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
#include <services/dataCastUnion.hpp>

// Qt
#include <QString>
#include <vector>

namespace EtherBench::Services {

// =============================================================
// CLASS
// =============================================================
enum class CasterEndianness { LITTLE_ENDIAN, BIG_ENDIAN };
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
    dataCastResult *cast(
        std::vector<uint8_t> input,
        CasterEndianness endianness = CasterEndianness::LITTLE_ENDIAN);

    dataCastResult *last_cast();

  private:
    /*
     * Private caster helpers
     */
    QString vec2binary();
    QString vec2octal();
    QString vec2ascii();
    QString vec2utf8();
    QString vec2utf16();
    QString vec2u8();
    QString vec2i8();
    QString vec2u16();
    QString vec2i16();
    QString vec2u24();
    QString vec2i24();
    QString vec2u32();
    QString vec2i32();
    QString vec2u64();
    QString vec2i64();
    QString vec2u128();
    QString vec2i128();
    QString vec2f32();
    QString vec2f64();
    QString vec2ts32();
    QString vec2ts64();

    /*
     * Private variables
     */
    dataCastResult result;
    dataCastUnion caster;
    size_t byte_size;
    CasterEndianness current_endianness;
};

} // namespace EtherBench::Services