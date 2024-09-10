#pragma once
#include "M_ColliderManager.h"

class Player;
class SubBoss
{
#pragma region メンバ変数
private:
	// プレイヤーのポインタ
	Player* pPlayer_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();
#pragma endregion
};