#pragma once
#include "ParticleMan.h"
class DeadParticle : public Particle2D
{
public:
    DeadParticle(void) = default;
    ~DeadParticle(void) override = default;

    void Initialize(void) override;
    void Update(void) override;

    float g{};
    float max = 18.f;
};

