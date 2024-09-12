#include "GameScene.h"
#include "PipelineManager.h"
#include "Texture.h"
#include "SmokeParticle.h"

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

#pragma region テクスチャ＆スプライト
	backGroundSprite_ = std::make_unique<Sprite>();
	backGroundSprite_->SetAnchorPoint({ 0.5f,0.5f });
	backGroundSprite_->SetPosition({ 960,540 });
	backGroundSprite_->SetSize({ 1920, 1080 });
	backGroundTex = LoadTexture("backGround.png");
#pragma endregion


    player_.Initialize(&colliderManager_);
	// 敵管理クラスの生成、初期化
	enemyMgr_ = std::make_unique<EnemyManager>();
	enemyMgr_->Initialize(&colliderManager_, &player_, camera_.get());

    particleManPtr_ = ParticleMan::GetInstance();
}

void GameScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::TITLE);
	}

    particleManPtr_->Update();

	// 各クラス更新処理
	enemyMgr_->Update();

    player_.Update();

#ifdef _DEBUG
	// ImGuiの処理
	enemyMgr_->ImGuiUpdate();

#endif
    colliderManager_.Update();
}

void GameScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	backGroundSprite_->MatUpdate();

	// スプライト行列更新
    player_.MatUpdate();
	// 各クラス行列更新処理
	enemyMgr_->MatUpdate();
    particleManPtr_->MatUpdate();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	// 背景の描画
	backGroundSprite_->Draw(backGroundTex);

	// 各クラス描画処理
	enemyMgr_->Draw();
    player_.Draw();

    particleManPtr_->Draw();
}

void GameScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
	enemyMgr_->Finalize();
}