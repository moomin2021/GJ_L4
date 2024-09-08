#pragma once
#include "ImGuiManager.h"
#include "Boss/Boss.h"
#include "Collision/M_ColliderManager.h"

class EnemyManager
{
#pragma region メンバ変数
private:
	// インスタンス
	ImGuiManager* pImGuiMgr_ = nullptr;

	// ボス
	std::unique_ptr<Boss> boss_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	EnemyManager() {}
	~EnemyManager() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();
#pragma endregion
};