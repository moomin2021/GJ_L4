#include "BaseMinion.h"

BaseMinion::BaseMinion() : sprites_(3), textures_(3) {}

void BaseMinion::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, const std::vector<uint16_t>& inTextures)
{
	// パラメーターを設定
	stats_ = inStats;
	// テクスチャの設定
	textures_ = inTextures;

	// スプライトの生成と設定
	for (auto& it : sprites_) {
		it = std::make_unique<Sprite>();
		it->SetPosition(stats_.position);
		it->SetSize(Vector2(64.0f, 64.0f));
		it->SetAnchorPoint({ 0.5f, 0.5f });
	}

	// コライダーの設定
	collider_.circle_.center = stats_.position;
	collider_.circle_.radius = 32.0f;
	std::string name = "Minion";
	auto callback = std::bind(&BaseMinion::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
}

void BaseMinion::MatUpadte()
{
	for (auto& it : sprites_) it->MatUpdate();
}

void BaseMinion::Draw()
{
	for (size_t i = 0; i < sprites_.size(); i++) sprites_[i]->Draw(textures_[i]);
}

void BaseMinion::Finalize()
{
	collider_.Finalize();
}