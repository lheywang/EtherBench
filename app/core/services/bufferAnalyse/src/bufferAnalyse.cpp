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
#include <services/bufferAnalyse.hpp>

// STD
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

// =============================================================
// CONSTEXPR
// =============================================================
constexpr int ENTROPY_LUT_SIZE = 256;
constexpr std::array<float, ENTROPY_LUT_SIZE> generate_entropy_lut() {
    std::array<float, ENTROPY_LUT_SIZE> arr;
    for (int i = 0; i < 256; ++i) {
        if (i == 0)
            arr[i] = 0;
        else {
            float p = static_cast<float>(i);
            arr[i] = -p * std::log2(p);
        }
    }
    return arr;
}
constexpr auto entropy_lut = generate_entropy_lut();

// =============================================================
// FUNCTIONS
// =============================================================

namespace EtherBench::Services {

std::vector<double>
entropy(const std::vector<uint8_t> &data, size_t windowSize, size_t step) {

    // Create the output buffer.
    std::vector<double> results;

    // Ensure we have enough data
    if (data.size() < windowSize)
        return results;

    // Pre calculate a factor
    double log2N = std::log2(static_cast<double>(windowSize));

    // Iterate
    for (size_t i = 0; i <= data.size() - windowSize; i += step) {

        double sumCountLogCount = 0;
        int counts[256] = {0};

        for (size_t j = 0; j < windowSize; ++j)
            counts[data[i + j]]++;

        for (int c = 0; c < 256; ++c) {
            if (counts[c] > 0)
                sumCountLogCount += entropy_lut[counts[c]];
        }

        //  H = log2(N) - (1/N * sum(ni * log2(ni)))
        double h = log2N - (sumCountLogCount / static_cast<double>(windowSize));

        results.push_back(std::clamp(h / log2N, 0.0, 1.0));
    }
    return results;
}

std::vector<double>
derivative(const std::vector<uint8_t> &data, size_t windowSize, size_t step) {
    std::vector<double> results;
    if (data.size() < windowSize)
        return results;

    for (size_t i = 0; i <= data.size() - windowSize; i += step) {
        double val = 0;

        for (size_t j = 1; j < windowSize; ++j) {
            val += std::abs(data[i + j] - data[i + j - 1]);
        }
        val /= (windowSize << 8); // * 256, shall be 255 but we'll round up (faster)

        results.push_back(std::clamp(val, 0.0, 1.0));
    }
    return results;
}

} // namespace EtherBench::Services
