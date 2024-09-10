#include "Move.h"

void Move::Update(void)
{
    // 1F前の物として記録
    inputVel_old = inputVel_current;
    velocity_old = velocity_current;
    direction_old = direction_current;

    // 初期化
    inputVel_current = {};
    velocity_current = {};
    direction_current = {};
}
