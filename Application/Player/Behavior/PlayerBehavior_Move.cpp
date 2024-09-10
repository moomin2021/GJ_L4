#include "PlayerBehavior_Move.h"
#include "Key.h"

void PlayerBehavior_Move::Entry(void)
{
}

void PlayerBehavior_Move::Execute(void)
{
    commonInfomation_->position += Move();

    // 方向に応じて絵を反転
    commonInfomation_->move.direction_current == DIRECTION_RIGHT ?
        commonInfomation_->sprite_player->SetFlipX(true) :
        commonInfomation_->sprite_player->SetFlipX(false);
}

void PlayerBehavior_Move::Exit(void)
{
}

Vector2 PlayerBehavior_Move::Move(void)
{
    auto key = Key::GetInstance();
    const auto& keyBind = commonInfomation_->keyBind;

    Vector2 input{};
    input.x = (float)(key->PushKey(keyBind.move_right) - key->PushKey(keyBind.move_left));

    Vector2 velocity{};
    velocity.x = input.x * commonInfomation_->kMoveSpeed;

    // 入力があった時のみ変更
    if (input.x > 0) { commonInfomation_->move.direction_current = DIRECTION_RIGHT; }
    else if (input.x < 0) { commonInfomation_->move.direction_current = DIRECITON_LEFT; }

#ifdef _DEBUG
    velocity.y = (float)(key->PushKey(keyBind.move_down) - key->PushKey(keyBind.move_up));
    velocity.y = velocity.y * commonInfomation_->kMoveSpeed;
    if (key->PushKey(DIK_LSHIFT)) { velocity *= 2; }
#endif // _DEBUG

    // どの程度移動したか記録する
    commonInfomation_->move.velocity_current += velocity;
    return velocity;
}
