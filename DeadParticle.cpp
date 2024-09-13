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
    size = { 20.f * scale_start.x, 20.f * scale_start.y };

    // rot
    rotate_start = 0;
    rotate_current = {};
    rotate_end = 360;

    // color
    color_start = { 1,1,1,1 };
    color_current = { 1,1,1,1 };
    color_end = { 1,1,1,1 };

    // texture
    textureHandle_ = LoadTexture("star5.png");
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
    float elapsed = time_toCurrent / time_toDead;
    elapsed = Util::Clamp(elapsed, 1.0f, 0.0f);
    rotate_current = Easing::lerp(rotate_start, rotate_end, elapsed);
    sprite->SetRotation(rotate_current);
}
