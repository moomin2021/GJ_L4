#include "EnemyManager.h"

#include <string>

void EnemyManager::Initialize()
{
	// インスタンス取得
	pImGuiMgr_ = ImGuiManager::GetInstance();

	// ボスの生成、初期化
	boss_ = std::make_unique<Boss>();
	boss_->Initialize();
}

void EnemyManager::Update()
{
	boss_->Update();
}

void EnemyManager::MatUpdate()
{
	boss_->MatUpdate();
}

void EnemyManager::Draw()
{
	boss_->Draw();
}

void EnemyManager::Finalize()
{
	boss_->Finalize();
}

void EnemyManager::ImGuiUpdate()
{
	// ウィンドウの開始
	pImGuiMgr_->BeginWindow("エネミー");

	// タブバーの開始
	if (pImGuiMgr_->BeginTabBar("EnemyTab")) {
		// ボスのタブ開始
		if (pImGuiMgr_->BeginTabItem("ボス")) {
			// ボスのImGui更新処理
			boss_->ImGuiUpdate(pImGuiMgr_);
			// ボスのタブ終了
			pImGuiMgr_->EndTabItem();
		}
		// タブバーの終了
		pImGuiMgr_->EndTabBar();
	}

	// ウィンドウの終了
	pImGuiMgr_->EndWindow();
}