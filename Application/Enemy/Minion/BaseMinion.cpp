#include "BaseMinion.h"

using namespace EnemyStatus;

BaseMinion::BaseMinion() : sprites_(3) {}

void BaseMinion::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	colMgrPtr = colMgrPtr;
	// パラメーターを設定
	stats_ = inStats;
	// データの設定
	data_ = inData;

	// スプライトの生成と設定
	for (auto& it : sprites_) {
		it = std::make_unique<Sprite>();
		it->SetPosition(stats_.position);
		it->SetSize(Vector2(64.0f, 64.0f));
		it->SetAnchorPoint({ 0.5f, 0.5f });
	}
}

void BaseMinion::MatUpdate()
{
	for (auto& it : sprites_) it->MatUpdate();
}

void BaseMinion::Draw()
{
	for (size_t i = 0; i < sprites_.size(); i++) sprites_[i]->Draw(data_->textures[i]);
}

void BaseMinion::Finalize()
{
	collider_.Finalize();
}