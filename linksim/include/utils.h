#include "SimConfig.h"

#include <string>
#include <utility>
#include <vector>

SimConfig parseConfig(const std::string& path);

void writeCSV(
    const std::string& path,
    const std::vector<std::pair<double, double>>& berCurve
);