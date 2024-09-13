#include "IPlayerBehavior.h"
#include "Key.h"
#include "Pad.h"

IPlayerBehavior::IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation)
{
    commonInfomation_ = arg_commonInfomation;
}

Vector2 IPlayerBehavior::Gravity(void)
{
    return Vector2(0, commonInfomation_->gravity.current_);
}

Vector2 IPlayerBehavior::Move(void)
{
    auto key = Key::GetInstance();
    auto pad = Pad::GetInstance();
    const auto& keyBind = commonInfomation_->keyBind;

    Vector2 input{};
    input.x = (float)(key->PushKey(keyBind.move_right) - key->PushKey(keyBind.move_left));
    input.x += pad->GetLStick().x;

    Vector2 velocity{};
    velocity.x = input.x * commonInfomation_->kMoveSpeed * TimeManager::GetInstance()->GetGameDeltaTime();

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
