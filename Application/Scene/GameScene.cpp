#include "GameScene.h"
#include "PipelineManager.h"
#include "Texture.h"
#include "SmokeParticle.h"
#include "Trajectory.h"

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

	blackOutSprite_= std::make_unique<Sprite>();
	blackOutSprite_->SetAnchorPoint({ 0.5f,0.5f });
	blackOutSprite_->SetPosition({ 960,540 });
	blackOutSprite_->SetSize({ 1920, 1080 });
	blackOutSprite_->SetColor({ 0,0,0,0 });
	blackOutTex_ = LoadTexture("white.png");

	IsGameOver = false;
	IsGameClear = false;
#pragma endregion


    player_.Initialize(&colliderManager_);
	// 敵管理クラスの生成、初期化
	enemyMgr_ = std::make_unique<EnemyManager>();
	enemyMgr_->Initialize(&colliderManager_, &player_, camera_.get());

    particleManPtr_ = ParticleMan::GetInstance();

	sound_ = Sound::GetInstance();

	bgm_ = sound_->LoadWave("Resources/Sound/Beast-From-Hell_loop.wav", 0.15f);

	IsPlayBgm_ = false;

	baseColor = { 0,0,0,0 };
	whiteBaseColor = { 1,1,1,0 };
}

void GameScene::Update()
{
	if (IsPlayBgm_ == false)
	{
		sound_->Play(bgm_, true);
		IsPlayBgm_ = true;
	}

#ifdef _DEBUG
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::TITLE);
	}

    if (key_->TriggerKey(DIK_N)) {
        particleManPtr_->AddParticle(std::make_unique<TrajectoryParticle>(), { 500,500 });
    }
#endif // _DEBUG

	if (player_.Get_IsAllDead())
	{
		// 徐々に暗くなる
		float4 color;
		baseColor.w += alphaValue_;
		blackOutSprite_->SetColor(baseColor);

		if (baseColor.w >= 1.0f)
		{
			// シーンチェンジ
			sceneIf_->ChangeScene(Scene::OVER);
		}
	}

	if (enemyMgr_->GetIsBossAlive()==false)
	{

		whiteBaseColor.w += alphaValue_;
		blackOutSprite_->SetColor(whiteBaseColor);

		if (whiteBaseColor.w >= 1.0f)
		{
			// シーンチェンジ
			sceneIf_->ChangeScene(Scene::CLEAR);
		}
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
	blackOutSprite_->MatUpdate();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	// 背景の描画
	backGroundSprite_->Draw(backGroundTex);

    particleManPtr_->Draw();
	// 各クラス描画処理
	enemyMgr_->Draw();
    player_.Draw();

	// 画面の前面にあるシーンチェンジ用黒いもの
	blackOutSprite_->Draw(blackOutTex_);
}

void GameScene::Finalize()
{
	sound_->Stop(bgm_);
	Texture::GetInstance()->ReleaseIntermediateResources();
	enemyMgr_->Finalize();
}