#pragma once
#include "SubBossInfo.h"
#include "Util.h"

// 攻撃タイプ
enum class SubBossAttackType {
	DescentDiveState,
};

// ベースクラス
class SubBossAttackState {
protected:
	// 現在の攻撃段階
	size_t attackStage_ = 0;

	// 攻撃終了したか
	bool isAttackEnd_ = false;

public:
	// デストラクタ
	virtual ~SubBossAttackState() = default;

	// 基本処理
	virtual void Initialize(SubBossInfo* info) = 0;
	virtual void Update(SubBossInfo* info) = 0;
	virtual void Finalize(SubBossInfo* info) = 0;

	// 攻撃終了したかを取得
	bool GetIsAttackEnd() { return isAttackEnd_; }
};

class DescentDiveState : public SubBossAttackState {
#pragma region メンバ変数
private:
	// ステージ0で使う変数
	Util::TimeInfo stage0Time_ = { 1.0f, 0.0f };	// ステージ0の時間
	Vector2 targetPos_ = Vector2();					// 目標の座標
	Vector2 presetTargetPos_ = Vector2();			// 目標前の座標
	// ステージ1で使う変数
	Util::TimeInfo stage1Time_ = { 5.0f, 0.0f };	// ステージ1の時間
	Util::MovementInfo moveInfoS1_;					// 移動情報
	// ステージ2で使う変数
	Util::TimeInfo stage2Time_ = { 1.0f, 0.0f };	// ステージ2の時間
	Util::TimeInfo shakeTime_ = { 0.025f, 0.0f };	// 震える間隔
	Vector2 shakeDir_ = Vector2(-5.0f, 0.0f);		// 震える方向
	// ステージ3で使う変数
	Util::TimeInfo stage3Time_ = { 1.0f, 0.0f };// ステージ3の時間
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	DescentDiveState() {}
	~DescentDiveState() {}

	// 基本処理
	void Initialize(SubBossInfo* info) override;
	void Update(SubBossInfo* info) override;
	void Finalize(SubBossInfo* info) override;
#pragma endregion
};