#include "SubBoss.h"
#include "Texture.h"
#include "ImGuiManager.h"

#include "Player.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// プレイヤーのポインタ受取
	subBossInfo_.playerPtr = playerPtr;
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

	subBossSprite_->SetPosition(subBossInfo_.position);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);
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
	// ImGuiのインスタンスを取得
	ImGuiManager* imgui = ImGuiManager::GetInstance();

	// ボスの状態を表示
	imgui->Text("ボスの状態 = %s", subBossMoveTypeStr_[(size_t)currentMoveType_].c_str());

	// 攻撃状態に切替
	if (imgui->Button("攻撃状態へ")) ChangeAttack();
}

void SubBoss::InitializeSubBossInfo()
{
	// 座標とサイズと回転度の設定
	subBossInfo_.position = Vector2(500.0f, 400.0f);
	subBossInfo_.size = Vector2(256.0f, 256.0f);
	subBossInfo_.rotation = 0.0f;
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
	currentAttackState_->Update(&subBossInfo_);
}

void SubBoss::Stun()
{
}

void SubBoss::ChangeAttack()
{
	// 攻撃状態が空ではなかったら終了処理をする
	if (currentAttackState_ != nullptr) currentAttackState_->Finalize(&subBossInfo_);

	// 攻撃状態の生成、初期化
	currentAttackState_ = std::make_unique<DescentDiveState>();
	currentAttackState_->Initialize(&subBossInfo_);

	// 状態の変更
	currentMoveType_ = SubBossMoveType::Attack;
}