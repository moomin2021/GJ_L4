#include "GameScene.h"
#include "PipelineManager.h"
#include "Texture.h"

GameScene::GameScene(IScene* sceneIf) : BaseScene(sceneIf) {}

void GameScene::Initialize()
{
#pragma region インスタンス
	key_ = Key::GetInstance();
#pragma endregion

#pragma region カメラ
	camera_ = std::make_unique<Camera>();
	camera_->SetEye({ 0.0f, 20.0f, -90.0f });
	camera_->SetTarget({ 0.0f, 10.0f, 0.0f });
	Sprite::SetCamera(camera_.get());
#pragma endregion

	// 敵管理クラスの生成、初期化
	enemyMgr_ = std::make_unique<EnemyManager>();
	enemyMgr_->Initialize(&colliderManager_);
}

void GameScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::TITLE);
	}

	// 各クラス更新処理
	enemyMgr_->Update();
    colliderManager_.Update();

	// ImGuiの処理
	enemyMgr_->ImGuiUpdate();
}

void GameScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	// 各クラス行列更新処理
	enemyMgr_->MatUpdate();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	
	// 各クラス描画処理
	enemyMgr_->Draw();
}

void GameScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
	enemyMgr_->Finalize();
}