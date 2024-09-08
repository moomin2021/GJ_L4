#pragma once
#include "ImGuiManager.h"
#include "Enemys/BaseEnemy.h"

#include <memory>

class EnemyManager;
class EnemyFactory
{
#pragma region メンバ変数
private:
	// 敵管理クラスポインタ
	EnemyManager* pEnemyMgr_ = nullptr;

	// 敵のテクスチャ
	std::vector<uint16_t> textures_;

	// デバックで敵を生成する座標
	Vector2 debugCreatePos_ = Vector2();
#pragma endregion

#pragma region メンバ関数
public:
	// 各基本処理
	void Initialize(EnemyManager* enemyMgrPtr);
	void ImGuiUpdate(ImGuiManager* imGuiMgrPtr);

	// 敵の生成
	void CreateEnemy(const Vector2& inPos);
#pragma endregion
};