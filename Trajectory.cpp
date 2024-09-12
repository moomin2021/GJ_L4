#include "Trajectory.h"
#include "Texture.h"
#include <memory>
#include "Sprite.h"

void TrajectoryParticle::Initialize(void)
{
    Particle2D;

    // flags
    isAlive = true;
    isDraw = true;

    // pos

    // time
    time_toDead = 1000;

    // size
    size = { size.x * scale_start.x, size.y * scale_start.y };

    // scale
    scale_start = { 1,1 };
    scale_end = { 1,1 };

    // rot
    rotate_start = 0.f;
    rotate_end = 0.f;

    // color
    color_start = { 1,1,1,1 };
    color_end = { 1,1,1,1 };

    // texture
    textureHandle_ = LoadTexture("smoke.png");
    // sprite settings
    sprite = std::make_unique<Sprite>();
    sprite->SetAnchorPoint({ 0.5f,0.5f });
    sprite->SetPosition(position_start);
    sprite->SetColor(color_start);
    sprite->SetRotation(rotate_start);
    sprite->SetSize(size);
}

void TrajectoryParticle::Update(void)
{
    Particle2D::Update();
}
