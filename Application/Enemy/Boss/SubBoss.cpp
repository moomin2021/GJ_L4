#include "SubBoss.h"
#include "Player.h"

void SubBoss::Initialize(M_ColliderManager* colMgrPtr, Player* playerPtr)
{
	// プレイヤーのポインタ受取
	pPlayer_ = playerPtr;
	colMgrPtr = colMgrPtr;

}

void SubBoss::Update()
{
}

void SubBoss::MatUpdate()
{
}

void SubBoss::Draw()
{
}

void SubBoss::Finalize()
{
}

void SubBoss::ImGuiUpdate()
{
}
