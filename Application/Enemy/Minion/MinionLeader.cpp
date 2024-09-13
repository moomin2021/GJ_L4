#include "MinionLeader.h"
#include "M_RectCollider.h"
#include "CollisionChecker.h"
#include "Player.h"
#include "Key.h"
#include "Easing.h"
#include "SmokeEffect.h"
#include "Util.h"
#include "Trajectory.h"

using namespace EnemyStatus;

void MinionLeader::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);

	// コライダーの設定
	collider_.circle_.center = stats_.position;
	collider_.circle_.radius = 32.0f;
	std::string name = "Minion";
	auto callback = std::bind(&MinionLeader::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
	collider_.Data_Add("Damage", 20.0f);

	// ターゲット
	lastTargetPos_ = stats_.position;
	targetPos_.x = stats_.position.x;
}

void MinionLeader::Update()
{
	//stats_.position.x += (Key::GetInstance()->PushKey(DIK_D) - Key::GetInstance()->PushKey(DIK_A)) * 100.0f * data_->timeMgrPtr->GetGameDeltaTime();
	//stats_.position.y += (Key::GetInstance()->PushKey(DIK_S) - Key::GetInstance()->PushKey(DIK_W)) * 100.0f * data_->timeMgrPtr->GetGameDeltaTime();

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
            Vector2 pos = { stats_.position.x + Util::GetRandomFloat(-18,18), + stats_.position.y + Util::GetRandomFloat(-18,18) };
            particleFrame_ = 0;
            ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos);
            Vector2 pos2 = { stats_.position.x + Util::GetRandomFloat(-18,18), + stats_.position.y + Util::GetRandomFloat(-18,18) };
            ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos2);
            //Vector2 pos3 = { position_.x + Util::GetRandomFloat(-18,18), +position_.y + Util::GetRandomFloat(-18,18) };
            //ParticleMan::GetInstance()->AddParticle(std::make_unique<TrajectoryParticle>(), pos3);
        }
    }
}

void MinionLeader::MatUpdate()
{
	BaseMinion::MatUpdate();
}

void MinionLeader::ImGuiUpdate(ImGuiManager* imgui)
{
	imgui = imgui;
}

void MinionLeader::Draw()
{
	BaseMinion::Draw();
}

void MinionLeader::Finalize()
{
	BaseMinion::Finalize();
}

void MinionLeader::UpdateFlockBehavior(std::vector<std::unique_ptr<BaseMinion>>& others, const std::vector<std::unique_ptr<BaseMinion>>& leaders)
{
	others;
	leaders;
}

void MinionLeader::CollisionCallBack()
{
	// 壁と衝突しているか
	bool isWallCol = false;
	std::string wallName = "";

	// プレイヤーに攻撃されたか
	bool isAttackedByPlayer = false;

	// 壁と天井の衝突判定
	for (size_t i = 0; i < 4; i++) {
		if (stats_.state == MinionState::KnockBack) break;
		// 壁か天井と当たったら
		if (collider_.IsDetect_Name("Boss" + std::to_string(i))) {
			// 押し出し処理
			ICollider* hitCol = collider_.Extract_Collider("Boss" + std::to_string(i));
			M_RectCollider* rect = static_cast<M_RectCollider*>(hitCol);
			Vector2 pushBack = CollisionResponse::PushBack_AABB2Circle(rect->square_, collider_.circle_);
			stats_.position += pushBack;
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
				ParticleMan::GetInstance()->AddParticle(std::make_unique<SmokeEffect>(), stats_.position,moveVec_);
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
		if (stats_.state == MinionState::Normal || stats_.state == MinionState::MoveX) {
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

	// スプライトの更新
	for (auto& it : sprites_) {
		it->SetPosition(stats_.position);
	}

	if (stats_.position.y >= 2100.0f) stats_.isAlive = false;

	// コライダーの更新
	collider_.circle_.center = sprites_[0]->GetPosition();
}

void MinionLeader::MoveUpdate()
{
	// 加速度を速度に加算
	stats_.velocity += stats_.acceleration * data_->timeMgrPtr->GetGameDeltaTime();

	// 速度を座標に反映
	stats_.position += stats_.velocity * data_->timeMgrPtr->GetGameDeltaTime();

	// 指数減衰を適用して減速させる
	stats_.velocity.x *= exp(-stats_.dampingFactor * data_->timeMgrPtr->GetGameDeltaTime());
	stats_.velocity.y *= exp(-stats_.dampingFactor * data_->timeMgrPtr->GetGameDeltaTime());

	stats_.acceleration *= exp(-0.98f * data_->timeMgrPtr->GetGameDeltaTime());
}

void (MinionLeader::* MinionLeader::stateTable[]) () = {
	&MinionLeader::Normal,
	& MinionLeader::FirstBeaten,
	& MinionLeader::KnockBack,
	& MinionLeader::SecondBeaten,
	& MinionLeader::MoveX,
	& MinionLeader::Spawn,
};

void MinionLeader::Normal()
{
	// 移動更新
	//MoveUpdate();
}

void MinionLeader::FirstBeaten()
{
	// 座標の更新
	stats_.position += moveVec_ * moveSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotation_ += backRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	collider_.circle_.center = stats_.position;
}

void MinionLeader::KnockBack()
{
	moveSpd_ -= knockAddSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotaSpd_ -= knockAddRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();

	// 座標の更新
	stats_.position += moveVec_ * moveSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	backRotation_ += backRotaSpd_ * data_->timeMgrPtr->GetGameDeltaTime();
	collider_.circle_.center = stats_.position;
}

void MinionLeader::SecondBeaten()
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

void MinionLeader::MoveX()
{
	stateMoveXTime_ += data_->timeMgrPtr->GetGameDeltaTime();

	// 加速度を速度に加算
	stats_.velocity += stateMoveXAcc_ * data_->timeMgrPtr->GetGameDeltaTime();
	stats_.velocity.x = Util::Clamp(stats_.velocity.x, 120.0f, -120.0f);

	// 速度を座標に反映
	stats_.position.x += stats_.velocity.x * data_->timeMgrPtr->GetGameDeltaTime();
	stats_.position.y = baseY_ + amolitude_ * std::sin(stateMoveXSpd_ * stateMoveXTime_);

	if (stateMoveXAcc_.x < 0 && stats_.position.x <= 400.0f) stateMoveXAcc_ = -stateMoveXAcc_;
	if (stateMoveXAcc_.x > 0 && stats_.position.x >= 1520.0f) stateMoveXAcc_ = -stateMoveXAcc_;
}

void MinionLeader::Spawn()
{
	spawnTime_.elapsedTime += data_->timeMgrPtr->GetGameDeltaTime();

	float rate = spawnTime_.GetElapsedRatio();
	stats_.position.x = Easing::Quint::easeOut(lastTargetPos_.x, targetPos_.x, rate);
	stats_.position.y = Easing::Quint::easeOut(lastTargetPos_.y, targetPos_.y, rate);

	if (spawnTime_.GetIsExceeded()) {
		stats_.state = MinionState::MoveX;
		if (stats_.position.x >= 960.0f) stateMoveXAcc_.x = -100.0f;
		else stateMoveXAcc_.x = 100.0f;
	}
}