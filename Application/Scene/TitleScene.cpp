#include "TitleScene.h"
#include "PipelineManager.h"
#include "ParticleEmitter2D.h"
#include "Texture.h"

TitleScene::TitleScene(IScene* sceneIf) : BaseScene(sceneIf) {}

void TitleScene::Initialize()
{
#pragma region インスタンス
	key_ = Key::GetInstance();
	// インスタンス取得
	pImGuiMgr_ = ImGuiManager::GetInstance();
#pragma endregion

#pragma region カメラ
	camera_ = std::make_unique<Camera>();
	camera_->SetEye({ 0.0f, 20.0f, -90.0f });
	camera_->SetTarget({ 0.0f, 10.0f, 0.0f });
	Sprite::SetCamera(camera_.get());
	ParticleEmitter2D::SetCamera(camera_.get());
#pragma endregion

#pragma region スプライト
	titleStartKeySprite_ = std::make_unique<Sprite>();
	titleStartKeySprite_->SetAnchorPoint({ 0.5f,0.5f });

	wallOnlySprite_ = std::make_unique<Sprite>();
	wallOnlySprite_->SetAnchorPoint({ 0.5f,0.5f });

	// スプライトのユニーク初期化
	titleSprites_.resize(TitleSpriteSize);
	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i] = std::make_unique<Sprite>();
		titleSprites_[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

	// スプライトの値の設定

	// デフォルトサイズ
	titleSpriteDefaultSize_.resize(TitleSpriteSize);
	titleSpriteDefaultSize_[TitleWall] = { 688,352 };
	titleSpriteDefaultSize_[WallFontTex] = { 120,120 };
	titleSpriteDefaultSize_[DaFontTex] = { 188,120 };
	titleSpriteDefaultSize_[Point1Tex] = { 100,100 };
	titleSpriteDefaultSize_[DaDaTex] = { 120,120 };
	titleSpriteDefaultSize_[Point2Tex] = { 100,100 };
	titleSpriteDefaultSize_[DaDaDaTex] = { 120,120 };
	titleSpriteDefaultSize_[BoTex] = { 84,118 };

	// デフォルトスケールと現在のスケール
	titleSpriteDefaultScale_.resize(TitleSpriteSize);
	titleSpriteCurrentScale_.resize(TitleSpriteSize);
	titleSpriteDefaultPos_.resize(TitleSpriteSize);
	titleSpriteColor_.resize(TitleSpriteSize);


	// 座標
	titleSpriteDefaultPos_[TitleWall] = { 960,400 };
	titleSpriteDefaultPos_[WallFontTex] = { 810,350 };
	titleSpriteDefaultPos_[DaFontTex] = { 850,490 };
	titleSpriteDefaultPos_[Point1Tex] = { 925,470 };
	titleSpriteDefaultPos_[DaDaTex] = { 1000,455 };
	titleSpriteDefaultPos_[Point2Tex] = { 1070,440 };
	titleSpriteDefaultPos_[DaDaDaTex] = { 1150,425 };
	titleSpriteDefaultPos_[BoTex] = { 1180,425 };

	// デフォルトスケール
	titleSpriteDefaultScale_[TitleWall] = { 1,1 };
	titleSpriteDefaultScale_[WallFontTex] = { 1.2f,1.2f };
	titleSpriteDefaultScale_[DaFontTex] = { 0.6f,0.6f };
	titleSpriteDefaultScale_[Point1Tex] = { 1,1 };
	titleSpriteDefaultScale_[DaDaTex] = { 0.9f,0.9f };
	titleSpriteDefaultScale_[Point2Tex] = { 1,1 };
	titleSpriteDefaultScale_[DaDaDaTex] = { 1,1 };
	titleSpriteDefaultScale_[BoTex] = { 1,1 };

	// チェンジスケール
	titleSpriteChangeScale_.resize(TitleSpriteSize);
	titleSpriteChangeScale_[TitleWall] = { 1,1 };
	titleSpriteChangeScale_[WallFontTex] = { 1,1 };
	titleSpriteChangeScale_[DaFontTex] = { 1.2f,1.2f };
	titleSpriteChangeScale_[Point1Tex] = { 1,1 };
	titleSpriteChangeScale_[DaDaTex] = { 1.8f,1.8f };
	titleSpriteChangeScale_[Point2Tex] = { 1,1 };
	titleSpriteChangeScale_[DaDaDaTex] = { 2,2 };
	titleSpriteChangeScale_[BoTex] = { 2,2 };

	// 回転
	titleSpriteRotation_.resize(TitleSpriteSize);
	titleSpriteRotation_[TitleWall] = 0;
	titleSpriteRotation_[WallFontTex] = -10;
	titleSpriteRotation_[DaFontTex] = -10;
	titleSpriteRotation_[Point1Tex] = 0;
	titleSpriteRotation_[DaDaTex] = -9;
	titleSpriteRotation_[Point2Tex] = 0;
	titleSpriteRotation_[DaDaDaTex] = -10;
	titleSpriteRotation_[BoTex] = -9;

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSpriteCurrentScale_[i] = titleSpriteDefaultScale_[i];
		titleSpriteColor_[i] = {1,1,1,1};
	}

	startKeySpritePos_ = { 960,780 };
	startKeySpriteDefultPos_ = startKeySpritePos_;
	startKeySpriteColor_ = { 1,1,1,1 };
	wallSpritePos_ = { 960,540 };

	startKeySpriteSize_ = { 360,120 };
	wallSpriteSize_ = {1920, 1080};

	wallFontAnimeCount = 0;
	wallFontCurrentTexNum = 0;
	wallFontAnimetionTimer = 0;

	wallFontAnimeCountMax = 2;
	wallFontCurrentTexNumMax = 3;
	wallFontAnimetionTimeLimit = 3;

	easeDa_.SetPowNum(3);
	easeDa_.SetEaseLimitTime(12);
	easeDa_.Reset();
	IsBigDa_ = false;

	easeDaDa_.SetPowNum(3);
	easeDaDa_.SetEaseLimitTime(15);
	easeDaDa_.Reset();
	IsBigDaDa_ = false;

	easeDaDaDa_.SetPowNum(3);
	easeDaDaDa_.SetEaseLimitTime(20);
	easeDaDaDa_.Reset();
	easeBo_.SetPowNum(3);
	easeBo_.SetEaseLimitTime((int32_t)(20 * 1.5f));
	easeBo_.Reset();
	boRotaDefult= -9;
	IsBigDaDaDa_ = false;

	sinCount = 0;
	sinCountMax = 120;
	sinSwingValue = 10;

	IsChangeScene_ = false;
	alphaLossValue_ = 1.0f / 60;

