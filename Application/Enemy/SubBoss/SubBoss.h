#pragma once
#include "Sprite.h"
#include "M_ColliderManager.h"
#include "Sprite.h"

#include "SubBossInfo.h"
#include "SubBossAttackState.h"

#include <vector>
#include <string>
#include <memory>

enum class SubBossMoveType {
	Wait,
	Attack,
	Stun,
};

class Player;
class SubBoss
{
#pragma region メンバ変数
private:
	// サブボスの情報
	SubBossInfo subBossInfo_ = {};

	// サブボスの描画関連
	std::unique_ptr<Sprite> subBossSprite_ = nullptr;
	std::vector<uint16_t> subBossTextures_;

	// サブボスの行動状態
	SubBossMoveType currentMoveType_ = SubBossMoveType::Wait;
	std::vector<std::string> subBossMoveTypeStr_ = {
		"待機", "攻撃", "行動不能"
	};

	// サブボスの攻撃関連
	SubBossAttackType currentAttackType_ = SubBossAttackType::DescentDiveState;
	std::unique_ptr<SubBossAttackState> currentAttackState_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	SubBoss();
	~SubBoss() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();

private:
	// サブボスの情報の初期化処理
	void InitializeSubBossInfo();

	// 状態別処理
	static void (SubBoss::* stateTable[]) ();
	void Wait();
	void Attack();
	void Stun();

	// 攻撃状態に変更
	void ChangeAttack();
#pragma endregion
};