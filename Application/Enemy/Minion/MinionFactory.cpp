#include "MinionFactory.h"
#include "Texture.h"

#include "EnemyManager.h"
#include "Minion/MinionLeader.h"
#include "Minion/MinionFollower.h"

using namespace EnemyStatus;

void MinionFactory::Initialize(EnemyManager* enemyMgrPtr, M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// ポインタ受取り
	pEnemyMgr_ = enemyMgrPtr;
	pColMgr_ = colMgrPtr;

	// パラメーター設定
	setStats_.crowdStats.maxSpeed = 200.0f;
	setStats_.crowdStats.maxForce = 0.1f;
	setStats_.crowdStats.separationDistance = 50.0f;
	setStats_.crowdStats.neighborRadius = 200.0f;

	// データの設定
	leaderData_.playerPtr = playerPtr;
	leaderData_.timeMgrPtr = TimeManager::GetInstance();
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyOutLine01.png"));
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyBlade01.png"));
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyFace01.png"));
	followerData_.playerPtr = playerPtr;
	followerData_.timeMgrPtr = TimeManager::GetInstance();
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyOutLine01.png"));
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyBlade01.png"));
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyFace01.png"));
}

void MinionFactory::ImGuiUpdate(ImGuiManager* imgui)
{
	// 敵の生成場所の入力
	imgui->InputVector2("生成座標", debugCreatePos_);

	static std::string curretStr = "Leader";
	if (imgui->BeginCombo("ファイル", curretStr))
	{
		// 攻撃タイプの選択
		for (size_t i = 0; i < minionTypeStr_.size(); i++)
		{
			bool isSelectable = (curretStr == minionTypeStr_[i]);

			if (imgui->Selectable(minionTypeStr_[i], isSelectable))
			{
				curretStr = minionTypeStr_[i];
				if (curretStr == "Leader") debugType_ = MinionType::Leader;
				if (curretStr == "Follower") debugType_ = MinionType::Follower;
			}

			if (isSelectable) imgui->SetItemDefaultFocus();
		}

		imgui->EndCombo();
	}

	// 敵を生成するボタン
	if (imgui->Button("生成する")) {
		CreateMinion(debugCreatePos_, debugType_);
	}
}

void MinionFactory::CreateMinion(const Vector2& inPos, EnemyStatus::MinionType type)
{
	// 雑魚敵新規作成
	std::unique_ptr<BaseMinion> newMinion;

	// パラメーターの設定
	setStats_.position = inPos;

	// リーダー
	if (type == EnemyStatus::MinionType::Leader) {
		newMinion = std::make_unique<MinionLeader>();
		newMinion->Initialize(pColMgr_, setStats_, &leaderData_);
		pEnemyMgr_->AddLeader(std::move(newMinion));
	}

	// フォロワー
	else if (type == EnemyStatus::MinionType::Follower) {
		newMinion = std::make_unique<MinionFollower>();
		newMinion->Initialize(pColMgr_, setStats_, &followerData_);
		pEnemyMgr_->AddFollower(std::move(newMinion));
	}
}