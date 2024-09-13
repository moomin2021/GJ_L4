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
	if (isOutlineDraw_) sprites_[0]->Draw(data_->textures[0]);
	sprites_[1]->Draw(data_->textures[1]);
	sprites_[2]->Draw(data_->textures[2]);
}

void BaseMinion::Finalize()
{
	collider_.Finalize();
}