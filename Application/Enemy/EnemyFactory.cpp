#include "EnemyFactory.h"
#include "Enemys/FloatingEnemy.h"
#include "EnemyManager.h"

void EnemyFactory::Initialize(EnemyManager* enemyMgrPtr)
{
	// 敵管理クラスの設定
	pEnemyMgr_ = enemyMgrPtr;
}

void EnemyFactory::ImGuiUpdate(ImGuiManager* imGuiMgrPtr)
{
	// 敵の生成場所の入力
	imGuiMgrPtr->InputVector2("生成座標", debugCreatePos_);

	// 敵を生成するボタン
	if (imGuiMgrPtr->Button("生成する")) {
		CreateEnemy(debugCreatePos_);
	}
}

void EnemyFactory::CreateEnemy(const Vector2& inPos)
{
	// 敵の新規生成、初期化
	std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<FloatingEnemy>();
	newEnemy->Initialize(inPos);

	// 敵管理クラスに新しく作成したデータを追加
	pEnemyMgr_->AddEnemy(std::move(newEnemy));
}
