#include "PlayerBehavior_Attack.h"
#include "TimeManager.h"

void PlayerBehavior_Attack::Entry(void)
{
    //** コライダー
    // メンバ変数の設定
    auto position = commonInfomation_->position + commonInfomation_->kCollision_positionOffset_playerCollider_attack;
    collider_attack_.square_.center = position;
    collider_attack_.square_.length = commonInfomation_->kCollision_Length_playerCollider_attack;
    // ローカル変数
    std::string name = "Player_Attack";
    auto callback = std::bind(&PlayerBehavior_Attack::Callback, this);
    // 初期化関数
    collider_attack_.Initialize(name, callback, commonInfomation_->ptr_colliderManager);

    // アニメーションタイマーを初期化
    commonInfomation_->timer_attackAnimation = 0.f;

    // 絵のずれをアンカーポイントで無理矢理補正
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_attack);
}

void PlayerBehavior_Attack::Execute(void)
{
    // 加算値
    float delta = TimeManager::GetInstance()->GetGameDeltaTime();
    // 最大値
    float max = commonInfomation_->kTime_AttackAnimation_max;

    // 現在地に加算
    commonInfomation_->timer_attackAnimation += delta;
    // 最大値を超えないように
    commonInfomation_->timer_attackAnimation = (std::min)(commonInfomation_->timer_attackAnimation, max);

    // 現在値
    float cur = commonInfomation_->timer_attackAnimation;
    // 分割数
    int32_t divide = commonInfomation_->kNum_AttackSprite_max;
    // 区間
    float range = max / divide;
    // 連番の何枚目を表示すべきか指定
    commonInfomation_->num_attackSprite = (std::min)(static_cast<int>(cur / range), commonInfomation_->kNum_AttackSprite_max - 1); // 最大値4

    // 方向に応じて絵を反転
    commonInfomation_->direction == DIRECTION_RIGHT ?
        commonInfomation_->sprite_player->SetFlipX(true) :
        commonInfomation_->sprite_player->SetFlipX(false);
}

void PlayerBehavior_Attack::Exit(void)
{
    // コライダー終了処理
    collider_attack_.Finalize();
}

void PlayerBehavior_Attack::Callback(void)
{
}
