#include <iostream>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "MovingAverageFilter.h"

MovingAverageFilter::MovingAverageFilter(const std::vector<double>& signalSamples, double sampleRate, int window)
    : Signal{signalSamples, sampleRate}, window{window} {
    if (window <= 0) throw std::invalid_argument("window size must be positive");
    if (window > static_cast<int>(signalSamples.size())) throw std::invalid_argument("window size cannot exceed number of samples");
}
    
std::vector<double> MovingAverageFilter::process() {
    std::vector<double> oldSignal = getSamples();
    int nSamples= static_cast<int>(oldSignal.size());
    std::vector<double> newSignal(nSamples, 0.0);

    int halfWindow = window / 2;

    for (int i = 0; i < nSamples; i++) {
        int start = std::max(0, i - halfWindow);
        int end = std::min(nSamples - 1, i + halfWindow);

        double sum = std::accumulate(oldSignal.begin() + start, 
                                        oldSignal.begin() + end + 1, 
                                        0.0);
        newSignal[i] = sum / static_cast<double>(end - start + 1);
    }
    return newSignal;
}

void MovingAverageFilter::describe() {
    std::cout << "Signal Type: Filtered-Averaged\n";
    std::cout << "Sample Count: " << getSamples().size() << "\n";
    std::cout << "Window Size: " << window << "\n";
}