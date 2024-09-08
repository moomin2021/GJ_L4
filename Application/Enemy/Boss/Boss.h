#pragma once
#include "ImGuiManager.h"
#include "Sprite.h"
#include "Vector2.h"

#include "Collision/M_RectCollider.h"

#include <vector>
#include <memory>

class Boss
{
#pragma region メンバ変数
private:
	// テクスチャ
	uint16_t bossT_ = 0;	// ボス
	uint16_t debugT_ = 0;	// デバック

	// ボス関連
	Vector2 bossPos_ = Vector2();	// 座標
	Vector2 bossSize_ = Vector2();	// サイズ
	std::unique_ptr<Sprite> bossS_ = nullptr;	// スプライト

	// 当たり判定関連
	std::vector<Vector2> bossColCenter_;	// 各コライダーの中心座標
	std::vector<Vector2> bossColLength_;	// 各コライダーの直径
	std::vector<M_RectCollider> bossCol_;	// コライダー
	std::vector<std::unique_ptr<Sprite>> bossColS_;// コライダーのスプライト
	bool isDisplayCol_ = true;	// 当たり判定を表示するか
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	Boss();
	~Boss() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate(ImGuiManager* pImGuiMgr);
#pragma endregion
};

