#include "MinionFollower.h"
#include "M_RectCollider.h"
#include "CollisionChecker.h"
#include "Player.h"
#include "SmokeEffect.h"
#include "Util.h"
#include "Trajectory.h"

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

    // パーティクル出す
    if (moveVec_.x != 0 || moveVec_.y != 0)
    {
        particleFrame_++;
        if (particleFrame_ >= 2)
        {
            Vector2 pos = { stats_.position.x + Util::GetRandomFloat(-18,18), +stats_.position.y + Util::GetRandomFloat(-18,18) };
            particleFrame_ = 0;
            ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos);
            Vector2 pos2 = { stats_.position.x + Util::GetRandomFloat(-18,18), +stats_.position.y + Util::GetRandomFloat(-18,18) };
            ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos2);
            //Vector2 pos3 = { position_.x + Util::GetRandomFloat(-18,18), +position_.y + Util::GetRandomFloat(-18,18) };
            //ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos3);
        }
    }
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

void MinionFollower::UpdateFlockBehavior(std::vector<std::unique_ptr<BaseMinion>>& others, const std::vector<std::unique_ptr<BaseMinion>>& leaders)
{
	Vector2 sep = Separate(others);
	Vector2 ali = Align(others);
	Vector2 coh = Cohesion(others);
	Vector2 followLeader = FollowNearestLeader(leaders);  // 近いリーダーを追従

	// 重み付けして加速度に加える
	stats_.acceleration += sep * 100.0f;
	stats_.acceleration += ali;
	stats_.acceleration += coh;
	stats_.acceleration += followLeader * 1.0f;  // リーダー追従は強め

	// 速度に加速度を加算して位置を更新
	stats_.velocity += stats_.acceleration;
	stats_.velocity = Limit(stats_.velocity, stats_.crowdStats.maxSpeed);
	stats_.position += stats_.velocity * data_->timeMgrPtr->GetGameDeltaTime();

	// 毎フレーム加速度をリセット
	stats_.acceleration = { 0, 0 };
}

void MinionFollower::CollisionCallBack()
{
	// 壁と衝突しているか
	bool isWallCol = false;
	std::string wallName = "";

	// プレイヤーに攻撃されたか
	bool isAttackedByPlayer = false;

	// 壁と天井の衝突判定
	for (size_t i = 0; i < 4; i++) {
		// 壁か天井と当たったら
		if (collider_.IsDetect_Name("Boss" + std::to_string(i))) {
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

			for (size_t i = 0; i < 10; i++)
			{
				ParticleMan::GetInstance()->AddParticle(std::make_unique<SmokeEffect>(), stats_.position, moveVec_);
			}

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

			for (size_t i = 0; i < 10; i++)
			{
				ParticleMan::GetInstance()->AddParticle(std::make_unique<SmokeEffect>(), stats_.position, moveVec_);
			}

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

Vector2 MinionFollower::Separate(const std::vector<std::unique_ptr<BaseMinion>>& others)
{
	Vector2 steer = { 0, 0 };
	int count = 0;
	for (const auto& other : others) {
		float d = stats_.position.Distance(other->GetPosition());
		if (d > 0 && d < stats_.crowdStats.separationDistance) {
			Vector2 diff = stats_.position - other->GetPosition();
			steer += diff.normalize() / d;
			count++;
		}
	}
	if (count > 0) {
		steer = steer * (1.0f / count);
	}
	return Limit(steer, stats_.crowdStats.maxForce);
}

Vector2 MinionFollower::Align(const std::vector<std::unique_ptr<BaseMinion>>& others)
{
	Vector2 sum = { 0, 0 };
	int count = 0;
	for (const auto& other : others) {
		float d = stats_.position.Distance(other->GetPosition());
		if (d > 0 && d < stats_.crowdStats.neighborRadius) {
			sum += other->GetVelocity();
			count++;
		}
	}
	if (count > 0) {
		sum = sum * (1.0f / count);
		return Limit(sum - stats_.velocity, stats_.crowdStats.maxForce);
	}
	return { 0, 0 };
}

Vector2 MinionFollower::Cohesion(const std::vector<std::unique_ptr<BaseMinion>>& others)
{
	Vector2 sum = { 0, 0 };
	int count = 0;
	for (const auto& other : others) {
		float d = stats_.position.Distance(other->GetPosition());
		if (d > 0 && d < stats_.crowdStats.neighborRadius) {
			sum += other->GetPosition();
			count++;
		}
	}
	if (count > 0) {
		sum = sum * (1.0f / count);
		return Seek(sum);
	}
	return { 0, 0 };
}

Vector2 MinionFollower::FollowNearestLeader(const std::vector<std::unique_ptr<BaseMinion>>& leaders)
{
	if (leaders.size() == 0) return Vector2();

	const BaseMinion* nearestLeader = leaders[0].get();
	float minDistance = stats_.position.Distance(leaders[0]->GetPosition());

	// 最も近いリーダーを探す
	for (const auto& leader : leaders) {
		float distance = stats_.position.Distance(leader->GetPosition());
		if (distance < minDistance) {
			nearestLeader = leader.get();
			minDistance = distance;
		}
	}

	return Seek(nearestLeader->GetPosition());  // 近いリーダーに追従
}

Vector2 MinionFollower::Seek(const Vector2& target)
{
	Vector2 desired = target - stats_.position;
	desired = Limit(desired.normalize() * stats_.crowdStats.maxSpeed, stats_.crowdStats.maxSpeed);
	return Limit(desired - stats_.velocity, stats_.crowdStats.maxForce);
}

Vector2 MinionFollower::Limit(const Vector2& vec, float max)
{
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (length > max) {
		return vec * (max / length);
	}
	return vec;
}
