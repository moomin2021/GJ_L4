#pragma once
#include "Boss/Boss.h"

class EnemyManager
{
#pragma region メンバ変数
private:
	std::unique_ptr<Boss> boss_ = nullptr;
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
#pragma endregion
};