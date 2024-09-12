#include "FloatingEnemy.h"
#include "Key.h"
#include "Util.h"
#include "M_RectCollider.h"
#include "CollisionChecker.h"
#include "Player.h"

using namespace EnemyStatus;

void FloatingEnemy::Initialize(size_t id, const Vector2& inPos, std::vector<uint16_t> texs, M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// 座標の設定
	position_ = inPos;
	// テクスチャの設定
	outlineTexture_ = texs[0];
	backTexture_ = texs[1];
	frontTexture_ = texs[2];

	// IDの設定
	id_ = id;

	// インスタンス取得
	pTimeMgr_ = TimeManager::GetInstance();
	pPlayer_ = playerPtr;

	// スプライトの生成、設定
	outlineSprite_ = std::make_unique<Sprite>();
	outlineSprite_->SetPosition(position_);
	outlineSprite_->SetSize(size_);
	outlineSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	outlineSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	backSprite_ = std::make_unique<Sprite>();
	backSprite_->SetPosition(position_);
	backSprite_->SetSize(size_);
	backSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	backSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	frontSprite_ = std::make_unique<Sprite>();
	frontSprite_->SetPosition(position_);
	frontSprite_->SetSize(size_);
	frontSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	frontSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });

	// コライダーの設定
	collider_.circle_.center = position_;
	collider_.circle_.radius = 32.0f;
	std::string name = "FloatingEnemy";
	auto callback = std::bind(&FloatingEnemy::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
}

void FloatingEnemy::Update()
{
	if (color_ < 1.0f) {
		color_ += addColor_ * pTimeMgr_->GetGameDeltaTime();
		color_ = Util::Clamp(color_, 1.0f, 0.0f);
		outlineSprite_->SetColor({ color_, color_ , color_ , color_ });
		backSprite_->SetColor({ color_, color_ , color_ , color_ });
		frontSprite_->SetColor({ color_, color_ , color_ , color_ });
	}

	// 状態別更新処理
	(this->*stateTable[(size_t)state_])();

	// 座標の更新
	position_ += moveVec_ * moveSpd_ * pTimeMgr_->GetGameDeltaTime();
	rotation_ += rotaSpd_ * pTimeMgr_->GetGameDeltaTime();
	if (state_ != State::Normal) frontRotation_ = rotation_;
	collider_.circle_.center = position_;

	// スプライトの更新
	outlineSprite_->SetPosition(position_);
	outlineSprite_->SetRotation(rotation_);
	backSprite_->SetPosition(position_);
	backSprite_->SetRotation(rotation_);
	frontSprite_->SetPosition(position_);
	frontSprite_->SetRotation(frontRotation_);
}

void FloatingEnemy::MatUpdate()
{
	outlineSprite_->MatUpdate();
	backSprite_->MatUpdate();
	frontSprite_->MatUpdate();
}

void FloatingEnemy::Draw()
{
	outlineSprite_->Draw(outlineTexture_);
	backSprite_->Draw(backTexture_);
	frontSprite_->Draw(frontTexture_);
}

void FloatingEnemy::Finalize()
{
	collider_.Finalize();
}

void FloatingEnemy::ImGuiUpdate(ImGuiManager* imGuiMgrPtr)
{
	// 座標の表示
	imGuiMgrPtr->Text("ID = %d, 座標 = { %f, %f }", id_, position_.x, position_.y);
}

void FloatingEnemy::CollisionCallBack()
{
	// 壁と衝突しているか
	bool isWallCol = false;
	std::string wallName = "";

	// プレイヤーに攻撃されたか
	bool isAttackedByPlayer = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (collider_.IsDetect_Name("Boss" + std::to_string(i)))
		{
			isWallCol = true;
			wallName = "Boss" + std::to_string(i);
		}

		if (collider_.IsDetect_Name("Player_Attack")) {
			isAttackedByPlayer = true;
		}
	}

	// 壁と衝突していたら
	if (isWallCol)
	{
		// 一回目殴られた状態なら
		if (state_ == State::FirstBeaten)
		{
			// 押し出し処理
			ICollider* hitCol = collider_.Extract_Collider(wallName);
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, collider_.circle_);
			position_ += pushBack;

			// 状態、移動方向、速度の設定
			state_ = State::KnockBack;
			moveVec_ = knockVec_;
			moveSpd_ = knockFirstSpd_;
			rotaSpd_ = knockFirstRotaSpd_;
			// ダメージの設定
			collider_.Data_Remove("Damage");
			collider_.Data_Add("Damage", 0.0f);
		}

		// 二回目殴られた状態なら
		else if (state_ == State::SecondBeaten)
		{
			// 押し出し処理
			ICollider* hitCol = collider_.Extract_Collider(wallName);
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, collider_.circle_);
			position_ += pushBack;

			// 移動方向の反転
			if (wallName == "Boss0") moveVec_.y = -moveVec_.y;
			if (wallName == "Boss1") moveVec_.x = -moveVec_.x;
			if (wallName == "Boss2") moveVec_.y = -moveVec_.y;
			if (wallName == "Boss3") moveVec_.x = -moveVec_.x;
		}
	}

	// プレイヤーに攻撃されていたら
	if (isAttackedByPlayer) {
		// ノーマル状態なら
		if (state_ == State::Normal) {
			// 状態、移動方向、速度の設定
			state_ = State::FirstBeaten;
			moveVec_ = firstBeatenVec_;
			moveSpd_ = firstBeatenMoveSpd_;
			rotaSpd_ = firstBeatenRotaSpd_;
			// ダメージの設定
			collider_.Data_Add("Damage", 20.0f);
		}

		// ノックバック状態なら
		else if (state_ == State::KnockBack) {
			// 状態、移動方向、速度の設定
			state_ = State::SecondBeaten;
			moveSpd_ = secondBeatenMoveSpd_;
			rotaSpd_ = secondBeatenRotaSpd_;
			// 移動方向の決定
			PlayerCommonInfomation* playerInfo = pPlayer_->Get_CommonInfomation();
			if (playerInfo->move.velocity_current.y > 0.0f) secondBeatenVec_.y = 0.6f;
			if (playerInfo->move.velocity_current.y <= 0.0f) secondBeatenVec_.y = -0.6f;
			if (Direction::DIRECITON_LEFT == playerInfo->move.direction_current) secondBeatenVec_.x = -1.0f;
			if (Direction::DIRECTION_RIGHT == playerInfo->move.direction_current) secondBeatenVec_.x = 1.0f;
			secondBeatenVec_.normalize();
			moveVec_ = secondBeatenVec_;
			// ダメージの設定
			collider_.Data_Remove("Damage");
			collider_.Data_Add("Damage", 20.0f);
		}
	}
}

void (FloatingEnemy::* FloatingEnemy::stateTable[]) () = {
	&FloatingEnemy::Normal,
	&FloatingEnemy::FirstBeaten,
	&FloatingEnemy::KnockBack,
	&FloatingEnemy::SecondBeaten,
};

void FloatingEnemy::Normal()
{
	rotaSpd_ = normalRotaSpd_;
}

void FloatingEnemy::FirstBeaten()
{

}

void FloatingEnemy::KnockBack()
{
	moveSpd_ -= knockAddSpd_ * pTimeMgr_->GetGameDeltaTime();
	rotaSpd_ -= knockAddRotaSpd_ * pTimeMgr_->GetGameDeltaTime();
}

void FloatingEnemy::SecondBeaten()
{
	nowTime_ += pTimeMgr_->GetGameDeltaTime();

	if (nowTime_ >= aliveTime_) {
		isAlive_ = false;
	}
}