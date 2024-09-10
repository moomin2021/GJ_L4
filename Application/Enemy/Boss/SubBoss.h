#pragma once
#include "Sprite.h"
#include "M_ColliderManager.h"

#include "SubBossInfo.h"

#include <vector>
#include <memory>

class Player;
class SubBoss
{
#pragma region メンバ変数
private:
	// プレイヤーのポインタ
	Player* pPlayer_ = nullptr;

	// サブボスの情報
	SubBossInfo subBossInfo_ = {};

	// サブボスの描画関連
	std::unique_ptr<Sprite> subBossSprite_ = nullptr;
	std::vector<uint16_t> subBossTextures_;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	SubBoss();
	~SubBoss() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();

private:
	// サブボスの情報の初期化処理
	void InitializeSubBossInfo();
#pragma endregion
};