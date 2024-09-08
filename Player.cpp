#include "Player.h"
#include "Texture.h"

Player::~Player(void)
{
    commonInfomation_->collider.Finalize();
}

void Player::Initialize(M_ColliderManager* arg_colliderManagerPtr)
{
    // スマートポインタの生成
    commonInfomation_ = std::make_shared<PlayerCommonInfomation>();

    // 初期設定
    behaviorMachine_.Initialize(&commonInfomation_);

    // スプライト
    sprite0_ = std::make_unique<Sprite>();
    sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    // 重力
    commonInfomation_->gravity.Initialize(commonInfomation_->kGravity_max, commonInfomation_->kGravity_add);

    //** コライダー
    // メンバ変数の設定
    commonInfomation_->collider.square_.center = commonInfomation_->position;
    commonInfomation_->collider.square_.length = commonInfomation_->kLength;
    // ローカル変数
    std::string name = "Player";
    auto callback = std::bind(&Player::CallBack, this);
    // 初期化関数
    commonInfomation_->collider.Initialize(name, callback, arg_colliderManagerPtr);
}

void Player::Update(void)
{
    behaviorMachine_.Update();
    sprite0_->SetPosition(commonInfomation_->position);

    commonInfomation_->Update();
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

void Player::CallBack(void)
{
}
