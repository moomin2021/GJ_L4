#include "MinionLeader.h"

void MinionLeader::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, const std::vector<uint16_t>& inTextures)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inTextures);
}

void MinionLeader::Update()
{
}

void MinionLeader::MatUpadte()
{
	BaseMinion::MatUpadte();
}

void MinionLeader::ImGuiUpdate()
{
}

void MinionLeader::Draw()
{
	BaseMinion::Draw();
}

void MinionLeader::Finalize()
{
	BaseMinion::Finalize();
}