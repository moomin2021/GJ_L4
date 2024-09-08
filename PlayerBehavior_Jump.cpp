#include "PlayerBehavior_Jump.h"

void PlayerBehavior_Jump::Entry(void)
{
    commonInfomation_->position += Jump();
}

void PlayerBehavior_Jump::Execute(void)
{
}

void PlayerBehavior_Jump::Exit(void)
{
}
