#include "Trajectory.h"
#include "Texture.h"
#include <memory>
#include "Sprite.h"
#include "Util.h"
#include "Easing.h"

void TrajectoryParticle::Initialize(void)
{
    // flags
    isAlive = true;
    isDraw = true;

    // pos
    position_current = position_start;

    // time
    time_toDead = 4;

    // scale
    scale_start = { 1,1 };
    scale_current = { 1,1 };
    scale_end = {  1,1 };

    // size
    size = { 20.f * scale_start.x, 20.f * scale_start.y };

    // rot
    rotate_start = -45.f;
    rotate_current = {};
    rotate_end = 45.f;

    // color
    color_start = { 1,1,1,1 };
    color_current = { 1,1,1,1 };
    color_end = { 1,1,1,1 };

    // texture
    textureHandle_ = LoadTexture("star.png");
    // sprite settings
    sprite = std::make_unique<Sprite>();
    sprite->SetAnchorPoint({ 0.5f,0.5f });
    sprite->SetPosition(position_start);
    sprite->SetColor(color_start);
    sprite->SetRotation(rotate_start);
    sprite->SetSize(size);

    SbaseSize = Util::GetRandomFloat(1, 2);
    baseSize = SbaseSize;
    frequency = 1.8f;       // 周波数
    amplitude = 0.10849f;   // 振幅
    phaseOffset = 2.3253f;  // 位相オフセット
    scale_end = { M_Scale(),M_Scale() };

    int num = Util::GetRandomInt(0, 100);
    isRotateOver = num % 20 == 0;
    if (isRotateOver)
    {
        rotate_start = -37.f;
        rotate_end = 560.f;
    }


    //const Vector2& start = position_start;
    //moveVec_ = position_end;
    //const float top = 145.f;    // y
    //const float right = 1823.f; // x
    //const float bottom = 915.f; // y
    //const float left = 97.f;    // x

    //float t_top = (top - start.y) / moveVec_.y;
    //float t_bottom = (bottom - start.y) / moveVec_.y;
    //float t_left = (left - start.x) / moveVec_.x;
    //float t_right = (right - start.x) / moveVec_.x;

    //Vector2 intersect_top = { start.x + t_top * moveVec_.x, top };
    //Vector2 intersect_bottom = { start.x + t_bottom * moveVec_.x, bottom };
    //Vector2 intersect_left = { left, start.y + t_left * moveVec_.y };
    //Vector2 intersect_right = { right, start.y + t_right * moveVec_.y };

    //Vector2 intersection = { 0, 0 };
    //if (t_top > 0 && intersect_top.x >= left && intersect_top.x <= right) { intersection = intersect_top; }
    //else if (t_bottom > 0 && intersect_bottom.x >= left && intersect_bottom.x <= right) { intersection = intersect_bottom; }
    //else if (t_left > 0 && intersect_left.y >= top && intersect_left.y <= bottom) { intersection = intersect_left; }
    //else if (t_right > 0 && intersect_right.y >= top && intersect_right.y <= bottom) { intersection = intersect_right; }

    //Vector2 displacement{};
    //displacement.x = intersection.x - start.x;  // x方向に進む量
    //displacement.y = intersection.y - start.y;  // y方向に進む量

    //moveVec_ = displacement;
}

void TrajectoryParticle::Update(void)
{
    Particle2D::Update();

    float elapsed1 = time_toCurrent / time_toDead;
    elapsed1 = Util::Clamp(elapsed1, 1.0f, 0.0f);
    baseSize = Easing::lerp(SbaseSize, 0.0f, elapsed1);

    float elapsed2 = time_toCurrent / time_toDead;
    elapsed2 = Util::Clamp(elapsed2, 1.0f, 0.0f);
    float mSize = Easing::Cubic::easeIn(0.0f, 1.f, elapsed2);

    Vector2 scale{M_Scale(),M_Scale()};
    scale.x -= mSize;
    scale.y -= mSize;
    Vector2 s = { size.x * scale.x, size.y * scale.y };
    sprite->SetSize(s);

    //float elapsed = time_toCurrent / time_toDead;
    //elapsed = Util::Clamp(elapsed, 1.0f, 0.0f);
    //elapsed = Easing::Cubic::easeInOut(rotate_start, rotate_end, elapsed);
    //sprite->SetRotation(elapsed);

    rotate_current = M_Rotate(time_toCurrent, rotate_start, rotate_end, 2.f);
    sprite->SetRotation(rotate_current);

    float elapsed3 = time_toCurrent / time_toDead;
    elapsed3 = Util::Clamp(elapsed3, 1.0f, 0.0f);
    color_current.w = Easing::lerp(1.f, 0.0f, elapsed3);
    sprite->SetColor(color_current);
}
