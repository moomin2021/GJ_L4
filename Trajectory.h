#pragma once
#include "ParticleMan.h"
#include <cmath>

class TrajectoryParticle : public Particle2D
{
public:
    TrajectoryParticle(void) = default;
    ~TrajectoryParticle(void) override = default;

    void Initialize(void) override;
    void Update(void) override;

private:
    float M_Scale(void) { return amplitude * std::sinf(frequency * time_toCurrent * phaseOffset) + baseSize; }
    float M_Rotate(float time, float min, float max, float period) { return min + (max - min) * (std::sin(time * period) + 1.f) / 2.f; }

    float frequency;
    float amplitude;
    float phaseOffset;
    float baseSize = 1.f;

    bool isRotateOver{};
};

