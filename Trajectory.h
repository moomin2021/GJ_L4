#pragma once
#include "ParticleMan.h"
class TrajectoryParticle : public Particle2D
{
    TrajectoryParticle(void) = default;
    ~TrajectoryParticle(void) override = default;

    void Initialize(void) override;
    void Update(void) override;
};

