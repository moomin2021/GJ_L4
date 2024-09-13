#include "DeadParticle.h"
#include "Texture.h"
#include "Util.h"
#include "Easing.h"

void DeadParticle::Initialize(void)
{
    // flags
    isAlive = true;
    isDraw = true;

    // pos
    position_current = position_start;

    // time
    time_toDead = 10;

    // scale
    scale_start = { 1,1 };
    scale_current = { 1,1 };
    scale_end = { 2,2};

    // size
    size = { 50.f * scale_start.x, 50.f * scale_start.y };

    // rot
    rotate_start = 0;
    rotate_current = {};
    rotate_end = 360;

    // color
    color_start = { 1,1,1,1 };
    color_current = { 1,1,1,1 };
    color_end = { 1,1,1,1 };

    // texture
    textureHandle_ = LoadTexture("starPP.png");
    // sprite settings
    sprite = std::make_unique<Sprite>();
    sprite->SetAnchorPoint({ 0.5f,0.5f });
    sprite->SetPosition(position_start);
    sprite->SetColor(color_start);
    sprite->SetRotation(rotate_start);
    sprite->SetSize(size);
}

void DeadParticle::Update(void)
{
    Particle2D::Update();

    float elapsed = time_toCurrent / time_toDead;
    elapsed = Util::Clamp(elapsed, 1.0f, 0.0f);

    g += 0.3f;
    g = (std::min)(g, max);

    rotate_current += 2.5f;
    sprite->SetRotation(rotate_current);

    scale_current.x = Easing::lerp(scale_start.x, scale_end.x, elapsed);
    scale_current.y = Easing::lerp(scale_start.y, scale_end.y, elapsed);
    size = { 60.f * scale_start.x, 60.f * scale_start.y };
    sprite->SetSize(size);

    position_end.y += g;

    position_current.x = Easing::Cubic::easeOut(position_start.x, position_end.x, elapsed);
    position_current.y = Easing::Cubic::easeOut(position_start.y, position_end.y, elapsed);
    sprite->SetPosition(position_current);
}
