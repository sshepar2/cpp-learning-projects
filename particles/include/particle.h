#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <string>
#include <iostream>

class Particle {
private:
    std::array<float, 3> position;
    float mass;
public:
    Particle(float x, float y, float z, float particleMass);
    virtual ~Particle() = default;
    std::array<float, 3> getPosition() const;
    float getMass() const;
    virtual float kineticEnergy();
    virtual void describe() = 0;
};

class ClassicalParticle : public Particle {
private:
    std::array<float, 3> velocity;
public:
    ClassicalParticle(float x, float y, float z, float particleMass, float vx, float vy, float vz);
    float kineticEnergy() override;
    void describe() override;
};

class QuantumParticle : public Particle {
private:
    double spin;
    std::string type;
public:
    QuantumParticle(float x, float y, float z, float particleMass, double particleSpin, const std::string& particleType);
    void describe() override;
};

#endif
