#ifndef QPSK_H
#define QPSK_H

#include <vector>
#include <complex>

/**
 * @brief QPSK (Quadrature Phase-Shift Keying) modulation scheme policy struct.
 *
 * Implements the modulation policy interface required by LinkSimulation.
 * Maps each consecutive pair of bits (bit[i], bit[i+1]) = (bitI, bitQ) to a 
 * complex symbol on the I and Q axes using map(bit): [0,1] -> [+1.0,-1.0] and 
 * {map(bitI), map(bitQ)} - each representing 0° and 180° phase states of the 
 * carrier respectively. Where the Q component is 90° out of phase with I.
 *
 * @note Intended for use as a template parameter: LinkSimulation<QPSK>
 */
struct QPSK {
    static constexpr int BITS_PER_SYMBOL = 2; ///< Two bits encoded per symbol

    /**
     * @brief Encodes a bit sequence into QPSK IQ symbols.
     * @param bits Input bits, values must be 0 or 1
     * @return Complex IQ symbols
     */
    static std::vector<std::complex<double>> encode(const std::vector<int>& bits);

    /**
     * @brief Decodes QPSK IQ symbols back to bits.
     *
     * Decision is made on the sign of the real (I) and
     * imaginary (Q) components, inverting the mapping used in encode:
     * Positive I/Q maps to bit 0, negative I/Q maps to bit 1.
     *
     * @param symbols Received IQ symbols, potentially corrupted by noise
     * @return Decoded bit sequence
     */
    static std::vector<int> decode(const std::vector<std::complex<double>>& symbols);
};

#endif