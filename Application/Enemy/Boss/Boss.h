#pragma once
#include "ImGuiManager.h"
#include "Sprite.h"
#include "Vector2.h"
#include "float4.h"

#include "Collision/M_ColliderManager.h"
#include "BossCol.h"

#include <vector>
#include <memory>

class Boss
{
#pragma region メンバ変数
private:
	// 当たり判定管理クラス
	M_ColliderManager* pColMgr_ = nullptr;

	// テクスチャ
	uint16_t bossT_ = 0;	// ボス
	uint16_t debugT_ = 0;	// デバック

	// ボス関連
	const float maxHP_ = 1000.0f;
	float nowHP_ = 0;
	Vector2 bossPos_ = Vector2();	// 座標
	Vector2 bossSize_ = Vector2();	// サイズ
	std::unique_ptr<Sprite> bossS_ = nullptr;	// スプライト
	// ヒビ
	std::unique_ptr<Sprite> crackS_ = nullptr;
	std::vector<uint16_t> crackTextures_;
	uint16_t crackT_ = 0;

	// 当たり判定関連
	std::vector<Vector2> bossColCenter_;	// 各コライダーの中心座標
	std::vector<Vector2> bossColLength_;	// 各コライダーの直径
	std::vector<BossCol> bossCol_;
	bool isDisplayCol_ = false;	// 当たり判定を表示するか

	// 色関連
	float4 startColor_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 endColor_ = float4(0.7f, 0.3f, 0.3f, 1.0f);
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	Boss();
	~Boss() {}

	// 基本処理
	void Initialize(M_ColliderManager* colMgrPtr);
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
	void ImGuiUpdate(ImGuiManager* pImGuiMgr);

	// ダメージの加算
	void AddDamage(float damage);

	// 色の更新
	void ColorUpdate();

private:
	
#pragma endregion

#pragma region ゲッター関数
public:
	/// <summary>
	/// ボスが生きているかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsAlive() { return nowHP_ >= 0.0f; }
#pragma endregion
};