#pragma endregion

#pragma region テクスチャ
	texture_ = LoadTexture("hae.png");
	wallFontTex_ = LoadDivTexture("KabeSheet.png", 4);

	titleTextures_.resize(TitleSpriteSize);
	titleTextures_[TitleWall] = LoadTexture("TitleKabe.png");
	titleTextures_[WallFontTex] = wallFontTex_[0];
	titleTextures_[DaFontTex] = LoadTexture("DaFont.png");
	titleTextures_[Point1Tex] = LoadTexture("pointFont.png");
	titleTextures_[DaDaTex] = LoadTexture("DadaFont.png");
	titleTextures_[Point2Tex] = LoadTexture("pointFont.png");
	titleTextures_[DaDaDaTex] = LoadTexture("DadadaFont.png");
	titleTextures_[BoTex] = LoadTexture("Bo-Font.png");

	titleStartKeyTex_ = LoadTexture("startKey.png");
	wallOnlyTex = LoadTexture("wallKariOnly.png");
#pragma endregion
}

void TitleScene::Update()
{
	if (key_->TriggerKey(DIK_SPACE)) {
		IsChangeScene_ = true;
		
	}

	// タイトルのフォントの挙動更新処理
	TitleFontStateUpdate();

	// タイトルのシーンチェンジ時の処理
	TitleChangeSceneUpdate();

	wallOnlySprite_->SetPosition(wallSpritePos_);
	wallOnlySprite_->SetSize(wallSpriteSize_);

	titleStartKeySprite_->SetPosition(startKeySpritePos_);
	titleStartKeySprite_->SetSize(startKeySpriteSize_);
	titleStartKeySprite_->SetColor(startKeySpriteColor_);


	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i]->SetPosition(titleSpriteDefaultPos_[i]);
		titleSprites_[i]->SetSize(titleSpriteDefaultSize_[i] * titleSpriteCurrentScale_[i]);
		titleSprites_[i]->SetRotation(titleSpriteRotation_[i]);
		titleSprites_[i]->SetColor(titleSpriteColor_[i]);
	}



