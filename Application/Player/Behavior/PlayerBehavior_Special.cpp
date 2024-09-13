#include "PlayerBehavior_Special.h"
#include "PlayerBehavior_Attack.h"
#include "TimeManager.h"

void PlayerBehavior_Special::Entry(void)
{
    direction_Entry_ = commonInfomation_->move.direction_current;

    Vector2 offset = commonInfomation_->kCollision_positionOffset_playerCollider_special;
    if (direction_Entry_ == DIRECTION_RIGHT && offset.x < 0) { offset.x *= -1; }
    else if (direction_Entry_ == DIRECITON_LEFT && offset.x > 0) { offset.x *= -1; }

    //** コライダー
    // メンバ変数の設定
    auto position = commonInfomation_->position + offset;
    collider_special_.square_.center = position;
    collider_special_.square_.length = commonInfomation_->kCollision_Length_playerCollider_special;
    // ローカル変数
    std::string name = "Player_Special";
    auto callback = std::bind(&PlayerBehavior_Special::Callback, this);
    // 初期化関数
    collider_special_.Initialize(name, callback, commonInfomation_->ptr_colliderManager);

    // アニメーションタイマーを初期化
    commonInfomation_->timer_specialAnimation = 0.f;

    // 絵のずれをアンカーポイントで無理矢理補正
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_special);
}

void PlayerBehavior_Special::Execute(void)
{
    Vector2 offset = commonInfomation_->kCollision_positionOffset_playerCollider_special;
    if (direction_Entry_ == DIRECTION_RIGHT && offset.x < 0) { offset.x *= -1; }
    else if (direction_Entry_ == DIRECITON_LEFT && offset.x > 0) { offset.x *= -1; }

    auto position = commonInfomation_->position + offset;
    collider_special_.square_.center = position;

    // 加算値
    float delta = TimeManager::GetInstance()->GetGameDeltaTime();
    // 最大値
    float max = commonInfomation_->kTime_SpecialAnimation_max;

    // 現在地に加算
    commonInfomation_->timer_specialAnimation += delta;
    // 最大値を超えないように
    commonInfomation_->timer_specialAnimation = (std::min)(commonInfomation_->timer_specialAnimation, max);

    // 現在値
    float cur = commonInfomation_->timer_specialAnimation;
    // 分割数
    int32_t divide = commonInfomation_->kNum_SpecialSprite_max;
    // 区間
    float range = max / divide;
    // 連番の何枚目を表示すべきか指定
    commonInfomation_->num_specialSprite = (std::min)(static_cast<int>(cur / range), commonInfomation_->kNum_SpecialSprite_max - 1); // 最大値4

    // 方向に応じて絵を反転
    commonInfomation_->move.direction_current == DIRECTION_RIGHT ?
        commonInfomation_->sprite_player->SetFlipX(true) :
        commonInfomation_->sprite_player->SetFlipX(false);
}

void PlayerBehavior_Special::Exit(void)
{
    // コライダー終了処理
    collider_special_.Finalize();
}

void PlayerBehavior_Special::Callback(void)
{
}

