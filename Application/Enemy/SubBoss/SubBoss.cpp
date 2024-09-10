#include "SubBoss.h"
#include "Texture.h"

#include "Player.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// プレイヤーのポインタ受取
	pPlayer_ = playerPtr;
	colMgrPtr = colMgrPtr;

	// サブボスの情報の初期化処理
	InitializeSubBossInfo();

	// サブボス描画関連
	// スプライトの生成、設定
	subBossSprite_ = std::make_unique<Sprite>();
	subBossSprite_->SetPosition(subBossInfo_.position);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	// テクスチャの読み込み
	subBossTextures_ = LoadDivTexture("subBossSheet.png", 3);
}

void SubBoss::Update()
{
	// 状態別更新処理
	(this->*stateTable[(size_t)currentMoveType_])();
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

void SubBoss::InitializeSubBossInfo()
{
	// 座標とサイズと回転度の設定
	subBossInfo_.position = Vector2(960.0f, 400.0f);
	subBossInfo_.size = Vector2(256.0f, 256.0f);
	subBossInfo_.rotation = 0;
}

void (SubBoss::*SubBoss::stateTable[]) () = {
	&SubBoss::Wait,
	&SubBoss::Attack,
	&SubBoss::Stun,
};

void SubBoss::Wait()
{
}

void SubBoss::Attack()
{
}

void SubBoss::Stun()
{
}
