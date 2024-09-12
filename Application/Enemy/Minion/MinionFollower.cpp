#include "MinionFollower.h"

void MinionFollower::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);
}

void MinionFollower::Update()
{
}

void MinionFollower::MatUpdate()
{
	BaseMinion::MatUpdate();
}

void MinionFollower::ImGuiUpdate(ImGuiManager* imgui)
{
	imgui = imgui;
}

void MinionFollower::Draw()
{
	BaseMinion::Draw();
}

void MinionFollower::Finalize()
{
	BaseMinion::Finalize();
}

void MinionFollower::CollisionCallBack()
{
}
