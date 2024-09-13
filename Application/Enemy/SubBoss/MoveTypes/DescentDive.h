#pragma once
#include "SubBossMoveState.h"

class DescentDive : public SubBossMoveState {
#pragma region メンバ変数
private:
	// ステージ0で使う変数
	Util::TimeInfo stage0Time_ = { 1.0f, 0.0f };	// ステージ0の時間
	Vector2 targetPos_ = Vector2();					// 目標の座標
	Vector2 presetTargetPos_ = Vector2();			// 目標前の座標
	// ステージ1で使う変数
	Util::TimeInfo stage1Time_ = { 2.0f, 0.0f };	// ステージ1の時間
	Util::MovementInfo moveInfoS1_;					// 移動情報
	// ステージ2で使う変数
	Util::TimeInfo stage2Time_ = { 1.0f, 0.0f };	// ステージ2の時間
	Util::TimeInfo shakeTime_ = { 0.025f, 0.0f };	// 震える間隔
	Vector2 shakeDir_ = Vector2(-5.0f, 0.0f);		// 震える方向
	// ステージ3で使う変数
	Vector2 diveVec = Vector2(0.0f, 1.0f);	// 突進する方向
	Util::MovementInfo diveInfo_;			// 突進する情報
	// ステージ4で使う変数
	Util::TimeInfo stage4Time_ = { 1.2f, 0.0f };	// ステージ4の時間
	// ステージ5で使う変数
	Util::TimeInfo stage5Time_ = { 2.0f, 0.0f };	// ステージ5の時間
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	DescentDive() {}
	~DescentDive() {}

	// 基本処理
	void Initialize(SubBossInfo* info) override;
	void Update(SubBossInfo* info) override;
	void Finalize(SubBossInfo* info) override;
#pragma endregion
};