#ifdef _DEBUG
	// ImGuiの処理
	ImGuiUpdate();

#endif
}

void TitleScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();

	// スプライト行列更新
	titleStartKeySprite_->MatUpdate();
	wallOnlySprite_->MatUpdate();

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i]->MatUpdate();
	}
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	titleStartKeySprite_->Draw(titleStartKeyTex_);
	wallOnlySprite_->Draw(wallOnlyTex);

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i]->Draw(titleTextures_[i]);
	}
}

void TitleScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}

void TitleScene::TitleFontStateUpdate()
{
	switch (fontState_)
	{
	case TitleScene::WallFontPhase:
	{
		wallFontAnimetionTimer++;


		if (wallFontAnimetionTimer >= wallFontAnimetionTimeLimit)
		{
			wallFontAnimetionTimer = 0;

			if (wallFontCurrentTexNum < wallFontCurrentTexNumMax)
			{
				wallFontCurrentTexNum++;
			}
			else {
				wallFontCurrentTexNum = 0;
				wallFontAnimeCount++;
			}
		}

		// テクスチャを変更
		titleTextures_[WallFontTex] = wallFontTex_[wallFontCurrentTexNum];

		if (wallFontAnimeCount >= wallFontAnimeCountMax)
		{
			wallFontAnimeCount = 0;
			fontState_ = DaPhase;
		}
	}
		break;
	case TitleScene::DaPhase:

		if (IsBigDa_ == false)
		{
			titleSpriteCurrentScale_[DaFontTex] = easeDa_.InPow(titleSpriteDefaultScale_[DaFontTex], titleSpriteChangeScale_[DaFontTex]);
			easeDa_.Update();

			if (easeDa_.GetIsEnd() == true)
			{
				easeDa_.Reset();
				IsBigDa_ = true;
			}
		}
		if (IsBigDa_)
		{
			titleSpriteCurrentScale_[DaFontTex] = easeDa_.OutPow(titleSpriteChangeScale_[DaFontTex], titleSpriteDefaultScale_[DaFontTex]);
			easeDa_.Update();

			if (easeDa_.GetIsEnd() == true)
			{
				easeDa_.Reset();
				IsBigDa_ = false;
				fontState_ = DaDaPhase;
			}
		}

		break;
	case TitleScene::DaDaPhase:
		if (IsBigDaDa_ == false)
		{
			titleSpriteCurrentScale_[DaDaTex] = easeDaDa_.InPow(titleSpriteDefaultScale_[DaDaTex], titleSpriteChangeScale_[DaDaTex]);
			easeDaDa_.Update();

			if (easeDaDa_.GetIsEnd() == true)
			{
				easeDaDa_.Reset();
				IsBigDaDa_ = true;
			}
		}
		if (IsBigDaDa_)
		{
			titleSpriteCurrentScale_[DaDaTex] = easeDaDa_.OutPow(titleSpriteChangeScale_[DaDaTex], titleSpriteDefaultScale_[DaDaTex]);
			easeDaDa_.Update();

			if (easeDaDa_.GetIsEnd() == true)
			{
				easeDaDa_.Reset();
				IsBigDaDa_ = false;
				fontState_ = DaDaDaPhase;
			}
		}

		break;
	case TitleScene::DaDaDaPhase:
		if (IsBigDaDaDa_ == false)
		{
			titleSpriteCurrentScale_[DaDaDaTex] = easeDaDaDa_.InPow(titleSpriteDefaultScale_[DaDaDaTex], titleSpriteChangeScale_[DaDaDaTex]);
			titleSpriteCurrentScale_[BoTex] = easeDaDaDa_.InPow(titleSpriteDefaultScale_[DaDaDaTex], titleSpriteChangeScale_[DaDaDaTex]);
			easeDaDaDa_.Update();

			if (easeDaDaDa_.GetIsEnd() == true)
			{
				easeDaDaDa_.Reset();
				IsBigDaDaDa_ = true;
			}
		}
		if (IsBigDaDaDa_)
		{
			titleSpriteCurrentScale_[DaDaDaTex] = easeDaDaDa_.OutPow(titleSpriteChangeScale_[DaDaDaTex], titleSpriteDefaultScale_[DaDaDaTex]);
			titleSpriteCurrentScale_[BoTex] = easeDaDaDa_.OutPow(titleSpriteChangeScale_[DaDaDaTex], titleSpriteDefaultScale_[DaDaDaTex]);
			easeDaDaDa_.Update();

			if (easeDaDaDa_.GetIsEnd() == true)
			{
				easeDaDaDa_.Reset();
				IsBigDaDaDa_ = false;
				easeBo_.Reset();
				fontState_ = WallFontPhase;
			}
		}
		titleSpriteRotation_[BoTex] = easeBo_.In(boRotaDefult, boRotaDefult + (360 * 3));
		easeBo_.Update();


		break;
	}

	sinCount++;
	if (sinCount >= sinCountMax)
	{
		sinCount = 0;
	}
	startKeySpritePos_.y = Sin_ZeroToOne(startKeySpriteDefultPos_.y, sinCountMax, sinCount, sinSwingValue);
}

