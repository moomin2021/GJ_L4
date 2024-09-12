#include "MinionFollower.h"
#include "M_RectCollider.h"
#include "CollisionChecker.h"
#include "Player.h"

using namespace EnemyStatus;

void MinionFollower::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);

	// コライダーの設定
	collider_.circle_.center = stats_.position;
	collider_.circle_.radius = 32.0f;
	std::string name = "Minion";
	auto callback = std::bind(&MinionFollower::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
}

void MinionFollower::Update()
{
	// 状態別更新処理
	(this->*stateTable[(size_t)stats_.state])();

	// 座標の更新
	for (auto& it : sprites_) it->SetPosition(stats_.position);

	// 回転の更新
	sprites_[0]->SetRotation(backRotation_);
	sprites_[1]->SetRotation(backRotation_);
	sprites_[2]->SetRotation(frontRotation_);
}

void MinionFollower::MatUpdate()
{
	BaseMinion::MatUpdate();
}

void MinionFollower::ImGuiUpdate(ImGuiManager* imgui)
{
	imgui = imgui;
}

void MinionFollower::Draw()
{
	BaseMinion::Draw();
}

void MinionFollower::Finalize()
{
	BaseMinion::Finalize();
}

void MinionFollower::CollisionCallBack()
{
	// 壁と衝突しているか
	bool isWallCol = false;
	std::string wallName = "";

	// プレイヤーに攻撃されたか
	bool isAttackedByPlayer = false;

	// ボスと衝突しているか
	for (size_t i = 0; i < 4; i++)
	{
		if (collider_.IsDetect_Name("Boss" + std::to_string(i)))
		{
			isWallCol = true;
			wallName = "Boss" + std::to_string(i);
		}
	}

	// プレイヤーの攻撃判定と衝突してるか
	if (collider_.IsDetect_Name("Player_Attack")) {
		isAttackedByPlayer = true;
	}

	// 壁と衝突していたら
	if (isWallCol)
	{
		// 一回目殴られた状態なら
		if (stats_.state == MinionState::FirstBeaten)
		{
			// 押し出し処理
			ICollider* hitCol = collider_.Extract_Collider(wallName);
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, collider_.circle_);
			stats_.position += pushBack;

			// 状態、移動方向、速度の設定
			stats_.state = MinionState::KnockBack;
			moveVec_ = knockVec_;
			moveSpd_ = knockFirstSpd_;
			backRotaSpd_ = knockFirstRotaSpd_;
			// ダメージの設定
			collider_.Data_Remove("Damage");
			collider_.Data_Add("Damage", 0.0f);
		}

		// 二回目殴られた状態なら
		else if (stats_.state == MinionState::SecondBeaten)
		{
			// 押し出し処理
			ICollider* hitCol = collider_.Extract_Collider(wallName);
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, collider_.circle_);
			stats_.position += pushBack;

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
		if (stats_.state == MinionState::Normal) {
			// 状態、移動方向、速度の設定
			stats_.state = MinionState::FirstBeaten;
			moveVec_ = firstBeatenVec_;
			moveSpd_ = firstBeatenMoveSpd_;
			backRotaSpd_ = firstBeatenRotaSpd_;
			// ダメージの設定
			collider_.Data_Add("Damage", 20.0f);
		}

		// ノックバック状態なら
		else if (stats_.state == MinionState::KnockBack) {
			// 状態、移動方向、速度の設定
			stats_.state = MinionState::SecondBeaten;
			moveSpd_ = secondBeatenMoveSpd_;
			backRotaSpd_ = secondBeatenRotaSpd_;
			// 移動方向の決定
			PlayerCommonInfomation* playerInfo = data_->playerPtr->Get_CommonInfomation();
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

void MinionFollower::MoveUpdate()
{
	// 加速度を速度に加算
	stats_.velocity += stats_.acceleration * data_->timeMgrPtr->GetGameDeltaTime();

	// 速度を座標に反映
	stats_.position += stats_.velocity * data_->timeMgrPtr->GetGameDeltaTime();

	// 指数減衰を適用して減速させる
	stats_.velocity.x *= exp(-stats_.dampingFactor * data_->timeMgrPtr->GetGameDeltaTime());
	stats_.velocity.y *= exp(-stats_.dampingFactor * data_->timeMgrPtr->GetGameDeltaTime());
}

void (MinionFollower::* MinionFollower::stateTable[]) () = {
	&MinionFollower::Normal,
	&MinionFollower::FirstBeaten,
	&MinionFollower::KnockBack,
	&MinionFollower::SecondBeaten,
};

void MinionFollower::Normal()
{
	// 移動更新
	MoveUpdate();
}

void MinionFollower::FirstBeaten()
{
	// 座標の更新
	stats_.position += moveVec_ * moveSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotation_ += backRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	collider_.circle_.center = stats_.position;
}

void MinionFollower::KnockBack()
{
	moveSpd_ -= knockAddSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotaSpd_ -= knockAddRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();

	// 座標の更新
	stats_.position += moveVec_ * moveSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotation_ += backRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	collider_.circle_.center = stats_.position;
}

void MinionFollower::SecondBeaten()
{
	nowTime_ += data_->timeMgrPtr->GetGameDeltaTime();

	if (nowTime_ >= aliveTime_) {
		stats_.isAlive = false;
	}

	// 座標の更新
	stats_.position += moveVec_ * moveSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotation_ += backRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	collider_.circle_.center = stats_.position;
}