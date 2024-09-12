#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"

#include "M_ColliderManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ParticleManager2D.h"

#include <memory>

class GameScene : public BaseScene
{
#pragma region メンバ変数
private:
	// インスタンス
	Key* key_ = nullptr;

	std::unique_ptr<Sprite> backGroundSprite_ = nullptr;
	int32_t backGroundTex = 0;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// 衝突判定マネージャー
    M_ColliderManager colliderManager_;

	// 敵マネージャー
	std::unique_ptr<EnemyManager> enemyMgr_ = nullptr;
    Player player_;

    ParticleManager2D* particleManagerPtr_ = ParticleManager2D::GetInstance();
    ParticleEmitter2D emitter1_{};
    uint16_t tex_{};
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
