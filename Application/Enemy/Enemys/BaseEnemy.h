#pragma once
#include "ImGuiManager.h"
#include "Sprite.h"

#include <stdint.h>
#include <memory>

class BaseEnemy
{
#pragma region メンバ変数
protected:
	// 生存フラグ
	bool isAlive_ = true;

	// スプライト
	std::unique_ptr<Sprite> sprite_ = nullptr;
	uint16_t texture_ = 0;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	BaseEnemy() {}
	virtual ~BaseEnemy() {}

	// 各基本処理
	virtual void Initialize(const Vector2& inPos, uint16_t tex) = 0;
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