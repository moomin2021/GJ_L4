#pragma once
#include "Sprite.h"

#include "M_ColliderManager.h"
#include "M_RectCollider.h"

#include <memory>

class Boss;
class BossCol
{
#pragma region メンバ変数
private:
	// ボスのポインタ
	Boss* pBoss_ = nullptr;

	// 当たり判定
	M_RectCollider collider_;

	// テクスチャ
	uint16_t debugTexture_ = 0;

	// デバック用スプライト
	std::unique_ptr<Sprite> debugSprite_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	BossCol() {}
	~BossCol() {}

	// 各基本処理
	void Initialize(Boss* bossPtr, M_ColliderManager* colMgrPtr, const Vector2& inCenter, const Vector2& inLength, size_t id);
	void Update();
	void MatUpdate();
	void Draw(bool isDebug);

private:
	// 衝突判定コールバック関数
	void CollisionCallBack();
#pragma endregion
};