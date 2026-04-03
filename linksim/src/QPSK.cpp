#include "constants.h"
#include "QPSK.h"

#include <complex>
#include <vector>

std::vector<std::complex<double>> QPSK::encode(const std::vector<int>& bits) {
    std::vector<std::complex<double>> symbols;
    for (int i = 0; i < static_cast<int>(bits.size()) - 1; i += 2) {
        symbols.push_back(std::complex<double>{ 
            (bits[i]   == 0 ? 1.0 : -1.0) * constants::iSqrtTwo, 
            (bits[i+1] == 0 ? 1.0 : -1.0) * constants::iSqrtTwo
        });
    }
    return symbols;
}

std::vector<int> QPSK::decode(const std::vector<std::complex<double>>& symbols) {
    std::vector<int> bits;
    for (const auto& symbol : symbols) {
        bits.push_back(symbol.real() > 0.0 ? 0 : 1);
        bits.push_back(symbol.imag() > 0.0 ? 0 : 1);
    }
    return bits;
}