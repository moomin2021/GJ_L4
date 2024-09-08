#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"

#include "M_ColliderManager.h"
#include "EnemyManager.h"

#include <memory>

class GameScene : public BaseScene
{
#pragma region メンバ変数
private:
	// インスタンス
	Key* key_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// 衝突判定マネージャー
    M_ColliderManager colliderManager_;

	// 敵マネージャー
	std::unique_ptr<EnemyManager> enemyMgr_ = nullptr;
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
