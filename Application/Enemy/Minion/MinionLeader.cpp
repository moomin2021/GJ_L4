#include "MinionLeader.h"

void MinionLeader::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);

	// コライダーの設定
	collider_.circle_.center = stats_.position;
	collider_.circle_.radius = 32.0f;
	std::string name = "Minion";
	auto callback = std::bind(&MinionLeader::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
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