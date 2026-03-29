#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include "constants.h"
#include "utils.h"
#include "Signal.h"

std::vector<double> generateSamples(
    const std::vector<double>& frequencies,
    const std::vector<double>& amplitudes,
    double sampleRate,
    double duration,
    double noiseLevel) {
    
    if (frequencies.size() != amplitudes.size()) throw std::invalid_argument("frequencies and amplitudes must have the same size");
    if (sampleRate <= 0.0) throw std::invalid_argument("sampleRate must be positive");
    if (duration <= 0.0) throw std::invalid_argument("duration must be positive");
    if (noiseLevel < 0.0) throw std::invalid_argument("noiseLevel must be non-negative");
    
    int nSamples = static_cast<int>(sampleRate * duration);
    std::vector<double> signal(nSamples, 0.0);

    // add sine wave components
    for (int n = 0; n < nSamples; n++) {
        double t = n / sampleRate;  // time at sample n
        for (int f = 0; f < static_cast<int>(frequencies.size()); f++) {
            signal[n] += amplitudes[f] * std::sin(2.0 * constants::PI * frequencies[f] * t);
        }
    }

    // add Gaussian noise
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(0.0, noiseLevel);

    for (int n = 0; n < nSamples; n++) {
        signal[n] += noise(gen);
    }

    return signal;
}

std::vector<std::complex<double>> dft(const std::vector<double>& samples) {
    assert(!samples.empty() && "dft input must not be empty");

    int N = static_cast<int>(samples.size());
    std::vector<std::complex<double>> dftSamples(N, {0.0, 0.0});
    
    for (int k = 0; k < N; k++) {
        for (int n = 0; n < N; n++) {
            dftSamples[k] += samples[n] * std::exp(std::complex<double>(0.0, -2.0 * constants::PI * k * n / N));
        }
    }
    return dftSamples;
}

std::vector<double> idft(const std::vector<std::complex<double>>& dftSamples) {
    assert(!dftSamples.empty() && "idft input must not be empty");

    int N = static_cast<int>(dftSamples.size());
    std::vector<double> samples(N, 0.0);

    for (int n = 0; n < N; n++) {
        std::complex<double> idftSample = {0.0, 0.0};

        for (int k = 0; k < N; k++) {
            idftSample += dftSamples[k] * std::exp(std::complex<double>(0.0, 2.0 * constants::PI * n * k / N));
        }
        samples[n] = idftSample.real() / N;
    }
    return samples;
}

double dominantFrequency(const std::vector<double>& samples, double sampleRate) {
    assert(!samples.empty() && "samples input must not be empty");
    assert(sampleRate > 0.0 && "sampleRate must be positive");
    
    int N = static_cast<int>(samples.size());    
    std::vector<std::complex<double>> dftSamples = dft(samples);

    int peakBin = 0;
    double peakMag = 0.0;
    for (int k = 1; k < N / 2; k++) {  // skip bin 0 (DC)
        double mag = std::abs(dftSamples[k]);
        if (mag > peakMag) {
            peakMag = mag;
            peakBin = k;
        }
    }

    return peakBin * (sampleRate / N);
}

void printStats(Signal* signal) {
    assert(signal != nullptr && "signal pointer must not be null");

    signal->describe();

    std::vector<double> samples = signal->getSamples();
    
    double energyRaw = std::inner_product(samples.begin(), samples.end(), samples.begin(), 0.0);
    samples = signal->process();
    double energyProc = std::inner_product(samples.begin(), samples.end(), samples.begin(), 0.0);
    
    int N = static_cast<int>(samples.size());
    double mean = std::accumulate(samples.begin(), samples.end(), 0.0) / N;
    double minVal = *std::min_element(samples.begin(), samples.end());
    double maxVal = *std::max_element(samples.begin(), samples.end());
    double variance = 0.0;
    for (double s : samples) variance += (s - mean) * (s - mean);
    variance /= N;

    std::cout << "Signal Statistics\n";
    std::cout << "  Energy Retained: " << 100.00 * energyProc / energyRaw << " %\n";
    std::cout << "  Mean:            " << mean << "\n";
    std::cout << "  StdDev:          " << std::sqrt(variance) << "\n";
    std::cout << "  Min:             " << minVal << "\n";
    std::cout << "  Max:             " << maxVal << "\n\n";
}
