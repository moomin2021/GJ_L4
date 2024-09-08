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
	pImGuiMgr_->BeginWindow("Enemy");
	boss_->ImGuiUpdate(pImGuiMgr_);
	pImGuiMgr_->EndWindow();
}