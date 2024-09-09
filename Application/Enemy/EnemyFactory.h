#pragma once
#include "M_ColliderManager.h"
#include "ImGuiManager.h"
#include "Enemys/BaseEnemy.h"

#include <memory>

class EnemyManager;
class Player;
class EnemyFactory
{
#pragma region メンバ変数
private:
	// 敵管理クラスポインタ
	EnemyManager* pEnemyMgr_ = nullptr;
	M_ColliderManager* pColMgr_ = nullptr;
	Player* pPlayer_ = nullptr;

	// 敵のテクスチャ
	std::vector<uint16_t> textures_;

	// デバックで敵を生成する座標
	Vector2 debugCreatePos_ = Vector2();

	// 生成数カウント
	size_t createCounter_ = 0;
#pragma endregion

#pragma region メンバ関数
public:
	// 各基本処理
	void Initialize(EnemyManager* enemyMgrPtr, M_ColliderManager* colMgrPtr, Player* playerPtr);
	void ImGuiUpdate(ImGuiManager* imGuiMgrPtr);

	// 敵の生成
	void CreateEnemy(const Vector2& inPos);
#pragma endregion
};