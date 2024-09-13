#include "GameOverScene.h"
#include <Texture.h>
#include "Pad.h"

GameOverScene::GameOverScene(IScene* sceneIf) : BaseScene(sceneIf)
{

}

void GameOverScene::Initialize()
{
	key_ = Key::GetInstance();

#pragma region テクスチャ＆スプライト
	backGroundSprite_ = std::make_unique<Sprite>();
	backGroundSprite_->SetAnchorPoint({ 0.5f,0.5f });
	backGroundSprite_->SetPosition({ 960,540 });
	backGroundSprite_->SetSize({ 1920, 1080 });
	backGroundTex = LoadTexture("gameOver.png");

	blackOutSprite_ = std::make_unique<Sprite>();
	blackOutSprite_->SetAnchorPoint({ 0.5f,0.5f });
	blackOutSprite_->SetPosition({ 960,540 });
	blackOutSprite_->SetSize({ 1920, 1080 });
	blackOutSprite_->SetColor({ 0,0,0,0 });
	blackOutTex_ = LoadTexture("white.png");

#pragma endregion

	IsStartScene_ = false;
}

void GameOverScene::Update()
{
	// 色を薄く
	if (IsStartScene_ == false)
	{
		float4 color = baseInColor;
		color.w = blackBaseColor.w - alphaValue_;
		blackOutSprite_->SetColor(color);

		if (color.w <= 0.0f)
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

	// 色を黒く
	if (IsChageScene_)
	{
		float4 color = baseOutColor;
		color.w = blackBaseColor.w + alphaValue_;
		blackOutSprite_->SetColor(color);

		if (color.w >= 1.0f)
		{
			IsChageScene_ = false;
			sceneIf_->ChangeScene(Scene::TITLE);
		}
	}
}

void GameOverScene::MatUpdate()
{
	backGroundSprite_->MatUpdate();
	blackOutSprite_->MatUpdate();
}

void GameOverScene::Draw()
{
	backGroundSprite_->Draw(backGroundTex);
	blackOutSprite_->Draw(blackOutTex_);
}

void GameOverScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}
