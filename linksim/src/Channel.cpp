#include "Channel.h"

#include <cmath>
#include <complex>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

Channel::Channel(const std::string& noiseModel) : noiseModel{noiseModel} {
    if (noiseModel != "AWGN") 
        throw std::invalid_argument("unsupported noise model: " + noiseModel);
}

std::vector<std::complex<double>> Channel::transmit(
    const std::vector<std::complex<double>>& symbols,
    const double snrSymbol
) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(
        0.0, 
        std::sqrt(1.0 / (2.0 * std::pow(10.0, snrSymbol / 10.0)))
    );
    std::vector<std::complex<double>> noisySymbols;
    for (auto& symbol : symbols) {
        std::complex<double> rc{noise(gen), noise(gen)};
        noisySymbols.push_back(symbol + rc);
    }
    return noisySymbols;
}