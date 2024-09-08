#include "SceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "TestScene.h"

SceneManager::SceneManager()
{
	// インスタンス取得
	imGuiMgr_ = ImGuiManager::GetInstance();
	dx12Cmd_ = DX12Cmd::GetInstance();
	timeMgr_ = TimeManager::GetInstance();
	particleMgr2D = ParticleManager2D::GetInstance();
}

void SceneManager::Initialize()
{
	// 時間管理クラスの初期化
	timeMgr_->Initialize();

	// パーティクル2D初期化
	particleMgr2D->Initialize();

	// 最初のシーンの生成と初期化
	nowScene_ = std::make_unique<GameScene>(this);
	nowScene_->Initialize();
}

void SceneManager::Update()
{
	// 時間管理クラスの更新
	timeMgr_->Update();

	// 次のシーンが設定されたら
	if (nextScene_ != Scene::NONE)
	{
		// 現在のシーンの終了処理を実行
		nowScene_->Finalize();
		nowScene_.reset();

		// シーンの生成
		switch (nextScene_)
		{
			case Scene::TITLE:
				nowScene_ = std::make_unique<TitleScene>(this);
				break;
			case Scene::GAME:
				nowScene_ = std::make_unique<GameScene>(this);
				break;
			case Scene::TEST:
				nowScene_ = std::make_unique<TestScene>(this);
				break;
		}

		// シーンの初期化
		nowScene_->Initialize();

		// 次のシーンをクリア
		nextScene_ = Scene::NONE;
	}

	// ImGuiの処理開始
	imGuiMgr_->Begin();

	// 現在のシーンを更新
	nowScene_->Update();
	particleMgr2D->Update();
	nowScene_->MatUpdate();
	particleMgr2D->MatUpdate();

	timeMgr_->ImGuiUpdate();

	if (Key::GetInstance()->TriggerKey(DIK_T)) ChangeScene(Scene::TEST);
}

void SceneManager::Draw()
{
	// 描画前処理
	dx12Cmd_->PreDraw();

	// パーティクルを描画
	particleMgr2D->DrawBack();

	// 現在のシーンの描画
	nowScene_->Draw();

	// パーティクルを描画
	particleMgr2D->DrawFront();

	// ImGuiの終了処理と描画処理
	imGuiMgr_->End();
	imGuiMgr_->Draw();

	// 描画後後処理
	dx12Cmd_->PostDraw();
}

void SceneManager::ChangeScene(const Scene& nextScene)
{
	// 次のシーンを設定
	nextScene_ = nextScene;
}

void SceneManager::GameEnd()
{
	isGameEnd_ = true;
}