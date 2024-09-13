#include "SubBoss.h"
#include "Texture.h"
#include "ImGuiManager.h"

#include "CollisionChecker.h"
#include "Player.h"
#include "EnemyManager.h"

#include "MoveTypes/DescentDive.h"
#include "MoveTypes/StartIntro.h"
#include "MoveTypes/EndGameOutro.h"
#include "MoveTypes/SummonMinions.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr, MinionFactory* minionFactoryPtr, EnemyManager* enemyMgrPtr)
{
	// プレイヤーのポインタ受取
	subBossInfo_.playerPtr = playerPtr;

	// サブボスの情報の初期化処理
	InitializeSubBossInfo(colMgrPtr, cameraPtr, minionFactoryPtr, enemyMgrPtr);

	// サブボス描画関連
	// スプライトの生成、設定
	subBossSprite_ = std::make_unique<Sprite>();
	subBossSprite_->SetPosition(subBossInfo_.position);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	subBossSprite_->SetColor(subBossInfo_.mainColor);
	// テクスチャの読み込み
	subBossTextures_ = LoadDivTexture("subBossSheet.png", 3);
	// スプライトの生成、設定
	subBossEyeSprite_ = std::make_unique<Sprite>();
	subBossEyeSprite_->SetPosition(subBossInfo_.position);
	subBossEyeSprite_->SetSize(subBossInfo_.size);
	subBossEyeSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	subBossEyeSprite_->SetColor(subBossInfo_.eyeColor);
	// テクスチャの読み込み
	subBossEyeTexture_ = LoadTexture("SubBossEye.png");

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
	// 行動の抽選
	MoveChance();

	// ダメージ処理
	DamageProcess();

	// ボスが死んだら
	if (subBossInfo_.enemyMgrPtr->GetIsBossAlive() == false && isGameClear_ == false) {
		// クリアフラグをONにする
		isGameClear_ = true;
		// 終了演出
		currentMoveType_ = SubBossMoveType::EndGameOutro;
		// 行動の生成
		ChangeMove();
	}

	// 状態別更新処理
	(this->*stateTable[(size_t)currentStateType_])();

	// スプライトの更新
	subBossSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);
	subBossSprite_->SetColor(subBossInfo_.mainColor);
	subBossEyeSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossEyeSprite_->SetColor(subBossInfo_.eyeColor);

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);

	// フラグのリセット
	subBossInfo_.isGroundCol = false;
}

void SubBoss::MatUpdate()
{
	subBossSprite_->MatUpdate();
	subBossEyeSprite_->MatUpdate();
	colSprite_->MatUpdate();
}

void SubBoss::Draw()
{
	subBossSprite_->Draw(subBossTextures_[0]);
	subBossEyeSprite_->Draw(subBossEyeTexture_);
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
	imgui->Text("ボスの状態 = %s", subBossMoveTypeStr_[(size_t)currentStateType_].c_str());

	// 座標の表示
	imgui->Text("座標 = { %f, %f }", subBossInfo_.position.x, subBossInfo_.position.y);

	// 当たり判定を表示するか
	imgui->CheckBox("当たり判定表示", isDebug_);

	static std::string curretStr = "StartIntro";
	if (imgui->BeginCombo("攻撃タイプ", curretStr))
	{
		// 攻撃タイプの選択
		for (size_t i = 0; i < subBossMoveTypeStr.size(); i++)
		{
			bool isSelectable = (curretStr == subBossMoveTypeStr[i]);
	
			if (imgui->Selectable(subBossMoveTypeStr[i], isSelectable))
			{
				curretStr = subBossMoveTypeStr[i];
				debugMoveTypeStr_ = curretStr;
			}
	
			if (isSelectable) imgui->SetItemDefaultFocus();
		}
	
		imgui->EndCombo();
	}

	// 攻撃状態に切替
	if (imgui->Button("攻撃状態へ")) DebugStartAttack();
}

void SubBoss::InitializeSubBossInfo(M_ColliderManager* colMgrPtr, Camera* cameraPtr, MinionFactory* minionFactoryPtr, EnemyManager* enemyMgrPtr)
{
	// 座標とサイズと回転度の設定
	subBossInfo_.position = Vector2(960.0f, 400.0f);
	subBossInfo_.size = Vector2(256.0f, 256.0f);
	subBossInfo_.rotation = 0.0f;
	subBossInfo_.mainColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	subBossInfo_.eyeColor = float4(1.0f, 1.0f, 1.0f, 0.0f);

	// コライダーの設定
	subBossInfo_.collider.circle_.center = subBossInfo_.position;
	subBossInfo_.collider.circle_.radius = 82.0f;
	std::string name = "SubBoss";
	auto callBack = std::bind(&SubBoss::CollisionCallBack, this);
	subBossInfo_.collider.Initialize(name, callBack, colMgrPtr);
	subBossInfo_.collider.Data_Add("Damage", 5.0f);

	// カメラの設定
	subBossInfo_.cameraPtr = cameraPtr;

	// 敵管理クラスポインタ受取
	subBossInfo_.enemyMgrPtr = enemyMgrPtr;

	// 生成器のポインタ受取
	subBossInfo_.minionFactoryPtr = minionFactoryPtr;

	// 行動の設定
	currentMoveState_ = std::make_unique<StartIntro>();
	currentMoveState_->Initialize(&subBossInfo_);

	// 状態の変更
	currentMoveType_ = SubBossMoveType::StartIntro;
	currentStateType_ = SubBossStateType::Move;
}

