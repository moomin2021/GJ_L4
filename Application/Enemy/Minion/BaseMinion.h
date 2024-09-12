#pragma once
#include "EnemyStatus.h"
#include "Sprite.h"

#include "M_ColliderManager.h"
#include "M_CircleCollider.h"

#include <memory>
#include <vector>

class BaseMinion
{
#pragma region メンバ変数
protected:
	// 基礎的なパラメータ
	EnemyStatus::MinionStats stats_ = {};

	// スプライト
	std::vector<std::unique_ptr<Sprite>> sprites_;
	// テクスチャ
	std::vector<uint16_t> textures_;
	// コライダー
	M_CircleCollider collider_ = {};
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	BaseMinion();
	virtual ~BaseMinion() {}

	// 各初期化処理
	virtual void Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, const std::vector<uint16_t>& inTextures);
	virtual void Update() = 0;
	virtual void MatUpadte();
	virtual void ImGuiUpdate() = 0;
	virtual void Draw();
	virtual void Finalize();

private:
	// 衝突判定コールバック関数
	virtual void CollisionCallBack() = 0;
#pragma endregion
};