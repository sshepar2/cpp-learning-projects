#ifndef SIM_CONFIG_H
#define SIM_CONFIG_H

#include <string>

/**
 * @brief Configuration parameters for a link simulation run.
 * 
 * Populated by parseing a JSON config file. Controls modulation scheme,
 * bit count, SNR sweep range, noise model, and output destination
 */
struct SimConfig {
    std::string modulation;    ///< Modulation scheme identifier e.g. "BPSK"
    int numBits;               ///< Number of bits per SNR points
    double snrMin;             ///< Start of SNR sweep in dB
    double snrMax;             ///< End of SNR sweep in dB
    double snrStep;            ///< SNR step size in dB
    std::string noiseModel;    ///< Noise model identifier, e.g. "AWGN"
    unsigned int seed;         ///< RNG seed for reproducibility
    std::string outputFile;    ///< Path to CSV output file
};

#endif