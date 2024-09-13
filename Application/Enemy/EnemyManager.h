#pragma once
#include "ImGuiManager.h"
#include "Collision/M_ColliderManager.h"

#include "Boss/Boss.h"
#include "SubBoss/SubBoss.h"
#include "Minion/BaseMinion.h"
#include "Minion/MinionFactory.h"

class Player;
class EnemyManager
{
#pragma region メンバ変数
private:
	// インスタンス
	ImGuiManager* pImGuiMgr_ = nullptr;
	Camera* pCamera_ = nullptr;

	// 敵生成器
	std::unique_ptr<MinionFactory> minionFactory_ = nullptr;

	// ボス
	std::unique_ptr<Boss> boss_ = nullptr;

	// サブボス
	std::unique_ptr<SubBoss> subBoss_ = nullptr;

	// 雑魚敵
	std::vector<std::unique_ptr<BaseMinion>> leaders_;
	std::vector<std::unique_ptr<BaseMinion>> followers_;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	EnemyManager() {}
	~EnemyManager() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate();

	// 雑魚敵の追加
	void AddLeader(std::unique_ptr<BaseMinion> newLeader) { leaders_.emplace_back(std::move(newLeader)); }
	void AddFollower(std::unique_ptr<BaseMinion> newFollower) { followers_.emplace_back(std::move(newFollower)); }
#pragma endregion

#pragma region ゲッター関数
public:
	/// <summary>
	/// ミニオンの数を取得
	/// </summary>
	/// <returns> ミニオンの数 </returns>
	size_t GetMinionAmount() { return leaders_.size() + followers_.size(); }

	/// <summary>
	/// ボスが生きているか
	/// </summary>
	/// <returns></returns>
	bool GetIsBossAlive() { return boss_->GetIsAlive(); }
#pragma endregion
};