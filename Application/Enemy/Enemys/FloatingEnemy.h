#pragma once
#include "BaseEnemy.h"

class FloatingEnemy : public BaseEnemy
{
#pragma region メンバ変数
private:
	// 敵関連
	Vector2 position_ = Vector2();// 座標
	Vector2 size_ = Vector2(64.0f, 64.0f);// サイズ
#pragma endregion

#pragma region メンバ関数
public:
	// 各基本処理
	void Initialize(const Vector2& inPos, uint16_t tex) override;
	void Update() override;
	void MatUpdate() override;
	void Draw() override;
	void Finalize() override;
	void ImGuiUpdate(ImGuiManager* imGuiMgrPtr) override;
#pragma endregion
};