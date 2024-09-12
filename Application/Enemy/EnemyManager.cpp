#include "EnemyManager.h"

#include <string>

void EnemyManager::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr, Camera* cameraPtr)
{
	// インスタンス取得
	pImGuiMgr_ = ImGuiManager::GetInstance();
	pCamera_ = cameraPtr;

	// 敵生成器の生成
	minionFactory_ = std::make_unique<MinionFactory>();
	minionFactory_->Initialize(this, colMgrPtr, playerPtr);

	// ボスの生成、初期化
	boss_ = std::make_unique<Boss>();
	boss_->Initialize(colMgrPtr);

	// サブボスの生成、初期化
	subBoss_ = std::make_unique<SubBoss>();
	subBoss_->Initialize(colMgrPtr, playerPtr, cameraPtr);
}

void EnemyManager::Update()
{
	boss_->Update();
	subBoss_->Update();

	// 雑魚敵の更新と死んだ時の処理
	for (auto it = leaders_.begin(); it != leaders_.end();)
	{
		(*it)->Update();
		if ((*it)->GetIsAlive() == false)
		{
			(*it)->Finalize();
			it = leaders_.erase(it);
		}
		else ++it;
	}

	// 雑魚敵の更新と死んだ時の処理
	for (auto it = followers_.begin(); it != followers_.end();)
	{
		(*it)->Update();
		if ((*it)->GetIsAlive() == false)
		{
			(*it)->Finalize();
			it = followers_.erase(it);
		}
		else ++it;
	}
}

void EnemyManager::MatUpdate()
{
	boss_->MatUpdate();
	subBoss_->MatUpdate();
	for (auto& it : leaders_) it->MatUpdate();
	for (auto& it : followers_) it->MatUpdate();
}

void EnemyManager::Draw()
{
	boss_->Draw();
	subBoss_->Draw();
	for (auto& it : leaders_) it->Draw();
	for (auto& it : followers_) it->Draw();
}

void EnemyManager::Finalize()
{
	boss_->Finalize();
	subBoss_->Finalize();
	for (auto& it : leaders_) it->Finalize();
	leaders_.clear();
	for (auto& it : followers_) it->Finalize();
	followers_.clear();
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
			minionFactory_->ImGuiUpdate(pImGuiMgr_);
			// 敵一覧
			pImGuiMgr_->Text("雑魚敵リーダー一覧");
			for (auto& it : leaders_) it->ImGuiUpdate(pImGuiMgr_);
			// 敵のタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// サブボスのタブ開始
		if (pImGuiMgr_->BeginTabItem("サブボス")) {
			// サブボスクラスのImGui更新処理
			subBoss_->ImGuiUpdate();
			// サブのタブ終了
			pImGuiMgr_->EndTabItem();
		}

		// タブバーの終了
		pImGuiMgr_->EndTabBar();
	}

	// ウィンドウの終了
	pImGuiMgr_->EndWindow();
}