void TitleScene::TitleChangeSceneUpdate()
{
	if (IsChangeScene_)
	{
		startKeySpriteColor_.w -= alphaLossValue_;

		for (size_t i = 0; i < TitleSpriteSize; i++)
		{
			titleSpriteColor_[i].w -= alphaLossValue_;

			if (titleSpriteColor_[i].w <= 0)
			{
				IsChangeScene_ = false;
				sceneIf_->ChangeScene(Scene::GAME);
			}
		}
	}
}

void TitleScene::ImGuiUpdate()
{
	// ウィンドウの開始
	pImGuiMgr_->BeginWindow("タイトルスプライト");

	pImGuiMgr_->InputInt("Num", debugNum, 1, 10);

	// タブバーの開始
	if (pImGuiMgr_->BeginTabBar("TitleSprite")) {
		// 座標のタブ開始
		if (pImGuiMgr_->BeginTabItem("座標")) {

			std::string s = "TitleSprite：" + std::to_string(debugNum);
			pImGuiMgr_->Text(s.c_str());
			pImGuiMgr_->InputVector2("Pos：", titleSpriteDefaultPos_[debugNum]);

			pImGuiMgr_->InputVector2("startKey", startKeySpritePos_);
			pImGuiMgr_->InputVector2("wall", wallSpritePos_);
			// ボスのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// サイズのタブ開始
		if (pImGuiMgr_->BeginTabItem("サイズ")) {

			std::string s = "TitleSprite：" + std::to_string(debugNum);
			pImGuiMgr_->Text(s.c_str());
			pImGuiMgr_->InputVector2("Size：", titleSpriteDefaultSize_[debugNum]);

			pImGuiMgr_->InputVector2("startKey", startKeySpriteSize_);
			pImGuiMgr_->InputVector2("wall", wallSpriteSize_);

			// サイズのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// サイズのタブ開始
		if (pImGuiMgr_->BeginTabItem("変化スケール")) {

			std::string s = "TitleSprite：" + std::to_string(debugNum);
			pImGuiMgr_->Text(s.c_str());
			pImGuiMgr_->InputVector2("ChangeScale：", titleSpriteChangeScale_[debugNum]);

			// サイズのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// 回転のタブ開始
		if (pImGuiMgr_->BeginTabItem("回転量")) {

			std::string s = "TitleSprite：" + std::to_string(debugNum);
			pImGuiMgr_->Text(s.c_str());
			pImGuiMgr_->InputFloat("Rotation", titleSpriteRotation_[debugNum], 1, 10);

			// サイズのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// タブバーの終了
		pImGuiMgr_->EndTabBar();
	}

	// ウィンドウの終了
	pImGuiMgr_->EndWindow();
}

float TitleScene::Sin_ZeroToOne(float pos, float maxCount, float nowCount, float swingWidth)
{
	float PI = 3.141592f;
	float result = pos + sin(PI * 2 / maxCount * nowCount) * swingWidth;
	return result;
}
