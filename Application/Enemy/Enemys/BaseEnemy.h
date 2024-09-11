#pragma once
#include "M_ColliderManager.h"
#include "ImGuiManager.h"
#include "Sprite.h"

#include <stdint.h>
#include <memory>

class Player;
class BaseEnemy
{
#pragma region メンバ変数
protected:
	// 生存フラグ
	bool isAlive_ = true;

	// スプライト
	std::unique_ptr<Sprite> outlineSprite_ = nullptr;
	std::unique_ptr<Sprite> backSprite_ = nullptr;
	std::unique_ptr<Sprite> frontSprite_ = nullptr;
	uint16_t outlineTexture_ = 0;
	uint16_t backTexture_ = 0;
	uint16_t frontTexture_ = 0;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	BaseEnemy() {}
	virtual ~BaseEnemy() {}

	// 各基本処理
	virtual void Initialize(size_t id, const Vector2& inPos, std::vector<uint16_t> texs, M_ColliderManager* colMgrPtr, Player* playerPtr) = 0;
	virtual void Update() = 0;
	virtual void MatUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
	virtual void ImGuiUpdate(ImGuiManager* imGuiMgrPtr) = 0;
#pragma endregion

#pragma region ゲッター関数
	/// <summary>
	/// 生存フラグの取得
	/// </summary>
	/// <returns> 生存しているか </returns>
	bool GetIsAlive() { return isAlive_; }
#pragma endregion
};