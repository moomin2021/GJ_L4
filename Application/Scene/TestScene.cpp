#include "TestScene.h"
#include "PipelineManager.h"
#include "ParticleEmitter2D.h"
#include "Texture.h"

TestScene::TestScene(IScene* sceneIf) : BaseScene(sceneIf) {}

void TestScene::Initialize()
{
#pragma region インスタンス
	key_ = Key::GetInstance();
#pragma endregion

#pragma region カメラ
	camera_ = std::make_unique<Camera>();
	camera_->SetEye({ 0.0f, 20.0f, -90.0f });
	camera_->SetTarget({ 0.0f, 10.0f, 0.0f });
	Sprite::SetCamera(camera_.get());
	ParticleEmitter2D::SetCamera(camera_.get());
#pragma endregion

#pragma region プレイヤー
	// スプライト
	playerS_ = std::make_unique<Sprite>();
	playerS_->SetPosition(playerPos_);
	playerS_->SetSize(playerSize_);
	playerS_->SetAnchorPoint({ 0.5f, 0.5f });
	// コライダー
	playerC_.square_.center = playerPos_;
	playerC_.square_.length = playerSize_;
	std::string name0 = "Player";
	auto callback0 = std::bind(&TestScene::PlayerColCallBack, this);
	playerC_.Initialize(name0, callback0, &colMgr_);
#pragma endregion

#pragma region 壁
	// スプライト
	wallS_ = std::make_unique<Sprite>();
	wallS_->SetPosition(wallPos_);
	wallS_->SetSize(wallSize_);
	wallS_->SetAnchorPoint({ 0.5f, 0.5f });
	// コライダー
	wallC_.square_.center = wallPos_;
	wallC_.square_.length = wallSize_;
	std::string name1 = "Wall";
	auto callback1 = std::bind(&TestScene::WallColCallBack, this);
	wallC_.Initialize(name1, callback1, &colMgr_);
#pragma endregion
}

void TestScene::Update()
{
	if (key_->TriggerKey(DIK_Q)) {
		sceneIf_->ChangeScene(Scene::TITLE);
	}

	// プレイヤーの移動処理
	playerPos_.x += (key_->PushKey(DIK_D) - key_->PushKey(DIK_A)) * 2.0f;
	playerPos_.y += (key_->PushKey(DIK_S) - key_->PushKey(DIK_W)) * 2.0f;
	playerC_.square_.center = playerPos_;


	// プレイヤーの座標更新
	playerS_->SetPosition(playerPos_);

	// 衝突判定クラスの更新処理
	colMgr_.Update();
}

void TestScene::MatUpdate()
{
	// カメラ更新
	camera_->Update();
	playerS_->MatUpdate();
	wallS_->MatUpdate();
}

void TestScene::Draw()
{
	PipelineManager::PreDraw("Sprite");
	playerS_->Draw();
	wallS_->Draw();
}

void TestScene::Finalize()
{
	Texture::GetInstance()->ReleaseIntermediateResources();
}

void TestScene::PlayerColCallBack()
{
	if (playerC_.IsDetect_Col()) playerS_->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	else playerS_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}

void TestScene::WallColCallBack()
{
	if (wallC_.IsDetect_Col()) wallS_->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	else wallS_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}