void (SubBoss::*SubBoss::stateTable[]) () = {
	&SubBoss::Wait,
	&SubBoss::Move,
	&SubBoss::Stun,
};

void SubBoss::Wait()
{
}

void SubBoss::Move()
{
	currentMoveState_->Update(&subBossInfo_);
	if (currentMoveState_->GetIsAttackEnd())
	{
		currentStateType_ = SubBossStateType::Wait;
		currentMoveState_->Finalize(&subBossInfo_);
		currentMoveState_ = nullptr;
	}
}

void SubBoss::Stun()
{
}

void SubBoss::ChangeMove()
{
	// 攻撃状態が空ではなかったら終了処理をする
	if (currentMoveState_ != nullptr) currentMoveState_->Finalize(&subBossInfo_);

	if (currentMoveType_ == SubBossMoveType::StartIntro) {
		currentMoveState_ = std::make_unique<StartIntro>();
		currentMoveState_->Initialize(&subBossInfo_);
	}

	else if (currentMoveType_ == SubBossMoveType::EndGameOutro)
	{
		currentMoveState_ = std::make_unique<EndGameOutro>();
		currentMoveState_->Initialize(&subBossInfo_);
	}

	else if (currentMoveType_ == SubBossMoveType::DescentDive)
	{
		currentMoveState_ = std::make_unique<DescentDive>();
		currentMoveState_->Initialize(&subBossInfo_);
	}

	else if (currentMoveType_ == SubBossMoveType::SummonMinions) {
		currentMoveState_ = std::make_unique<SummonMinions>();
		currentMoveState_->Initialize(&subBossInfo_);
	}

	// 状態の変更
	currentStateType_ = SubBossStateType::Move;
}

void SubBoss::MoveChance()
{
	// 状態が待機状態以外なら処理を飛ばす
	if (currentStateType_ != SubBossStateType::Wait) return;

	// ランダムで行動を決める
	size_t rnd = Util::GetRandomInt(2, 3);

	// 雑魚敵がまだいてHPが500以下なら雑魚敵がいる時も突進攻撃をする
	if (subBossInfo_.enemyMgrPtr->GetMinionAmount() > 0 && subBossInfo_.enemyMgrPtr->GetBossHP() <= 500.0f) {
		currentMoveType_ = SubBossMoveType::DescentDive;
		// 行動の生成
		ChangeMove();
	}

	if (subBossInfo_.enemyMgrPtr->GetMinionAmount() <= 0) {
		currentMoveType_ = (SubBossMoveType)rnd;
		// 行動の生成
		ChangeMove();
	}
}

void SubBoss::DebugStartAttack()
{
	if (debugMoveTypeStr_ == "StartIntro") {
		currentMoveType_ = SubBossMoveType::StartIntro;
	}

	else if (debugMoveTypeStr_ == "DescentDive")
	{
		currentMoveType_ = SubBossMoveType::DescentDive;
	}

	else if (debugMoveTypeStr_ == "EndGameOutro") {
		currentMoveType_ = SubBossMoveType::EndGameOutro;
	}

	else if (debugMoveTypeStr_ == "SummonMinions") {
		currentMoveType_ = SubBossMoveType::SummonMinions;
	}

	ChangeMove();
}

void SubBoss::StartDamageProcess()
{
	// 連続でダメージは受けない
	if (isDamage_) return;
	isDamage_ = true;
	subBossInfo_.mainColor = damageColor_;
	subBossInfo_.eyeColor = damageColor_;
	damageTime_.elapsedTime = 0.0f;
}

void SubBoss::DamageProcess()
{
	// ダメージフラグが[OFF]なら処理を飛ばす
	if (isDamage_ == false) return;

	TimeManager* timeMgrPtr = TimeManager::GetInstance();
	
	damageTime_.elapsedTime += timeMgrPtr->GetGameDeltaTime();

	if (damageTime_.GetIsExceeded()) {
		isDamage_ = false;
		subBossInfo_.mainColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
		subBossInfo_.eyeColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void SubBoss::CollisionCallBack()
{
	// プレイヤーの攻撃判定に衝突したら
	if (subBossInfo_.collider.IsDetect_Name("Player_Attack")) {
		StartDamageProcess();
	}

	// 壁と天井の衝突判定
	for (size_t i = 0; i < 4; i++) {
		if (i == 2) continue;
		// 壁か天井と当たったら
		if (subBossInfo_.collider.IsDetect_Name("Boss" + std::to_string(i))) {
			// 押し出し処理
			ICollider* hitCol = subBossInfo_.collider.Extract_Collider("Boss" + std::to_string(i));
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, subBossInfo_.collider.circle_);
			subBossInfo_.position += pushBack;
		}
	}

	// 床と当たったら
	if (subBossInfo_.collider.IsDetect_Name("Boss2"))
	{
		// 押し出し処理
		ICollider* hitCol = subBossInfo_.collider.Extract_Collider("Boss2");
		M_RectCollider* rectCol = static_cast<M_RectCollider*>(hitCol);
		Circle circle = subBossInfo_.collider.circle_;
		Square rect = rectCol->square_;
		// 矩形の最近接点
		float rectY = rect.center.y - rect.length.y / 2.0f;
		float circleY = circle.center.y + circle.radius;
		float pushBack = rectY - circleY;
		subBossInfo_.position.y += pushBack;
	}

	// 壁と衝突しているかを判定
	if (subBossInfo_.collider.IsDetect_Name("Boss2"))
	{
		subBossInfo_.isGroundCol = true;
	}

	// スプライトの更新
	subBossSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);
	subBossEyeSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);
}