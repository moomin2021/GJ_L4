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

#pragma region スプライト
	sprite0_ = std::make_unique<Sprite>();
	sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	sprite1_ = std::make_unique<Sprite>();
	sprite1_->SetSize({ 200.0f, 200.0f });
#pragma endregion

#pragma region テクスチャ
	texture_ = LoadTexture("hae.png");
#pragma endregion
}

void GameScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::TITLE);
	}
}

void GameScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	// スプライト行列更新
	sprite0_->MatUpdate();
	sprite1_->MatUpdate();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	sprite1_->Draw();
	sprite0_->Draw(texture_);
}

void GameScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}