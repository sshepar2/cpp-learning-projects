#include "particle.h"

// Particle class methods, interface/virtual class
Particle::Particle(float x, float y, float z, float particleMass)
    : position{x, y, z}, mass{particleMass} {}

std::array<float, 3> Particle::getPosition() const {
    return position;
}

float Particle::getMass() const {
    return mass;
}

float Particle::kineticEnergy() {
    return 0.0f;
}

// ClassicalParticle methods
ClassicalParticle::ClassicalParticle(float x, float y, float z, float particleMass, float vx, float vy, float vz)
    : Particle{x, y, z, particleMass}, velocity{vx, vy, vz} {}

float ClassicalParticle::kineticEnergy() {
    return 0.5f * getMass() * (velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
}

void ClassicalParticle::describe() {
    std::cout << "Type: Classical" << "\n";
    std::cout << "Position: " << getPosition()[0] << ", " << getPosition()[1] << ", " << getPosition()[2] << "\n";
    std::cout << "Velocity: " << velocity[0] << ", " << velocity[1] << ", " << velocity[2] << "\n";
    std::cout << "Mass: " << getMass() << "\n";
}

// QuantumParticle methods
QuantumParticle::QuantumParticle(float x, float y, float z, float particleMass, double particleSpin, const std::string& particleType)
    : Particle{x, y, z, particleMass}, spin{particleSpin}, type{particleType} {}

void QuantumParticle::describe() {
    std::cout << "Type: " << type << "\n";
    std::cout << "Spin: " << spin << "\n";
    std::cout << "Position: " << getPosition()[0] << ", " << getPosition()[1] << ", " << getPosition()[2] << "\n";
    std::cout << "Mass: " << getMass() << "\n";
}
