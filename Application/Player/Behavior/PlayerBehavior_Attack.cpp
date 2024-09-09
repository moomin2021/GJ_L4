#include "PlayerBehavior_Attack.h"

void PlayerBehavior_Attack::Entry(void)
{
    //** コライダー
    // メンバ変数の設定
    auto position = commonInfomation_->position + commonInfomation_->kOffset_attackCollider;
    collider_attack_.square_.center = position;
    collider_attack_.square_.length = commonInfomation_->kLength_attackCollider;
    // ローカル変数
    std::string name = "Player_Attack";
    auto callback = std::bind(&PlayerBehavior_Attack::Callback, this);
    // 初期化関数
    collider_attack_.Initialize(name, callback, commonInfomation_->ptr_colliderManager);
}

void PlayerBehavior_Attack::Execute(void)
{
}

void PlayerBehavior_Attack::Exit(void)
{
    collider_attack_.Finalize();
}

void PlayerBehavior_Attack::Callback(void)
{
}
