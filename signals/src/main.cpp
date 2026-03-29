#include <iostream> // cerr only
#include <vector>
#include <exception>
#include <stdexcept>
#include "NoisySignal.h"
#include "MovingAverageFilter.h"
#include "BandPassFilter.h"
#include "utils.h"

int main() {
    try {
        std::vector<double> frequencies = {1.0, 2.0, 3.0, 10.0, 20.0}; // Hz
        std::vector<double> amplitudes = {1.0, 2.0, 3.0, 4.0, 5.0};
        double rate = 100.0; // Hz rate > 2 * max(frequencies)
        double duration = 20.0; // Seconds
        double noiseLevel = 1.0;
        
        std::vector<double> signal = generateSamples(
            frequencies,
            amplitudes,
            rate,
            duration, 
            noiseLevel
        );

        NoisySignal ns(signal, rate);
        printStats(&ns);

        int window = 10;

        MovingAverageFilter maf(signal, rate, window);
        printStats(&maf);

        double minFreq = 2.0;
        double maxFreq = 5.0;
        
        BandPassFilter bpf(signal, rate, minFreq, maxFreq);
        printStats(&bpf);

    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}