#pragma once
#include "Collision/M_RectCollider.h"

class EnemyManager
{
#pragma region メンバ変数
private:
	// 当たり判定
	M_RectCollider stage_ = {};
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	EnemyManager() {}
	~EnemyManager() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();

private:
	void Collision();
#pragma endregion
};