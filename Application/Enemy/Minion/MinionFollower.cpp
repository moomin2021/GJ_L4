#include "MinionFollower.h"

void MinionFollower::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, const std::vector<uint16_t>& inTextures)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inTextures);
}

void MinionFollower::Update()
{
}

void MinionFollower::MatUpadte()
{
	BaseMinion::MatUpadte();
}

void MinionFollower::ImGuiUpdate()
{
}

void MinionFollower::Draw()
{
	BaseMinion::Draw();
}

void MinionFollower::Finalize()
{
	BaseMinion::Finalize();
}