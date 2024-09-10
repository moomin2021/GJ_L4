#include "PlayerCommonInfomation.h"

void PlayerCommonInfomation::Update(void)
{
    collider.square_.center = position;
    gravity.Update();
}
