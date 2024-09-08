#include "Player.h"
#include "Texture.h"

void Player::Initialize(void)
{
    // スマートポインタの生成
    commonInfomation_ = std::make_shared<PlayerCommonInfomation>();

    // 初期設定
    behaviorMachine_.Initialize(&commonInfomation_);

    sprite0_ = std::make_unique<Sprite>();
    sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });
}

void Player::Update(void)
{
    behaviorMachine_.Update();
    sprite0_->SetPosition(commonInfomation_->position);

    commonInfomation_->position += behaviorMachine_.Get_PlayerBehaviorPtr()->Gravity();
}

void Player::MatUpdate(void)
{
    sprite0_->MatUpdate();
}

void Player::Draw(void)
{
    auto texture = LoadTexture("hae.png");
    sprite0_->Draw(texture);
}
