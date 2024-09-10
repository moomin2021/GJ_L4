#pragma once
#include "SubBossInfo.h"

// 攻撃タイプ
enum class SubBossAttackType {
	DescentDiveState,
};

// ベースクラス
class SubBossAttackState {
protected:
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