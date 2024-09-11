#pragma once
#include "Vector2.h"

class Shake
{
#pragma region メンバ変数
private:
	Vector2 intensity_ = Vector2();	// シェイク強度
	float shakeDuration_ = 0.0f;	// シェイク持続時間
	float elapsedTime_ = 0.0f;		// 経過時間
	Vector2 offset_ = Vector2();	// シェイクによる座標のずれ
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	Shake() {}
	~Shake() {}

	// シェイクの設定
	void SetShake(const Vector2& intensity, float duration);

	// 更新処理
	void Update(float deltaTime);
#pragma endregion

#pragma region ゲッター関数
public:
	/// <summary>
	/// シェイクのオフセットの取得
	/// </summary>
	/// <returns> シェイクのオフセット </returns>
	const Vector2& GetOffset() { return offset_; }
#pragma endregion
};