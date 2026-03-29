#ifndef NOISY_SIGNAL_H
#define NOISY_SIGNAL_H

#include <vector>
#include "Signal.h"

/**
 * @brief Represents a raw unprocessed signal with no filtering applied.
 *
 * Serves as a baseline in the processing pipeline. process() returns
 * samples unchanged, allowing comparison against filtered outputs.
 */
class NoisySignal : public Signal {
public:
    /**
     * @brief Constructs a NoisySignal with the given samples and sample rate.
     * @param signalSamples Time-domain input samples
     * @param sampleRate Sampling rate in Hz
     * @throws std::invalid_argument if sampleRate <= 0 or samples is empty
     */
    NoisySignal(const std::vector<double>& signalSamples, double sampleRate);

    /**
     * @brief Returns samples unchanged.
     * @return Unmodified input samples
     */
    std::vector<double> process() override;

    /**
     * @brief Prints signal type and sample count.
     */
    void describe() override;
};

#endif