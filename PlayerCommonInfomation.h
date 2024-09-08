#pragma once
#include "Vector2.h"
#include "Gravity.h"
#include "M_RectCollider.h"

struct PlayerCommonInfomation
{
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

    Vector2 position{};
    Gravity gravity{};

    M_ColliderManager* ptr_colliderManager{};
    M_RectCollider collider{};

    void Update(void);
};

