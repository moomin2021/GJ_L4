#include "PlayerBehavior_Jump.h"

void PlayerBehavior_Jump::Entry(void)
{
    Jump();
}

void PlayerBehavior_Jump::Execute(void)
{
}

void PlayerBehavior_Jump::Exit(void)
{
}

void PlayerBehavior_Jump::Jump(void)
{
    commonInfomation_->gravity.Set_Current(commonInfomation_->kJumpPower);
    commonInfomation_->move.can_jump = false;
}
