#include "BossCol.h"
#include "Texture.h"

#include "Boss.h"

void BossCol::Initialize(Boss* bossPtr, M_ColliderManager* colMgrPtr, const Vector2& inCenter, const Vector2& inLength, size_t id)
{
	// ボスポインタを取得
	pBoss_ = bossPtr;

	// コライダーの設定
	collider_.square_.center = inCenter;
	collider_.square_.length = inLength;
	std::string name = "Boss" + std::to_string(id);
	auto callback = std::bind(&BossCol::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);

	// テクスチャの読み込み
	debugTexture_ = LoadTexture("white.png");

	// スプライトの生成、設定
	debugSprite_ = std::make_unique<Sprite>();
	debugSprite_->SetPosition(inCenter);
	debugSprite_->SetSize(inLength);
	debugSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	debugSprite_->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });
}

void BossCol::Update()
{
}

void BossCol::MatUpdate()
{
	debugSprite_->MatUpdate();
}

void BossCol::Draw(bool isDebug)
{
	// デバック状態なら描画
	if (isDebug == false) return;
	debugSprite_->Draw(debugTexture_);
}

void BossCol::CollisionCallBack()
{
	// 敵と衝突したらダメージを受ける
	if (collider_.IsDetect_Name("Minion")) {
		// 敵のコライダーを取得
		ICollider* hitCol = collider_.Extract_Collider("Minion");
		float damage = hitCol->Data_Get<float>("Wall_Damage");
		if (damage > 0) pBoss_->AddDamage(damage);
	}
}