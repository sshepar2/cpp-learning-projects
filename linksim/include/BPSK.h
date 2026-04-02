#ifndef BPSK_H
#define BPSK_H

#include <vector>
#include <complex>

/**
 * @brief BPSK (Binary Phase Shift Keying) modulation scheme policy struct.
 *
 * Implements the modulation policy interface required by LinkSimulation.
 * Maps each bit to a complex symbol on the I axis — bit 0 to {+1, 0}
 * and bit 1 to {-1, 0} — representing 0° and 180° phase states of the
 * carrier respectively. Q component is always zero for pure BPSK.
 *
 * @note Intended for use as a template parameter: LinkSimulation<BPSK>
 */
struct BPSK {
    static constexpr int BITS_PER_SYMBOL = 1; ///< One bit encoded per symbol

    /**
     * @brief Encodes a bit sequence into BPSK IQ symbols.
     * @param bits Input bits, values must be 0 or 1
     * @return Complex IQ symbols with Q always zero
     */
    static std::vector<std::complex<double>> encode(const std::vector<int>& bits);

    /**
     * @brief Decodes BPSK IQ symbols back to bits.
     *
     * Decision is made on the sign of the real (I) component.
     * Positive I maps to bit 0, negative I maps to bit 1.
     *
     * @param symbols Received IQ symbols, potentially corrupted by noise
     * @return Decoded bit sequence
     */
    static std::vector<int> decode(const std::vector<std::complex<double>>& symbols);
};

#endif