#include "MinionLeader.h"

void MinionLeader::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);
}

void MinionLeader::Update()
{
}

void MinionLeader::MatUpdate()
{
	BaseMinion::MatUpdate();
}

void MinionLeader::ImGuiUpdate(ImGuiManager* imgui)
{
	imgui = imgui;
}

void MinionLeader::Draw()
{
	BaseMinion::Draw();
}

void MinionLeader::Finalize()
{
	BaseMinion::Finalize();
}

void MinionLeader::CollisionCallBack()
{

}