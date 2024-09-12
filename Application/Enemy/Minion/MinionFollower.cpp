#include "MinionFollower.h"

void MinionFollower::Initialize(M_ColliderManager* colMgrPtr, const EnemyStatus::MinionStats& inStats, EnemyStatus::MinionData* inData)
{
	BaseMinion::Initialize(colMgrPtr, inStats, inData);

	// コライダーの設定
	collider_.circle_.center = stats_.position;
	collider_.circle_.radius = 32.0f;
	std::string name = "Minion";
	auto callback = std::bind(&MinionFollower::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
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
