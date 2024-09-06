#include "TitleScene.h"
#include "PipelineManager.h"
#include "Texture.h"

TitleScene::TitleScene(IScene* sceneIf) : BaseScene(sceneIf) {}

void TitleScene::Initialize()
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
	sprite0_->SetSize({ 200.0f, 200.0f });
	sprite1_ = std::make_unique<Sprite>();
	sprite1_->SetColor({ 1.0f, 1.0f, 1.0f, 0.5f });
#pragma endregion

#pragma region テクスチャ
	texture_ = LoadTexture("hae.png");
#pragma endregion
}

void TitleScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::GAME);
	}
}

void TitleScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	// スプライト行列更新
	sprite0_->MatUpdate();
	sprite1_->MatUpdate();
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite");

	sprite0_->Draw(texture_);
	sprite1_->Draw();
}

void TitleScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}