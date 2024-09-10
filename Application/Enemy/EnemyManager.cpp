#include "EnemyManager.h"

#include <string>

void EnemyManager::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// インスタンス取得
	pImGuiMgr_ = ImGuiManager::GetInstance();

	// 敵生成器の生成
	enemyFactory_ = std::make_unique<EnemyFactory>();
	enemyFactory_->Initialize(this, colMgrPtr, playerPtr);

	// ボスの生成、初期化
	boss_ = std::make_unique<Boss>();
	boss_->Initialize(colMgrPtr);

	// サブボスの生成、初期化
	subBoss_ = std::make_unique<SubBoss>();
	subBoss_->Initialize(colMgrPtr, playerPtr);
}

void EnemyManager::Update()
{
	boss_->Update();
	subBoss_->Update();

	// 敵の更新と死んだ時の処理
	for (auto it = enemys_.begin(); it != enemys_.end();)
	{
		(*it)->Update();
		if ((*it)->GetIsAlive() == false)
		{
			(*it)->Finalize();
			it = enemys_.erase(it);
		}
		else ++it;
	}
}

void EnemyManager::MatUpdate()
{
	boss_->MatUpdate();
	subBoss_->MatUpdate();
	for (auto& it : enemys_) it->MatUpdate();
}

void EnemyManager::Draw()
{
	boss_->Draw();
	subBoss_->Draw();
	for (auto& it : enemys_) it->Draw();
}

void EnemyManager::Finalize()
{
	boss_->Finalize();
	subBoss_->Finalize();
	for (auto& it : enemys_) it->Finalize();
	enemys_.clear();
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

		// 敵のタブ開始
		if (pImGuiMgr_->BeginTabItem("敵")) {
			// 敵生成器クラスのImGui更新処理
			enemyFactory_->ImGuiUpdate(pImGuiMgr_);
			// 敵一覧
			pImGuiMgr_->Text("敵一覧");
			for (auto& it : enemys_) it->ImGuiUpdate(pImGuiMgr_);
			// 敵のタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// タブバーの終了
		pImGuiMgr_->EndTabBar();
	}

	// ウィンドウの終了
	pImGuiMgr_->EndWindow();
}