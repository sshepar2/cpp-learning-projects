#include <iostream>
#include "NoisySignal.h"

NoisySignal::NoisySignal(const std::vector<double>& signalSamples, double sampleRate)
    : Signal{signalSamples, sampleRate} {}

std::vector<double> NoisySignal::process() {
    return getSamples();
}

void NoisySignal::describe() {
    std::cout << "Signal Type: Noisy/Raw Signal\n";
    std::cout << "Sample Count: " << getSamples().size() << "\n";
}
