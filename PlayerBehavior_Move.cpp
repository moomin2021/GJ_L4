#include "PlayerBehavior_Move.h"
#include "Key.h"

void PlayerBehavior_Move::Entry(void)
{
}

void PlayerBehavior_Move::Execute(void)
{
    commonInfomation_->position += Move();
}

void PlayerBehavior_Move::Exit(void)
{
}

Vector2 PlayerBehavior_Move::Move(void)
{
    auto key = Key::GetInstance();

    Vector2 velocity{};
    velocity.x = (float)(key->PushKey(DIK_D) + key->PushKey(DIK_A));
    velocity.x = velocity.x * commonInfomation_->kMoveSpeed;

    return velocity;
}
