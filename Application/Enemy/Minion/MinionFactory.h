#pragma once
#include "M_ColliderManager.h"

#include "BaseMinion.h"
#include "EnemyStatus.h"

class Player;
class EnemyManager;
class MinionFactory
{
#pragma region メンバ変数
private:
	// ポインタ
	EnemyManager* pEnemyMgr_ = nullptr;
	M_ColliderManager* pColMgr_ = nullptr;

	// テクスチャ
	std::vector<uint16_t> leaderTextures_ = {};
	std::vector<uint16_t> followerTextures_ = {};

	// データ
	EnemyStatus::MinionData leaderData_ = {};
	EnemyStatus::MinionData followerData_ = {};

	// 設定パラメーター
	EnemyStatus::MinionStats setStats_ = {};
#pragma endregion

#pragma region メンバ関数
public:
	// 初期化処理
	void Initialize(EnemyManager* enemyMgrPtr, M_ColliderManager* colMgrPtr, Player* playerPtr);

	// ImGuiの更新処理
	void ImGuiUpdate(ImGuiManager* imgui);

	// 雑魚敵の生成
	void CreateMinion(const Vector2& inPos, EnemyStatus::MinionType type);
#pragma endregion
};