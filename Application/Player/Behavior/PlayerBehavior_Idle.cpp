#include "PlayerBehavior_Idle.h"

void PlayerBehavior_Idle::Entry(void)
{
    // 絵のずれをアンカーポイントで無理矢理補正
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_idle);

    // アニメーションタイマーを初期化
    commonInfomation_->timer_idleAnimation = 0.f;
    // アニメーションインターバルを初期化
    commonInfomation_->timer_idleInterval = 0.f;
}

void PlayerBehavior_Idle::Execute(void)
{
    // 加算値
    float delta = TimeManager::GetInstance()->GetGameDeltaTime();
    // 最大値
    float max = commonInfomation_->kTime_IdleAnimation_max;

    // 現在地に加算
    commonInfomation_->timer_idleAnimation += delta;
    // 最大値を超えないように
    commonInfomation_->timer_idleAnimation = (std::min)(commonInfomation_->timer_idleAnimation, max);

    // 現在値
    float cur = commonInfomation_->timer_idleAnimation;
    // 分割数
    int32_t divide = commonInfomation_->kNum_IdleSprite_max;
    // 区間
    float range = max / divide;
    // 連番の何枚目を表示すべきか指定
    commonInfomation_->num_idleSprite = (std::min)(static_cast<int>(cur / range), divide - 1); // 最大値3

    // 方向に応じて絵を反転
    commonInfomation_->move.direction_current == DIRECTION_RIGHT ?
        commonInfomation_->sprite_player->SetFlipX(true) :
        commonInfomation_->sprite_player->SetFlipX(false);

    // アニメーションが終了していないならスキップ
    if (cur < max) { return; }
    // インターバルの最大値
    float max_interval = commonInfomation_->kTime_IdleInterval_max;
    // インターバルの現在値に加算
    commonInfomation_->timer_idleInterval += delta;

    // インターバルが最大値を超えていないならスキップ
    if (commonInfomation_->timer_idleInterval < max_interval) { return; }
    // アニメーションタイマーを初期化
    commonInfomation_->timer_idleAnimation = 0.f;
    commonInfomation_->timer_idleInterval = 0.f;
}

void PlayerBehavior_Idle::Exit(void)
{
}
