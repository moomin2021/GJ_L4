#pragma once
#include "SubBoss/SubBossInfo.h"
#include "Util.h"

#include <vector>
#include <string>

// 攻撃タイプ文字列
const std::vector<std::string> subBossMoveTypeStr = {
	"StartIntro",
	"EndGameOutro",
	"DescentDive",
};

// 攻撃タイプ
enum class SubBossMoveType {
	StartIntro,
	EndGameOutro,
	DescentDive,
};

// ベースクラス
class SubBossMoveState {
protected:
	// 現在の攻撃段階
	size_t moveStage_ = 0;

	// 攻撃終了したか
	bool isAttackEnd_ = false;

public:
	// デストラクタ
	virtual ~SubBossMoveState() = default;

	// 基本処理
	virtual void Initialize(SubBossInfo* info) = 0;
	virtual void Update(SubBossInfo* info) = 0;
	virtual void Finalize(SubBossInfo* info) = 0;

	// 攻撃終了したかを取得
	bool GetIsAttackEnd() { return isAttackEnd_; }
};