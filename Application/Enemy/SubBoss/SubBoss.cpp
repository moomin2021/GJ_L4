#include "SubBoss.h"
#include "Texture.h"
#include "ImGuiManager.h"

#include "CollisionChecker.h"
#include "Player.h"

#include "MoveTypes/DescentDive.h"

SubBoss::SubBoss() : subBossTextures_(3) {}

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr)
{
	// プレイヤーのポインタ受取
	subBossInfo_.playerPtr = playerPtr;

	// サブボスの情報の初期化処理
	InitializeSubBossInfo(colMgrPtr, cameraPtr);

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
	(this->*stateTable[(size_t)currentStateType_])();

	// スプライトの更新
	subBossSprite_->SetPosition(subBossInfo_.position + subBossInfo_.shakeOffset);
	subBossSprite_->SetSize(subBossInfo_.size);
	subBossSprite_->SetRotation(subBossInfo_.rotation);

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);

	// フラグのリセット
	subBossInfo_.isGroundCol = false;
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

	// 座標の表示
	imgui->Text("座標 = { %f, %f }", subBossInfo_.position.x, subBossInfo_.position.y);

	// 当たり判定を表示するか
	imgui->CheckBox("当たり判定表示", isDebug_);

	static std::string curretStr = "DescentDive";
	if (imgui->BeginCombo("攻撃タイプ", curretStr))
	{
		// 攻撃タイプの選択
		for (size_t i = 0; i < subBossMoveTypeStr.size(); i++)
		{
			bool isSelectable = (curretStr == subBossMoveTypeStr[i]);
	
			if (imgui->Selectable(subBossMoveTypeStr[i], isSelectable))
			{
				curretStr = subBossMoveTypeStr[i];
				debugAttackTypeStr_ = curretStr;
			}
	
			if (isSelectable) imgui->SetItemDefaultFocus();
		}
	
		imgui->EndCombo();
	}

	// 攻撃状態に切替
	if (imgui->Button("攻撃状態へ")) DebugStartAttack();
}

void SubBoss::InitializeSubBossInfo(M_ColliderManager* colMgrPtr, Camera* cameraPtr)
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
	subBossInfo_.collider.Data_Add("Damage", 5.0f);

	// カメラの設定
	subBossInfo_.cameraPtr = cameraPtr;
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

void SubBoss::ChangeAttack()
{
	// 攻撃状態が空ではなかったら終了処理をする
	if (currentMoveState_ != nullptr) currentMoveState_->Finalize(&subBossInfo_);

	// 攻撃状態の生成、初期化
	currentMoveState_ = std::make_unique<DescentDive>();
	currentMoveState_->Initialize(&subBossInfo_);

	// 状態の変更
	currentStateType_ = SubBossStateType::Move;
}

void SubBoss::DebugStartAttack()
{
	// 攻撃状態が空ではなかったら終了処理をする
	if (currentMoveState_ != nullptr) currentMoveState_->Finalize(&subBossInfo_);

	if (debugAttackTypeStr_ == "DescentDive")
	{
		currentMoveState_ = std::make_unique<DescentDive>();
		currentMoveState_->Initialize(&subBossInfo_);
	}

	// 状態の変更
	currentStateType_ = SubBossStateType::Move;
}

void SubBoss::CollisionCallBack()
{
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

	// コライダーの更新
	subBossInfo_.collider.circle_.center = subBossSprite_->GetPosition();
	colSprite_->SetPosition(subBossInfo_.collider.circle_.center);
}