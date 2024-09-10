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

    Vector2 input{};
    input.x = (float)(key->PushKey(DIK_D) - key->PushKey(DIK_A));

    Vector2 velocity{};
    velocity.x = input.x * commonInfomation_->kMoveSpeed;

    // 入力があった時のみ変更
    if (input.x > 0) { commonInfomation_->direction = DIRECTION_RIGHT; }
    else if (input.x < 0) { commonInfomation_->direction = DIRECITON_LEFT; }

#ifdef _DEBUG
    velocity.y = (float)(key->PushKey(DIK_S) - key->PushKey(DIK_W));
    velocity.y = velocity.y * commonInfomation_->kMoveSpeed;
    if (key->PushKey(DIK_LSHIFT)) { velocity *= 2; }
#endif // _DEBUG

    return velocity;
}
