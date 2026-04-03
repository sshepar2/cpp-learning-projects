#ifndef CHANNEL_H
#define CHANNEL_H

#include <complex>
#include <string>
#include <vector>

/**
 * @brief Models a noisy transmission channel.
 *
 * Adds complex Gaussian noise to IQ symbols to simulate transmission
 * impairments. The noise power is determined by the SNR per symbol 
 * passed to transmit(), allowing the same Channel instance to be reused
 * across multiple SNR values in a sweep.
 *
 * Currently supports AWGN (Additive White Gaussian Noise) only.
 * Independent Gaussian noise is added to both I and Q components.
 */
class Channel {
private:
    std::string noiseModel; ///< Noise model identifier e.g. "AWGN"
public:
    /**
     * @brief Constructs a Channel with the specified noise model.
     * @param noiseModel Noise model identifier, currently only "AWGN" supported
     * @throws std::invalid_argument if noiseModel is not supported
     */
    Channel(const std::string& noiseModel = "AWGN");

    /**
     * @brief Transmits IQ symbols through the channel, adding noise.
     *
     * Noise standard deviation is derived from snrDb assuming unit
     * signal power: sigma = sqrt(1 / (2 * 10^(snrDb/10)))
     *
     * @param symbols Input IQ symbols to corrupt
     * @param snrSymbol Signal to noise ratio per symbol (Es/N0) in dB
     * @return Noise-corrupted IQ symbols
     */
    std::vector<std::complex<double>> transmit(
        const std::vector<std::complex<double>>& symbols,
        const double snrSymbol
    ) const;
};

#endif