#pragma once
#include "ParticleMan.h"

class SmokeParticle : public Particle2D
{
public:
    SmokeParticle(void) = default;
    ~SmokeParticle(void) override = default;

    void Initialize(void) override;
    void Update(void) override {};

};

