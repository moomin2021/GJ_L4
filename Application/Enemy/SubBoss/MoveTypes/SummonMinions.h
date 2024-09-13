#pragma once
#include "SubBossMoveState.h"

class SummonMinions : public SubBossMoveState
{
#pragma region メンバ変数
private:
	// ステージ0で使う変数
	Util::TimeInfo stage0Time_ = { 2.0f, 0.0f };	// ステージ0の時間
	Vector2 targetPos0_ = Vector2();				// 目標座標
	Vector2 lastTargetPos0_ = Vector2();			// 目標前座標
	// ステージ1で使う変数
	Util::TimeInfo stage1Time_ = { 1.0f, 0.0f };	// ステージ1の時間
	float4 startEyeColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };// 目の色の開始数値
	float4 endEyeColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };	// 目の色の終了数値
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	SummonMinions() {}
	~SummonMinions() {}

	// 基本処理
	void Initialize(SubBossInfo* info) override;
	void Update(SubBossInfo* info) override;
	void Finalize(SubBossInfo* info) override;
#pragma endregion
};