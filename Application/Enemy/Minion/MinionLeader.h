#pragma once
#include "BaseMinion.h"

class MinionLeader : public BaseMinion
{
#pragma region メンバ変数
private:
#pragma endregion

#pragma region メンバ関数
public:
	// 各初期化処理
	void Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, const std::vector<uint16_t>& inTextures) override;
	void Update() override;
	void MatUpadte() override;
	void ImGuiUpdate() override;
	void Draw() override;
	void Finalize() override;
#pragma endregion
};
