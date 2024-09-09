#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"
#include "M_ColliderManager.h"
#include "M_RectCollider.h"

#include <memory>

class TestScene : public BaseScene
{
#pragma region メンバ変数
private:
	// インスタンス
	Key* key_ = nullptr;

	// 衝突判定マネージャー
	M_ColliderManager colMgr_;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// プレイヤー
	Vector2 playerPos_ = Vector2(500.0f, 500.0f);
	Vector2 playerSize_ = Vector2(20.0f, 20.0f);
	std::unique_ptr<Sprite> playerS_ = nullptr;
	M_RectCollider playerC_;

	// 壁
	Vector2 wallPos_ = Vector2(800.0f, 500.0f);
	Vector2 wallSize_ = Vector2(200.0f, 100.0f);
	std::unique_ptr<Sprite> wallS_ = nullptr;
	M_RectCollider wallC_;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	TestScene(IScene* sceneIf);
	~TestScene() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();

private:
	void PlayerColCallBack();
	void WallColCallBack();
#pragma endregion
};
