#include "PlayerBehavior_Move.h"
#include "Key.h"
#include "Pad.h"

void PlayerBehavior_Move::Entry(void)
{
}

void PlayerBehavior_Move::Execute(void)
{
    commonInfomation_->position += Move();

    // 加算値
    float delta = TimeManager::GetInstance()->GetGameDeltaTime();
    // 最大値
    float max = commonInfomation_->kTime_MoveAnimation_max;

    // 現在地に加算
    commonInfomation_->timer_moveAnimation += delta;
    // 最大値を超えないように
    commonInfomation_->timer_moveAnimation = (std::min)(commonInfomation_->timer_moveAnimation, max);

    // 現在値
    float cur = commonInfomation_->timer_moveAnimation;
    // 分割数
    int32_t divide = commonInfomation_->kNum_MoveSprite_max;
    // 区間
    float range = max / divide;
    // 連番の何枚目を表示すべきか指定
    commonInfomation_->num_moveSprite = (std::min)(static_cast<int>(cur / range), divide - 1); // 最大値3

    // 方向に応じて絵を反転
    commonInfomation_->move.direction_current == DIRECTION_RIGHT ?
        commonInfomation_->sprite_player->SetFlipX(true) :
        commonInfomation_->sprite_player->SetFlipX(false);

    // アニメーションが終了していないならスキップ
    if (cur < max) { return; }
    // インターバルの最大値
    float max_interval = commonInfomation_->kTime_MoveInterval_max;
    // インターバルの現在値に加算
    commonInfomation_->timer_moveInterval += delta;

    // インターバルが最大値を超えていないならスキップ
    if (commonInfomation_->timer_moveInterval < max_interval) { return; }
    // アニメーションタイマーを初期化
    commonInfomation_->timer_moveAnimation = 0.f;
    commonInfomation_->timer_moveInterval = 0.f;
}

void PlayerBehavior_Move::Exit(void)
{
}

Vector2 PlayerBehavior_Move::Move(void)
{
    auto key = Key::GetInstance();
    auto pad = Pad::GetInstance();
    const auto& keyBind = commonInfomation_->keyBind;

    Vector2 input{};
    input.x = (float)(key->PushKey(keyBind.move_right) - key->PushKey(keyBind.move_left));
    input.x += pad->GetLStick().x;

    Vector2 velocity{};
    velocity.x = input.x * commonInfomation_->kMoveSpeed * TimeManager::GetInstance()->GetDeltaTime();

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
