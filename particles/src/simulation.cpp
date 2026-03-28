#include "simulation.h"

void printSimulationSummary(std::vector<Particle*> particlePointers) {
    for (const auto& particle : particlePointers) {
        particle->describe();
        std::cout << "KE: " << particle->kineticEnergy() << std::endl;
    }
}
