#pragma once
#include "ImGuiManager.h"
#include "Collision/M_ColliderManager.h"

#include "Boss/Boss.h"
#include "SubBoss/SubBoss.h"
#include "Enemys/BaseEnemy.h"
#include "EnemyFactory.h"

class Player;
class EnemyManager
{
#pragma region メンバ変数
private:
	// インスタンス
	ImGuiManager* pImGuiMgr_ = nullptr;
	Camera* pCamera_ = nullptr;

	// 敵生成器
	std::unique_ptr<EnemyFactory> enemyFactory_ = nullptr;

	// ボス
	std::unique_ptr<Boss> boss_ = nullptr;

	// サブボス
	std::unique_ptr<SubBoss> subBoss_ = nullptr;

	// 敵
	std::vector<std::unique_ptr<BaseEnemy>> enemys_;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	EnemyManager() {}
	~EnemyManager() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();

	// 敵の追加
	void AddEnemy(std::unique_ptr<BaseEnemy> newEnemy) { enemys_.emplace_back(std::move(newEnemy)); }
#pragma endregion
};