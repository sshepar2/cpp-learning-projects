#ifndef LINK_SIMULATION_H
#define LINK_SIMULATION_H

#include "BitGenerator.h"
#include "Channel.h"

#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Orchestrates a digital link simulation and computes BER vs SNR.
 *
 * Generates a random bit sequence, modulates it using the specified scheme,
 * passes it through a noise channel, demodulates, and computes the bit error
 * rate. Sweeping over a range of SNR values produces a BER curve suitable
 * for link budget analysis.
 *
 * The modulation scheme is specified as a template parameter and must provide:
 * - static constexpr int BITS_PER_SYMBOL
 * - static std::vector<std::complex<double>> encode(const std::vector<int>&)
 * - static std::vector<int> decode(const std::vector<std::complex<double>>&)
 *
 * @tparam ModScheme Modulation policy struct e.g. BPSK, QPSK
 *
 * @note All method definitions are in this header since LinkSimulation
 *       is a template class and cannot be split into a .cpp file.
 *
 * Example usage:
 * @code
 * LinkSimulation<BPSK> sim(10000, "AWGN", 42);
 * auto curve = sim.sweepSNR({-5.0, 0.0, 5.0, 10.0});
 * @endcode
 */
template <typename ModScheme>
class LinkSimulation {
private:
    int nBits;
    BitGenerator bitGen;
    Channel channel;

    /**
     * @brief Computes bit error rate between transmitted and received bits.
     * @param bits Original transmitted bits
     * @param decoded Received bits after demodulation
     * @return Fraction of bits received incorrectly in range [0, 1]
     */
    double computeBER(
        const std::vector<int>& bits, 
        const std::vector<int>& decoded
    ) const {
        double errors = 0.0;
        for (int i = 0; i < nBits; i++) {
            errors += (decoded[i] != bits[i] ? 1.0 : 0.0);
        }
        return errors / nBits;
    }

    /**
     * @brief Runs one simulation at a given SNR and returns BER.
     * @param snrDb Signal to noise ratio in dB
     * @return Bit error rate at this SNR
     */
    double runAtSNR(double snrDb) const {
        std::vector<int> bits = bitGen.generate(nBits);
        std::vector<std::complex<double>> symbols = ModScheme::encode(bits);
        std::vector<std::complex<double>> received = channel.transmit(symbols, snrDb);
        std::vector<int> decoded = ModScheme::decode(received);
        return computeBER(bits, decoded);
    }

public:
/**
     * @brief Constructs a LinkSimulation with the given parameters.
     * @param nBits Number of bits to simulate per SNR point
     * @param noiseModel Noise model identifier, currently only "AWGN" supported
     * @param seed RNG seed for reproducible bit sequences
     * @throws std::invalid_argument if nBits <= 0 
     * @throws std::invalid_argument if noiseModel is not supported (propagated from Channel)
     */
    LinkSimulation(
        int nBits,
        std::string noiseModel = "AWGN",
        unsigned int seed = std::random_device{}()
    ) : nBits{nBits}, bitGen{seed}, channel{noiseModel} {
        if (nBits <= 0) 
            throw std::invalid_argument("nBits must be positive");
    }

    /**
     * @brief Sweeps over SNR values and returns a BER curve.
     *
     * Each point in the returned vector is a {snr_db, ber} pair.
     * Results are suitable for direct output to CSV and plotting
     * on a logarithmic BER axis.
     *
     * @param snrValues Vector of SNR values in dB to simulate
     * @return Vector of {SNR, BER} pairs in the same order as snrValues
     */
    std::vector<std::pair<double, double>> sweepSNR(
        const std::vector<double>& snrValues
    ) const {
        std::vector<std::pair<double, double>> berCurve;
        for (const auto& snrDb : snrValues) {
            // C++17 - deduces pair from vector type
            berCurve.push_back({snrDb, runAtSNR(snrDb)});
        }
        return berCurve;
    }
};

#endif