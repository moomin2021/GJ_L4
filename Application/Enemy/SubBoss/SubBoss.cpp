#include "SubBoss.h"
#include "Texture.h"
#include "ImGuiManager.h"

#include "CollisionChecker.h"
#include "Player.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// プレイヤーのポインタ受取
	subBossInfo_.playerPtr = playerPtr;

	// サブボスの情報の初期化処理
	InitializeSubBossInfo(colMgrPtr);

	// サブボス描画関連
	// スプライトの生成、設定
	subBossSprite_ = std::make_unique<Sprite>();
	subBossSprite_->SetPosition(subBossInfo_.position);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	// テクスチャの読み込み
	subBossTextures_ = LoadDivTexture("subBossSheet.png", 3);

	// デバック関連
	// スプライトの生成、設定
	colSprite_ = std::make_unique<Sprite>();
	colSprite_->SetPosition(subBossInfo_.position);
	colSprite_->SetSize({ subBossInfo_.collider.circle_.radius * 2.0f, subBossInfo_.collider.circle_.radius * 2.0f });
	colSprite_->SetAnchorPoint({0.5f, 0.5f});
	colSprite_->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });
	// テクスチャ読み込み
	debugTexture_ = LoadTexture("circle.png");
}

void SubBoss::Update()
{
	// 状態別更新処理
	(this->*stateTable[(size_t)currentMoveType_])();

	// スプライトの更新
	subBossSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);
}

void SubBoss::MatUpdate()
{
	subBossSprite_->MatUpdate();
	colSprite_->MatUpdate();
}

void SubBoss::Draw()
{
	subBossSprite_->Draw(subBossTextures_[0]);
	if (isDebug_) colSprite_->Draw(debugTexture_);
}

void SubBoss::Finalize()
{
	subBossInfo_.collider.Finalize();
}

void SubBoss::ImGuiUpdate()
{
	// ImGuiのインスタンスを取得
	ImGuiManager* imgui = ImGuiManager::GetInstance();

	// ボスの状態を表示
	imgui->Text("ボスの状態 = %s", subBossMoveTypeStr_[(size_t)currentMoveType_].c_str());

	// 当たり判定を表示するか
	imgui->CheckBox("当たり判定表示", isDebug_);

	// 攻撃状態に切替
	if (imgui->Button("攻撃状態へ")) ChangeAttack();
}

void SubBoss::InitializeSubBossInfo(M_ColliderManager* colMgrPtr)
{
	// 座標とサイズと回転度の設定
	subBossInfo_.position = Vector2(500.0f, 400.0f);
	subBossInfo_.size = Vector2(256.0f, 256.0f);
	subBossInfo_.rotation = 0.0f;

	// コライダーの設定
	subBossInfo_.collider.circle_.center = subBossInfo_.position;
	subBossInfo_.collider.circle_.radius = 82.0f;
	std::string name = "SubBoss";
	auto callBack = std::bind(&SubBoss::CollisionCallBack, this);
	subBossInfo_.collider.Initialize(name, callBack, colMgrPtr);
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

void SubBoss::CollisionCallBack()
{
	// 壁との衝突判定
	for (size_t i = 0; i < 4; i++) {
		// 壁と当たったら
		if (subBossInfo_.collider.IsDetect_Name("Boss" + std::to_string(i))) {
			// 押し出し処理
			ICollider* hitCol = subBossInfo_.collider.Extract_Collider("Boss" + std::to_string(i));
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, subBossInfo_.collider.circle_);
			subBossInfo_.position += pushBack;
		}
	}

	// スプライトの更新
	subBossSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);
}