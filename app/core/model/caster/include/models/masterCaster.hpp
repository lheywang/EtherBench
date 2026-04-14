/**
 * @file    masterCaster.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Hold the buffer parsing work, for everything.
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
#include "../../private/baseCaster.hpp"
#include "../../private/customCaster.hpp"
#include "masterCasterMagic.hpp"
#include "masterCasterTypes.hpp"

// Qt
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

// STD
#include <vector>
namespace EtherBench::Models {
// =============================================================
// CLASS
// =============================================================
class MasterCaster : public BaseCaster {
  Q_OBJECT // only the top level is a Q_OBJECT

      public :
      /*
       * Constructor and destructors
       */
      MasterCaster();
    ~MasterCaster();

    /*
     * overrides
     */

    std::vector<CastResult> get() override;
  public slots:
    void parse(EtherBench::Models::BufferSlot slot, uint64_t address, uint64_t size) override;

    /*
     * Public functions
     */

    /**
     * @brief Look for some known signatures, available on the target buffer.
     *
     * @param slot      The target slot.
     */
    void look(EtherBench::Models::BufferSlot slot);

    /**
     * @brief Create new parsers, that can be called at anytime.
     *
     * @param path
     */
    void addParser(QString &path);
    void addParser(std::vector<CustomParserElement> elements);

  signals:
    /**
     * @brief Signal emitted once a cast result is available to fetch.
     *
     */
    void castFinished();

  private:
    /*
     * Private functions
     */
    /**
     * @brief Look on the whole buffer for a specific signature. Can be multithreaded.
     *
     * @param slot      The target slot.
     * @param signature The target signature.
     *
     * @return std::vector<SearchResult> A vector of structs, containing the results.
     */
    std::vector<SearchResult> lookForSignature(EtherBench::Models::BufferSlot slot, std::vector<uint8_t> signature);

    /**
     * @brief If we've identified an executable, we can call this function to knwo a bit more about
     *        the said executable. Call LIEF lib internally.
     *
     * @param slot      The target slot.
     * @param address   The target address.
     *
     * @return std::vector<CastResult> A list of results, that could be directly sent to the treeview.
     */
    std::vector<CastResult> parseExecutable(EtherBench::Models::BufferSlot slot, uint64_t address);

    /**
     * @brief If we've identified an binary file, we can call this function to knwo a bit more about
     *        the said executable. Call libcintelhex lib internally.
     *
     * @param slot      The target slot.
     * @param address   The target address.
     *
     * @return std::vector<CastResult> A list of results, that could be directly sent to the treeview.
     */
    std::vector<CastResult> parseBinary(EtherBench::Models::BufferSlot slot, uint64_t address);

    /**
     * @brief If we need to perform a custom parse, call that function. Decided internally.
     *
     * @param slot      The target slot.
     * @param address   The target address.
     * @return std::vector<CastResult>
     */
    std::vector<CastResult> parseCustom(EtherBench::Models::BufferSlot slot, uint64_t address);

    /*
     * Private variables
     */
    std::vector<CustomCaster *> customParsers; // Handle the custom parsers to be called.
};

} // namespace EtherBench::Models