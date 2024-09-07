#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"

#include "M_ColliderManager.h"

#include <memory>

class GameScene : public BaseScene
{
#pragma region メンバ変数
private:
	// インスタンス
	Key* key_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// スプライト
	std::unique_ptr<Sprite> sprite0_ = nullptr;
	std::unique_ptr<Sprite> sprite1_ = nullptr;

	// テクスチャ
	int32_t texture_ = 0;

    M_ColliderManager colliderManager_;
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	GameScene(IScene* sceneIf);
	~GameScene() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
#pragma endregion
};
