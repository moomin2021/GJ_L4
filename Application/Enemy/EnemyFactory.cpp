#include "EnemyFactory.h"
#include "Texture.h"
#include "Enemys/FloatingEnemy.h"
#include "EnemyManager.h"
#include "Player.h"

void EnemyFactory::Initialize(EnemyManager* enemyMgrPtr, M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// ポインタ受取り
	pEnemyMgr_ = enemyMgrPtr;
	pColMgr_ = colMgrPtr;
	pPlayer_ = playerPtr;

	// テクスチャの読み込み
	textures_.emplace_back(LoadTexture("zakoEnemy01.png"));
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
	newEnemy->Initialize(createCounter_, inPos, textures_[0], pColMgr_, pPlayer_);

	// 敵管理クラスに新しく作成したデータを追加
	pEnemyMgr_->AddEnemy(std::move(newEnemy));

	// カウントを進める
	createCounter_++;
}
