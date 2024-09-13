#pragma once
#include "float4.h"
#include "Sprite.h"
#include "M_ColliderManager.h"
#include "Sprite.h"

#include "SubBossInfo.h"
#include "MoveTypes/SubBossMoveState.h"

#include <vector>
#include <string>
#include <memory>

enum class SubBossStateType {
	Wait,
	Move,
	Stun,
};

class Player;
class MinionFactory;
class EnemyManager;
class SubBoss
{
#pragma region メンバ変数
private:
	// サブボスの情報
	SubBossInfo subBossInfo_ = {};

	// サブボスの描画関連
	std::unique_ptr<Sprite> subBossSprite_ = nullptr;
	std::unique_ptr<Sprite> subBossEyeSprite_ = nullptr;
	std::vector<uint16_t> subBossTextures_;
	uint16_t subBossEyeTexture_ = 0;

	// サブボスの行動状態
	SubBossStateType currentStateType_ = SubBossStateType::Wait;
	std::vector<std::string> subBossMoveTypeStr_ = {
		"待機", "攻撃", "行動不能"
	};

	// サブボスの攻撃関連
	SubBossMoveType currentMoveType_ = SubBossMoveType::DescentDive;
	std::unique_ptr<SubBossMoveState> currentMoveState_ = nullptr;

	// デバック
	bool isDebug_ = false;
	std::unique_ptr<Sprite> colSprite_ = nullptr;
	uint16_t debugTexture_ = 0;
	std::string debugMoveTypeStr_ = "StartIntro";

	// ダメージ関連
	Util::TimeInfo damageTime_ = { 0.2f, 0.0f };
	float4 damageColor_ = float4(0.7f, 0.2f, 0.2f, 1.0f);
	bool isDamage_ = false;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	SubBoss();
	~SubBoss() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr, MinionFactory* minionFactoryPtr, EnemyManager* enemyMgrPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();

private:
	// サブボスの情報の初期化処理
	void InitializeSubBossInfo(M_ColliderManager* colMgrPtr, Camera* cameraPtr, MinionFactory* minionFactoryPtr, EnemyManager* enemyMgrPtr);

	// 状態別処理
	static void (SubBoss::* stateTable[]) ();
	void Wait();
	void Move();
	void Stun();

	// 攻撃状態に変更
	void ChangeMove();

	// 行動の抽選
	void MoveChance();

	// デバックで選択した攻撃を開始
	void DebugStartAttack();

	// ダメージを受けた時の処理
	void StartDamageProcess();
	void DamageProcess();

	// 衝突判定コールバック関数
	void CollisionCallBack();
#pragma endregion
};