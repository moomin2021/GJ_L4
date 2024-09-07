#include "Player.h"

void Player::Initialize(void)
{
    // スマートポインタの生成
    commonInfomation_ = std::make_shared<PlayerCommonInfomation>();

    // 初期設定
    behaviorMachine_.Initialize(&commonInfomation_);
}

void Player::Update(void)
{
    behaviorMachine_.Update();
}
