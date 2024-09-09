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
    velocity.x = (float)(key->PushKey(DIK_D) - key->PushKey(DIK_A));
    velocity.y = (float)(key->PushKey(DIK_S) - key->PushKey(DIK_W));
    velocity.x = velocity.x * commonInfomation_->kMoveSpeed;
    velocity.y = velocity.y * commonInfomation_->kMoveSpeed;
    if (key->PushKey(DIK_LSHIFT)) { velocity *= 2; }

    return velocity;
}
