#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include <vector>
#include "Signal.h"

/**
 * @brief Low-pass filter that smooths a signal using a sliding window average.
 *
 * Each output sample is the mean of its neighboring samples within the window.
 * A shrinking window is used at the edges to preserve edge sample magnitude
 * rather than zero-padding, which would suppress edge values artificially.
 */
class MovingAverageFilter : public Signal {
private:
    int window;

public:
    /**
     * @brief Constructs a MovingAverageFilter with the specified window size.
     * @param signalSamples Time-domain input samples
     * @param sampleRate Sampling rate in Hz
     * @param window Number of samples in the averaging window, must be positive
     *               and no greater than the number of samples
     * @throws std::invalid_argument if window <= 0 or window > samples.size()
     */
    MovingAverageFilter(const std::vector<double>& signalSamples, double sampleRate, int window);

    /**
     * @brief Applies moving average smoothing and returns the result.
     * @return Smoothed signal with the same number of samples as the input
     */
    std::vector<double> process() override;

    /**
     * @brief Prints signal type, sample count, and window size.
     */
    void describe() override;
};

#endif
