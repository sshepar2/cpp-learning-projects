#include "BPSK.h"
#include "QPSK.h"
#include "LinkSimulation.h"
#include "SimConfig.h"
#include "utils.h"

#include <iostream>  // cerr only
#include <stdexcept>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./linksim config.json\n";
        return 1;
    }

    try {
        SimConfig config = parseConfig(argv[1]);

        std::vector<double> snrValues;
        for (double snr = config.snrMin; snr <= config.snrMax; snr += config.snrStep) {
            snrValues.push_back(snr);
        }

        if (config.modulation == "BPSK") {
            LinkSimulation<BPSK> sim(config.numBits, config.noiseModel, config.seed);
            auto berCurve = sim.sweepSNR(snrValues);
            writeCSV(config.outputFile, berCurve);
            
        } else if (config.modulation == "QPSK") {
            LinkSimulation<QPSK> sim(config.numBits, config.noiseModel, config.seed);
            auto berCurve = sim.sweepSNR(snrValues);
            writeCSV(config.outputFile, berCurve);
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}