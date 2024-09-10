#include "SubBossAttackState.h"
#include "TimeManager.h"
#include "Easing.h"
#include "Util.h"

void DescentDiveState::Initialize(SubBossInfo* info)
{
	presetTargetPos_ = info->position;
	targetPos_ = Vector2(960.0f, 400.0f);
}

void DescentDiveState::Update(SubBossInfo* info)
{
	// 時間管理クラスのインスタンスを取得
	TimeManager* timeMgr = TimeManager::GetInstance();

	// 規定の場所へ移動
	if (attackState_ == 0) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();

		// 座標移動
		float rate = stage0Time_.GetElapsedRatio();
		info->position.x = Easing::Quint::easeOut(presetTargetPos_.x, targetPos_.x, rate);
		info->position.y = Easing::Quint::easeOut(presetTargetPos_.y, targetPos_.y, rate);

		// 時間を超えたか
		if (stage0Time_.GetIsExceeded()) {
			// 次の段階へ
			attackState_++;
		}
	}
}

void DescentDiveState::Finalize(SubBossInfo* info)
{
	info = info;
}