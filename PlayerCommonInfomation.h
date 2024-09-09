#pragma once
#include "Vector2.h"
#include "Gravity.h"
#include "M_RectCollider.h"
#include "Sprite.h"
#include <memory>
#include "TimeManager.h"

struct PlayerCommonInfomation
{
    //-Const-------------------------
    // Move
    const float kMoveSpeed = 5.f;

    // Gravity
    const float kGravity_max = 4.5f;
    const float kGravity_add = 0.1f;

    // Jump
    const float kJumpPower = -5.f;

    // Collider
    const Vector2 kLength_collider = { 20,20 };
    const Vector2 kLength_attackCollider = { 20,20 };
    const Vector2 kOffset_attackCollider = { 0 ,30 };

    // Time
    const float kAttackInterval_max = 20.f; // sec
    const float kInvincible_max = 20.f;     // sec

    //-Variable-----------------------------
    Vector2 position{};
    Gravity gravity{};
    float timer_attackInterval{};
    float timer_invincible{};

    // Collider
    M_ColliderManager* ptr_colliderManager{};
    M_RectCollider collider{};

    // sprite
    bool is_drawCollider{};
    std::unique_ptr<Sprite> sprite_collider = nullptr;
    std::unique_ptr<Sprite> sprite_attackCollider = nullptr;

    void Update(void);
};

