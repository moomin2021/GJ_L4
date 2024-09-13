#include "GameClearScene.h"
#include "Texture.h"
#include "Pad.h"
#include "PipelineManager.h"

GameClearScene::GameClearScene(IScene* sceneIf) : BaseScene(sceneIf)
{

}

void GameClearScene::Initialize()
{
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
	backGroundTex = LoadTexture("gameClear.png");

	blackOutSprite_ = std::make_unique<Sprite>();
	blackOutSprite_->SetAnchorPoint({ 0.5f,0.5f });
	blackOutSprite_->SetPosition({ 960,540 });
	blackOutSprite_->SetSize({ 1920, 1080 });
	blackOutSprite_->SetColor({ 0,0,0,0 });
	blackOutTex_ = LoadTexture("white.png");
#pragma endregion
}

void GameClearScene::Update()
{
	// 色を薄く
	if (IsStartScene_ == false)
	{
		baseInColor.w -= alphaValue_;
		blackOutSprite_->SetColor(baseInColor);

		if (baseInColor.w <= 0.0f)
		{
			IsStartScene_ = true;

		}
	}
	// 画面表示
	else
	{
		if (Pad::GetInstance()->GetTriggerButton(BUTTON::PAD_A))
		{
			IsChageScene_ = true;
		}
	}

	// 色を白く
	if (IsChageScene_)
	{
		baseOutColor.w+= alphaValue_;
		blackOutSprite_->SetColor(baseOutColor);

		if (baseOutColor.w >= 1.0f)
		{
			IsChageScene_ = false;
			sceneIf_->ChangeScene(Scene::TITLE);
		}
	}
}

void GameClearScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	backGroundSprite_->MatUpdate();
	blackOutSprite_->MatUpdate();
}

void GameClearScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	backGroundSprite_->Draw(backGroundTex);
	blackOutSprite_->Draw(blackOutTex_);
}

void GameClearScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}
