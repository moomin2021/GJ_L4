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
	sprite0_ = std::make_unique<Sprite>();
	sprite0_->SetSize({ 200.0f, 200.0f });
	sprite1_ = std::make_unique<Sprite>();
	sprite1_->SetColor({ 1.0f, 1.0f, 1.0f, 0.5f });

	// スプライトのユニーク初期化
	titleSprites_.resize(TitleSpriteSize);
	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i] = std::make_unique<Sprite>();
	}

	// スプライトの値の設定

	// デフォルトサイズ
	titleSpriteDefaultSize_.resize(TitleSpriteSize);
	titleSpriteDefaultSize_[TitleWall] = { 100,100 };
	titleSpriteDefaultSize_[WallFontTex] = { 100,100 };
	titleSpriteDefaultSize_[DaFontTex] = { 100,100 };
	titleSpriteDefaultSize_[Point1Tex] = { 100,100 };
	titleSpriteDefaultSize_[DaDaTex] = { 100,100 };
	titleSpriteDefaultSize_[Point2Tex] = { 100,100 };
	titleSpriteDefaultSize_[DaDaDaTex] = { 100,100 };
	titleSpriteDefaultSize_[BoTex] = { 100,100 };

	// デフォルトスケールと現在のスケール
	titleSpriteDefaultScale_.resize(TitleSpriteSize);
	titleSpriteCurrentScale_.resize(TitleSpriteSize);
	titleSpriteDefaultPos_.resize(TitleSpriteSize);

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSpriteDefaultScale_[i] = { 1,1 };
		titleSpriteCurrentScale_[i] = titleSpriteDefaultScale_[i];
		titleSpriteDefaultPos_[i] = { 500,500 };
	}

	// チェンジスケール
	titleSpriteChangeScale_.resize(TitleSpriteSize);
	titleSpriteChangeScale_[TitleWall] = { 1,1 };
	titleSpriteChangeScale_[WallFontTex] = { 1,1 };
	titleSpriteChangeScale_[DaFontTex] = { 1.5f,1.5f };
	titleSpriteChangeScale_[Point1Tex] = { 1,1 };
	titleSpriteChangeScale_[DaDaTex] = { 1.8f,1.8f };
	titleSpriteChangeScale_[Point2Tex] = { 1,1 };
	titleSpriteChangeScale_[DaDaDaTex] = { 2,2 };
	titleSpriteChangeScale_[BoTex] = { 2,2 };
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

#pragma endregion
}

void TitleScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::GAME);
	}

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSpriteCurrentScale_[i] = titleSpriteChangeScale_[i];

		titleSprites_[i]->SetPosition(titleSpriteDefaultPos_[i]);
		titleSprites_[i]->SetSize(titleSpriteDefaultSize_[i] * titleSpriteCurrentScale_[i]);
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
	sprite0_->MatUpdate();
	sprite1_->MatUpdate();

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i]->MatUpdate();
	}
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	sprite0_->Draw(texture_);
	sprite1_->Draw();

	for (size_t i = 0; i < TitleSpriteSize; i++)
	{
		titleSprites_[i]->Draw(titleTextures_[i]);
	}
}

void TitleScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
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

			// ボスのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// サイズのタブ開始
		if (pImGuiMgr_->BeginTabItem("サイズ")) {

			std::string s = "TitleSprite：" + std::to_string(debugNum);
			pImGuiMgr_->Text(s.c_str());
			pImGuiMgr_->InputVector2("Size：", titleSpriteDefaultSize_[debugNum]);

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

		// タブバーの終了
		pImGuiMgr_->EndTabBar();
	}

	// ウィンドウの終了
	pImGuiMgr_->EndWindow();
}
