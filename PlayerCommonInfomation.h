#pragma once
#include "Vector2.h"

struct PlayerCommonInfomation
{
    const float kMoveSpeed = 5.f;
    const float kGravity = 0.3f;
    const float kJumpPower = -5.f;

    Vector2 position;
};

