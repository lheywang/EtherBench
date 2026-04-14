/**
 * @file    customCaster.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the custom Parser class, for the user enabled data parsing.
 * @version 0.1
 * @date    2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include "baseCaster.hpp"
#include <models/masterCasterTypes.hpp>

// Libraries
#include <models/memoryPool.hpp>

// Qt
#include <QString>
#include <QStringList>
#include <QVariant>

// STD
#include <vector>

namespace EtherBench::Models {
// =============================================================
// STRUCT
// =============================================================
/**
 * @brief Hold a parsed element, from the struct. Sent as JSON arrays.
 *
 */
struct CustomParserElement {
    QString name;
    uint64_t offset;
    uint64_t size;
    QString type;
};

// =============================================================
// CLASS
// =============================================================
/**
 * @brief Handle the cast of some bytes according to a single spec.
 *
 */
class CustomCaster : public BaseCaster {

  public:
    /*
     * Constructors and destructors
     */
    CustomCaster();
    CustomCaster(QString &path);
    CustomCaster(std::vector<CustomParserElement> parsers);

    /*
     * Overrides functions
     */
    void parse(EtherBench::Models::BufferSlot slot, uint64_t address, uint64_t size) override;
    std::vector<CastResult> get() override;

    /*
     * Specialized functions
     */

    /**
     * @brief load a list of parsers from a .ebc file.
     *
     * @param path The file path
     */
    void loadFromFile(QString &path);

  private:
    /*
     * Functions
     */

    /**
     * @brief Parse an element from the buffer, according to the passed specs.
     *        Each call will use the next parser, automatically.
     *
     * @param bytes     The raw bytes inputs.
     * @param element   The element to be parsed.
     */
    CastResult parseElement(std::vector<uint8_t> bytes, CustomParserElement element);

    /*
     * Variables
     */
    std::vector<CustomParserElement> elements; // Store the parser elements.
};

} // namespace EtherBench::Models
