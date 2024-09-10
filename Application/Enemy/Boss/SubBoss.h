#pragma once
#include "M_ColliderManager.h"
#include "Sprite.h"

#include <memory>

class Player;
class SubBoss
{
#pragma region メンバ変数
private:
	// プレイヤーのポインタ
	Player* pPlayer_ = nullptr;

	// サブボスのデータ
	Vector2 subBossPos_ = Vector2(960.0f, 400.0f);
	Vector2 subBossSize_ = Vector2(256.0f, 256.0f);

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
#pragma endregion
};