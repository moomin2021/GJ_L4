#pragma once
#include "Sprite.h"
#include "Vector2.h"

#include "Collision/M_RectCollider.h"

#include <memory>

class Boss
{
#pragma region メンバ変数
private:
	// ボスの座標とサイズ
	Vector2 bossPos_ = Vector2();
	Vector2 bossSize_ = Vector2();

	// テクスチャハンドル
	uint16_t bossT_ = 0;

	// スプライト
	std::unique_ptr<Sprite> bossS_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	Boss() {}
	~Boss() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
#pragma endregion
};

