#include "StartIntro.h"
#include "TimeManager.h"
#include "Easing.h"

void StartIntro::Initialize(SubBossInfo* info)
{
	info;
}

void StartIntro::Update(SubBossInfo* info)
{
	// 時間管理クラスのインスタンスを取得
	TimeManager* timeMgr = TimeManager::GetInstance();

	// 規定の場所へ移動
	if (moveStage_ == 0) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage0Time_.GetElapsedRatio();
		info->mainColor.x = Easing::lerp(startMainColor_.x, endMainColor_.x, rate);
		info->mainColor.y = Easing::lerp(startMainColor_.y, endMainColor_.y, rate);
		info->mainColor.z = Easing::lerp(startMainColor_.z, endMainColor_.z, rate);
		info->mainColor.w = Easing::lerp(startMainColor_.w, endMainColor_.w, rate);
		// 時間を超えたら次の段階へ
		if (stage0Time_.GetIsExceeded()) moveStage_++;
	}

	else if (moveStage_ == 1) {
		// 時間の加算
		stage1Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage1Time_.GetElapsedRatio();
		info->eyeColor.x = Easing::lerp(startEyeColor_.x, endEyeColor_.x, rate);
		info->eyeColor.y = Easing::lerp(startEyeColor_.y, endEyeColor_.y, rate);
		info->eyeColor.z = Easing::lerp(startEyeColor_.z, endEyeColor_.z, rate);
		info->eyeColor.w = Easing::lerp(startEyeColor_.w, endEyeColor_.w, rate);
		// 時間を超えたら次の段階へ
		if (stage1Time_.GetIsExceeded())
		{
			moveStage_++;
			isAttackEnd_ = true;
		}
	}
}

void StartIntro::Finalize(SubBossInfo* info)
{
	info;
}