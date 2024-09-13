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
	// ステージ2で使う変数
	Util::TimeInfo stage2Time_ = { 0.2f, 0.0f };
	uint16_t stage2MaxCount_ = 10;
	uint16_t stage2Counter_ = 0;

	// サウンド
	uint16_t leaderSpawnSound_ = 0;
	uint16_t followerSpawnSound_ = 0;
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