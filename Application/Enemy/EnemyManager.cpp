#include "EnemyManager.h"

#include <string>

void EnemyManager::Initialize()
{
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