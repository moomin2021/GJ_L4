#pragma once
#include "Vector2.h"
#include "Gravity.h"

struct PlayerCommonInfomation
{
    const float kMoveSpeed = 5.f;

    // Gravity
    const float kGravity_max = 4.5f;
    const float kGravity_add = 0.1f;

    const float kJumpPower = -5.f;

    Vector2 position;
    Gravity gravity;

    void Update(void);
};

