#include "particle.h"
#include "simulation.h"

int main() {
    std::vector<Particle*> particles;
    ClassicalParticle cp(0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f);
    QuantumParticle qp(0.0f, 0.0f, 0.0f, 1.0f, 0.5f, "electron");
    particles.push_back(&cp);
    particles.push_back(&qp);
    printSimulationSummary(particles);
    return 0;
}
