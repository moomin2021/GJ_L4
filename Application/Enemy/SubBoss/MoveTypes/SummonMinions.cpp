#include "SummonMinions.h"
#include "TimeManager.h"
#include "Easing.h"
#include "Minion/MinionFactory.h"

using namespace EnemyStatus;

void SummonMinions::Initialize(SubBossInfo* info)
{
	// ステージ1で使う変数の初期化
	if (info->position.x <= 960.0f) targetPos0_.x = 1620.0f;
	else targetPos0_.x = 300.0f;
	targetPos0_.y = 400.0f;
	lastTargetPos0_ = info->position;
}

void SummonMinions::Update(SubBossInfo* info)
{
	TimeManager* timeMgr = TimeManager::GetInstance();

	// 規定の場所へ移動
	if (moveStage_ == 0) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage0Time_.GetElapsedRatio();
		info->position.x = Easing::Quint::easeOut(lastTargetPos0_.x, targetPos0_.x, rate);
		info->position.y = Easing::Quint::easeOut(lastTargetPos0_.y, targetPos0_.y, rate);
		// 時間を超えたら次の段階へ
		if (stage0Time_.GetIsExceeded()) moveStage_++;
	}

	// リーダーの召喚
	else if (moveStage_ == 1) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 時間を超えたら次の段階へ
		if (stage0Time_.GetIsExceeded()) {
			moveStage_++;
			info->minionFactoryPtr->CreateMinion(info->position, MinionType::Leader);
		}
	}
}

void SummonMinions::Finalize(SubBossInfo* info)
{
	info;
}