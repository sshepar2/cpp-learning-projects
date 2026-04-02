
#include "BitGenerator.h"
#include <vector>
#include <random>

BitGenerator::BitGenerator(unsigned int seed)
    : seed{seed}, gen{seed} {}

std::vector<int> BitGenerator::generate(int nBits) const {
    gen.seed(seed);
    std::uniform_int_distribution<> dist(0, 1);
    std::vector<int> bits;
    for (int i = 0; i < nBits; i++) {
        bits.push_back(dist(gen));
    }
    return bits;
}