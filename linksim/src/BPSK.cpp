#include "BPSK.h"

#include <complex>
#include <vector>

std::vector<std::complex<double>> BPSK::encode(const std::vector<int>& bits) {
    std::vector<std::complex<double>> symbols;
    for (int bit : bits) {
        symbols.push_back(bit == 0 ? std::complex<double>{ 1.0, 0.0}
                                   : std::complex<double>{-1.0, 0.0});
    }
    return symbols;
}

std::vector<int> BPSK::decode(const std::vector<std::complex<double>>& symbols) {
    std::vector<int> bits;
    for (const auto& symbol : symbols) {
        bits.push_back(symbol.real() > 0.0 ? 0 : 1);
    }
    return bits;
}