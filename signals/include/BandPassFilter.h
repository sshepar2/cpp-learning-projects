#ifndef BAND_PASS_FILTER_H
#define BAND_PASS_FILTER_H

#include <vector>
#include "Signal.h"

/**
 * @brief Band-pass filter that isolates a frequency range using the DFT.
 *
 * Applies a forward DFT, zeroes frequency bins outside the specified band,
 * and recovers the filtered signal via inverse DFT. Frequency resolution
 * is determined by sampleRate / nSamples.
 */
class BandPassFilter : public Signal {
private:
    double minFreq;
    double maxFreq;

public:
    /**
     * @brief Constructs a BandPassFilter with the specified frequency band.
     * @param signalSamples Time-domain input samples
     * @param sampleRate Sampling rate in Hz
     * @param minFreq Lower cutoff frequency in Hz, must be non-negative
     * @param maxFreq Upper cutoff frequency in Hz, must be greater than minFreq
     * @throws std::invalid_argument if minFreq < 0, maxFreq <= minFreq,
     *         or maxFreq exceeds the Nyquist limit (sampleRate / 2)
     */
    BandPassFilter(const std::vector<double>& signalSamples, double sampleRate, double minFreq, double maxFreq);

    /**
     * @brief Applies band-pass filtering via DFT and returns the result.
     * @return Filtered time-domain samples with energy outside the band removed
     */
    std::vector<double> process() override;

    /**
     * @brief Prints signal type, sample count, and frequency band.
     */
    void describe() override;
};

#endif