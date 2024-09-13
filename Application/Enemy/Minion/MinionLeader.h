#pragma once
#include "BaseMinion.h"
#include "Util.h"

class MinionLeader : public BaseMinion
{
#pragma region メンバ変数
private:
	// 殴られたあとに使う基本変数
	Vector2 moveVec_ = Vector2();
	float moveSpd_ = 0.0f;

	// 一回目殴られた時に使う変数
	Vector2 firstBeatenVec_ = Vector2(0.0f, 1.0f);// 殴られた時の方向
	float firstBeatenMoveSpd_ = 800.0f;// 殴った時の移動速度
	float firstBeatenRotaSpd_ = 800.0f;// 殴った時の回転速度

	// ノックバックしている時に使う変数
	Vector2 knockVec_ = Vector2(0.0f, -1.0f);
	float knockFirstSpd_ = 600.0f;// ノックバックした時の最初の速度
	float knockAddSpd_ = 300.0f;// 徐々に加算される速度
	float knockFirstRotaSpd_ = 600.0f;// 最初の回転速度
	float knockAddRotaSpd_ = 300.0f;// 徐々に加算される回転速度

	// 二回目殴られた時に使う変数
	Vector2 secondBeatenVec_ = Vector2(0.0f, 0.0f);// 殴られた時の方向
	float secondBeatenMoveSpd_ = 1000.0f;// 殴った時の移動速度
	float secondBeatenRotaSpd_ = 1000.0f;// 殴った時の回転速度

	// 死ぬまでの時間
	float nowTime_ = 0.0f;
	float aliveTime_ = 4.0f;

	// 召喚された時
	Util::TimeInfo spawnTime_ = { 1.0f, 0.0f };
	Vector2 targetPos_ = Vector2(0.0f, 700.0f);
	Vector2 lastTargetPos_ = Vector2();
	Vector2 stateMoveXAcc_ = Vector2();
	float amolitude_ = 100.0f;
	float baseY_ = 700.0f;
	float stateMoveXTime_ = 0.0f;
	float stateMoveXSpd_ = 1.0f;

    int32_t particleFrame_{};
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	MinionLeader() {}
	~MinionLeader() {}

	// 各初期化処理
	void Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData) override;
	void Update() override;
	void MatUpdate() override;
	void ImGuiUpdate(ImGuiManager* imgui) override;
	void Draw() override;
	void Finalize() override;

	// 群れの行動の更新
	void UpdateFlockBehavior(std::vector<std::unique_ptr<BaseMinion>>& others, const std::vector<std::unique_ptr<BaseMinion>>& leaders) override;

private:
	// 衝突判定コールバック関数
	void CollisionCallBack() override;

	// 移動の更新処理
	void MoveUpdate();

	// 状態別処理
	static void (MinionLeader::* stateTable[]) ();
	void Normal();
	void FirstBeaten();
	void KnockBack();
	void SecondBeaten();
	void MoveX();
	void Spawn();
#pragma endregion
};
