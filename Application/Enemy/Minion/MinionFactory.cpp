#include "MinionFactory.h"
#include "Texture.h"

#include "EnemyManager.h"
#include "Minion/MinionLeader.h"
#include "Minion/MinionFollower.h"

void MinionFactory::Initialize(EnemyManager* enemyMgrPtr, M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// ポインタ受取り
	pEnemyMgr_ = enemyMgrPtr;
	pColMgr_ = colMgrPtr;

	// データの設定
	leaderData_.playerPtr = playerPtr;
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyOutLine01.png"));
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyBlade01.png"));
	leaderData_.textures.emplace_back(LoadTexture("zakoEnemyFace01.png"));
	followerData_.playerPtr = playerPtr;
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyOutLine01.png"));
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyBlade01.png"));
	followerData_.textures.emplace_back(LoadTexture("zakoEnemyFace01.png"));
}

void MinionFactory::ImGuiUpdate(ImGuiManager* imgui)
{
	imgui = imgui;
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
	}

	// フォロワー
	else if (type == EnemyStatus::MinionType::Follower) {
		newMinion = std::make_unique<MinionFollower>();
		newMinion->Initialize(pColMgr_, setStats_, &followerData_);
	}
}