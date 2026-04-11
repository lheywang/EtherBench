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
// STD
#include <cstdint>
#include <vector>

namespace EtherBench::Services {

// =============================================================
// FUNCTIONS
// =============================================================

/**
 * @brief Compute the entropy over @ref step bytes for @ref windowSize bytes in total from
 *        a @ref data buffer. That a very nice feature to quickly analyse, by eyes the
 *        contents from a memory buffer.
 *
 * @param data          The input vector.
 * @param windowSize    The number of bytes that must be analyzed.
 * @param step          The number of bytes per step. Reminder : More is faster !
 *
 * @return std::vector<double>
 */
std::vector<double>
entropy(const std::vector<uint8_t> &data, size_t windowSize, size_t step);

/**
 * @brief Compute the derivative from a value to another over @step bytes for @ref
 *        windowSize bytes in total from @ref data buffer ! Provide the missing
 *        informations about a given buffer.
 *
 * @param data          The input vector.
 * @param windowSize    The number of bytes that must be analyzed.
 * @param step          The number of bytes per step. Reminder : More is faster !
 *
 * @return std::vector<double>
 */
std::vector<double>
derivative(const std::vector<uint8_t> &data, size_t windowSize, size_t step);

} // namespace EtherBench::Services