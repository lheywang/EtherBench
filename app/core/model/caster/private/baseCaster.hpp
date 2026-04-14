/**
 * @file    baseCaster.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   The common API to all casters.
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
#include <models/masterCasterTypes.hpp>

// Libraries
#include <models/memoryPool.hpp>

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
class BaseCaster : public QObject {
    Q_OBJECT

  public:
    /*
     * Constructor and destructors
     */
    BaseCaster();
    ~BaseCaster();

    /*
     * Public functions
     */

  public slots:
    /**
     * @brief   Parse some bytes from the target buffer. The buffer isn't passed directly, as this enable passing by
     *          reference, which is going to be much, much faster.
     *
     * @param slot      The target slot to be parsed.
     * @param address   The target address at which we shall look.
     * @param size      The target size to be looked for.
     */
    virtual void parse(EtherBench::Models::BufferSlot slot, uint64_t address, uint64_t size) = 0;

  public:
    /**
     * @brief Get the parsing results objects.
     *
     * @return vector of Cast results.
     */
    virtual std::vector<CastResult> get() = 0;
};

} // namespace EtherBench::Models
