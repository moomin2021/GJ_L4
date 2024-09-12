#pragma once
#include "ImGuiManager.h"
#include "Sprite.h"

#include "M_ColliderManager.h"
#include "M_CircleCollider.h"
#include "EnemyStatus.h"
#include "Sprite.h"

#include <memory>
#include <vector>

class BaseMinion
{
#pragma region メンバ変数
protected:
	// 基礎的なパラメータ
	EnemyStatus::MinionStats stats_ = {};
	// データ
	EnemyStatus::MinionData* data_ = nullptr;

	// 回転度
	float backRotaSpd_ = 0.0f;
	float backRotation_ = 0.0f;
	float frontRotation_ = 0.0f;

	// スプライト
	std::vector<std::unique_ptr<Sprite>> sprites_;
	// コライダー
	M_CircleCollider collider_ = {};

#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	BaseMinion();
	virtual ~BaseMinion() {}

	// 各初期化処理
	virtual void Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData);
	virtual void Update() = 0;
	virtual void MatUpdate();
	virtual void ImGuiUpdate(ImGuiManager* imgui) = 0;
	virtual void Draw();
	virtual void Finalize();

	// 群れの行動の更新
	virtual void UpdateFlockBehavior(std::vector<std::unique_ptr<BaseMinion>>& others, const std::vector<std::unique_ptr<BaseMinion>>& leaders) = 0;

private:
	// 衝突判定コールバック関数
	virtual void CollisionCallBack() = 0;
#pragma endregion

#pragma region ゲッター関数
public:
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns> 座標 </returns>
	const Vector2& GetPosition() const { return stats_.position; }
	
	/// <summary>
	/// 速度の取得
	/// </summary>
	/// <returns> 速度 </returns>
	const Vector2& GetVelocity() const { return stats_.velocity; }

	/// <summary>
	/// 生存フラグの取得
	/// </summary>
	/// <returns> 生存フラグ </returns>
	bool GetIsAlive() const { return stats_.isAlive; }
#pragma endregion
};