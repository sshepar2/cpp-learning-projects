#ifndef BIT_GENERATOR_H
#define BIT_GENERATOR_H

#include <random>
#include <vector>

/**
 * @brief Generates reproducible random bit sequences.
 *
 * Wraps a Mersenne Twister RNG seeded at construction. Each call to
 * generate() reseeds from the stored seed before producing bits,
 * guaranteeing the same sequence is returned for the same nBits
 * regardless of how many times generate() has been called previously.
 *
 * This reproducibility is important for link simulations where the
 * same bit sequence should be transmitted at every SNR point so that
 * BER differences reflect noise level only, not different bit patterns.
 */
class BitGenerator {
private:
    unsigned int seed;        ///< Stored seed for reproducible generation
    mutable std::mt19937 gen; ///< Mersenne Twister RNG
public:
    /**
     * @brief Constructs a BitGenerator with the given seed.
     * @param seed RNG seed. Defaults to a hardware random value if omitted.
     */
    BitGenerator(unsigned int seed = std::random_device{}());

    /**
     * @brief Generates a reproducible sequence of random bits.
     *
     * Reseeds the RNG from the stored seed before each call, so the
     * returned sequence is identical for the same nBits on every call.
     *
     * @param nBits Number of bits to generate, must be positive
     * @return Vector of random bits, each value 0 or 1
     * @pre nBits must be greater than zero
     */
    std::vector<int> generate(int nBits) const;
};

#endif