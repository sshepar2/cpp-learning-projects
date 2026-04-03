#include "SimConfig.h"
#include "utils.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

/**
 * @brief Parses a JSON configuration file and returns a SimConfig struct.
 *
 * Opens and parses the specified JSON file, populates a SimConfig struct,
 * and validates all fields before returning. Throws on missing keys,
 * malformed JSON, or invalid parameter values.
 *
 * Expected JSON structure:
 * @code
 * {
 *     "modulation":   "BPSK",
 *     "num_bits":     10000,
 *     "snr_range_db": { "min": -5.0, "max": 15.0, "step": 1.0 },
 *     "noise_model":  "AWGN",
 *     "seed":         42,
 *     "output_file":  "results/ber_results.csv"
 * }
 * @endcode
 *
 * @param path Path to the JSON config file
 * @return Populated and validated SimConfig struct
 * @throws std::runtime_error if the file cannot be opened
 * @throws std::invalid_argument if any field fails validation
 * @note snr sweep will start at "min" and stop at "max" thus "step" > 0
 * @note The "seed" field is optional. If omitted, a hardware random seed is used.
 */
SimConfig parseConfig(const std::string& path) {

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("could not open config file: " + path);

    nlohmann::json j = nlohmann::json::parse(file);
    
    SimConfig config;
    config.modulation = j["modulation"]; // BPSK, QPSK
    config.numBits    = j["num_bits"];
    config.snrMin     = j["snr_range_db"]["min"];
    config.snrMax     = j["snr_range_db"]["max"];
    config.snrStep    = j["snr_range_db"]["step"];
    config.noiseModel = j["noise_model"]; // only AWGN atm
    config.seed       = j.value("seed", static_cast<unsigned int>(std::random_device{}()));
    config.outputFile = j["output_file"];

    if (config.numBits <= 0)
        throw std::invalid_argument("num_bits must be positive");
    if (config.modulation == "QPSK" && config.numBits % 2 != 0)
        throw std::invalid_argument("num_bits must be even for QPSK modulation");
    if (config.snrStep <= 0.0)
        throw std::invalid_argument("snr_range_db.step must be positive");
    if (config.snrMax < config.snrMin) 
        throw std::invalid_argument("snr_range_db.max must be greater than min");
    if (config.modulation != "BPSK" && config.modulation != "QPSK")
        throw std::invalid_argument("unsupported modulation: " + config.modulation);
    if (config.noiseModel != "AWGN")
        throw std::invalid_argument("unsupported noise model: " + config.noiseModel);

    return config;
}

/**
 * @brief Writes a BER curve to a CSV file.
 *
 * Outputs a two-column CSV with a header row, one row per SNR point.
 * Values are written in fixed precision to six decimal places.
 * Any directories in the CSV path which do not exist prior to 
 * calling will be created by this function.
 *
 * Output format:
 * @code
 * snr_db,ber
 * -5.000000,0.152341
 *  0.000000,0.078432
 * @endcode
 *
 * @param path Path to the output CSV file
 * @param berCurve Vector of {SNR, BER} pairs to write
 * @throws std::runtime_error if the file cannot be opened
 * @pre berCurve must not be empty
 */
void writeCSV(
    const std::string& path,
    const std::vector<std::pair<double, double>>& berCurve
) {
    // Since C++17
    std::filesystem::create_directories(
        std::filesystem::path(path).parent_path()
    );
    std::ofstream file(path);
    if (!file.is_open()) throw std::runtime_error(
        "Could not open output file: " + path
    );
    file << "snr_db,ber\n";
    //C++17 - allows structured bindings
    for (const auto& [snr, ber] : berCurve) {
        file << std::fixed << std::setprecision(6) << snr << "," << ber << "\n";
    }
}