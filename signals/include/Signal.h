#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

/**
 * @brief Abstract base class representing a digitally sampled signal.
 *
 * Provides a common interface for all signal types including raw signals
 * and filtered variants. Derived classes must implement describe() and
 * may override process() to apply signal processing operations.
 */
class Signal {
private:
    std::vector<double> samples;
    double rate;

public:
    /**
     * @brief Constructs a Signal with the given samples and sample rate.
     * @param signalSamples Time-domain samples of the signal
     * @param sampleRate Sampling rate in Hz, must be positive
     * @throws std::invalid_argument if sampleRate <= 0 or samples is empty
     */
    Signal(const std::vector<double>& signalSamples, double sampleRate);

    /**
     * @brief Returns the raw time-domain samples.
     * @return Vector of signal samples
     */
    std::vector<double> getSamples() const;

    /**
     * @brief Returns the sample rate in Hz.
     * @return Sample rate
     */
    double getSampleRate() const;

    /**
     * @brief Applies signal processing and returns the result.
     *
     * Default implementation returns samples unchanged.
     * Derived classes override this to apply filtering or other processing.
     *
     * @return Processed signal samples
     */
    virtual std::vector<double> process();

    /**
     * @brief Prints a description of the signal type and properties.
     */
    virtual void describe() = 0;
    
    virtual ~Signal() = default;
};

#endif