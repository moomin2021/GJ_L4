#pragma once
#include "BaseMinion.h"

class MinionFollower : public BaseMinion
{
#pragma region メンバ変数
private:
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	MinionFollower() {}
	~MinionFollower() {}

	// 各初期化処理
	void Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData) override;
	void Update() override;
	void MatUpdate() override;
	void ImGuiUpdate(ImGuiManager* imgui) override;
	void Draw() override;
	void Finalize() override;

private:
	// 衝突判定コールバック関数
	void CollisionCallBack() override;
#pragma endregion
};
