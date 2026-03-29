#include <iostream>
#include <complex>
#include <stdexcept>
#include "utils.h"
#include "BandPassFilter.h"

BandPassFilter::BandPassFilter(const std::vector<double>& signalSamples, double sampleRate, double minFreq, double maxFreq)
    : Signal{signalSamples, sampleRate}, minFreq{minFreq}, maxFreq{maxFreq} {
    if (minFreq < 0.0) throw std::invalid_argument("minFreq must be non-negative");
    if (maxFreq <= minFreq) throw std::invalid_argument("maxFreq must be greater than minFreq");
    if (maxFreq > sampleRate / 2.0) throw std::invalid_argument("maxFreq exceeds Nyquist limit (sampleRate / 2)");
}

std::vector<double> BandPassFilter::process() {
    std::vector<double> rawSamples = getSamples();
    int nSamples = static_cast<int>(rawSamples.size());
    
    // forward transform
    std::vector<std::complex<double>> dftSamples = dft(rawSamples);

    // apply filter
    for (int k = 0; k < nSamples; k++) {
        double freq = k * (getSampleRate() / nSamples);
        if (freq < minFreq || freq > maxFreq) {
            dftSamples[k] = {0.0, 0.0};
        }
    }

    // reverse transform
    return idft(dftSamples);
}

void BandPassFilter::describe() {
    std::cout << "Signal Type: Filtered-Band Pass\n";
    std::cout << "Sample Count: " << getSamples().size() << "\n";
    std::cout << "Frequency Range: " << minFreq << "-" << maxFreq << " Hz\n";
}