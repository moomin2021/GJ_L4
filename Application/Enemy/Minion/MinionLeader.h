#pragma once
#include "BaseMinion.h"

class MinionLeader : public BaseMinion
{
#pragma region メンバ変数
private:
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	MinionLeader() {}
	~MinionLeader() {}

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
