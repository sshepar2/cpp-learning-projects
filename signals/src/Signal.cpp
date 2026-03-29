#include <stdexcept>
#include "Signal.h"

Signal::Signal(const std::vector<double>& signalSamples, double sampleRate)
    : samples{signalSamples}, rate{sampleRate} {
    // willingly incur 'cost' of initializing before validation, in this case
    if (signalSamples.empty()) throw std::invalid_argument("signalSamples must not be empty");
    if (sampleRate <= 0.0) throw std::invalid_argument("sampleRate must be positive");
}

std::vector<double> Signal::getSamples() const {
    return samples;
}
double Signal::getSampleRate() const {
    return rate;
}

std::vector<double> Signal::process() {
    return samples;
}
