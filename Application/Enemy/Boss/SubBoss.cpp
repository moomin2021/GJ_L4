#include "SubBoss.h"
#include "Texture.h"

#include "Player.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// プレイヤーのポインタ受取
	pPlayer_ = playerPtr;
	colMgrPtr = colMgrPtr;

	// サブボスの描画関連
	subBossSprite_ = std::make_unique<Sprite>();
	subBossSprite_->SetPosition(subBossPos_);
	subBossSprite_->SetSize(subBossSize_);
	subBossSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	subBossTextures_ = LoadDivTexture("subBossSheet.png", 3);
}

void SubBoss::Update()
{
}

void SubBoss::MatUpdate()
{
	subBossSprite_->MatUpdate();
}

void SubBoss::Draw()
{
	subBossSprite_->Draw(subBossTextures_[0]);
}

void SubBoss::Finalize()
{
}

void SubBoss::ImGuiUpdate()
{
}
