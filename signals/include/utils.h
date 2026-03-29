#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <complex>
#include "Signal.h"

/**
 * @brief Returns samples from linear combination of sine waves
 * @param frequencies List of frequencies for sine waves, Hz
 * @param amplitudes Corresponding amplitudes for sine waves
 * @param sampleRate Sample rate in Hz
 * @param duration Total length of signal in seconds
 * @param noiseLevel Std of Gaussian being sampled
 * @return Samples from generated noisy signal
 */
std::vector<double> generateSamples(
    const std::vector<double>& frequencies,
    const std::vector<double>& amplitudes,
    double sampleRate,
    double duration,
    double noiseLevel);

/**
 * @brief Computes the Discrete Fourier Transform of a real-valued signal.
 * @param samples Time-domain samples, must not be empty
 * @return Complex frequency-domain representation of the samples
 * @pre samples must not be empty
 * @note This is a naive O(N^2) implementation intended for educational
 *       purposes. For production use, prefer an FFT library such as FFTW or Intel MKL.
 */
std::vector<std::complex<double>> dft(const std::vector<double>& samples);

/**
 * @brief Computes the Inverse Discrete Fourier Transform of a complex-valued signal.
 * @param dftSamples Time-domain samples, must not be empty
 * @return Real-valued time-domain samples
 * @pre dftSamples must not be empty
 * @note This is a naive O(N^2) implementation intended for educational
 *       purposes. For production use, prefer an FFT library such as FFTW or Intel MKL.
 */
std::vector<double> idft(const std::vector<std::complex<double>>& dftSamples);

/**
 * @brief Returns the dominant frequency in a signal
 * @param samples Time domain samples
 * @param sampleRate Sample rate in Hz
 * @return Frequency in Hz of the highest energy component
 */
double dominantFrequency(const std::vector<double>& samples, double sampleRate);

/**
 * @brief Prints useful information about signal for diagnostics
 * @param signal Pointer to Signal object
 */
void printStats(Signal* signal);

#endif