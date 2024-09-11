#pragma once
#include "Direction.h"
#include "Vector2.h"

struct Move
{
    Move(void) = default;
    ~Move(void) = default;

    void Update(void);

    // 入力
    Vector2 inputVel_current{};
    Vector2 inputVel_old{};

    // 移動値
    Vector2 velocity_current{};
    Vector2 velocity_old{};

    bool is_ground{};
    bool can_jump{};
    Direction direction_current{};
    Direction direction_old{};
};

