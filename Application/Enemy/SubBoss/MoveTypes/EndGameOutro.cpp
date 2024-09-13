#include "EndGameOutro.h"
#include "TimeManager.h"
#include "Easing.h"

void EndGameOutro::Initialize(SubBossInfo* info)
{
	info;
}

void EndGameOutro::Update(SubBossInfo* info)
{
	// 時間管理クラスのインスタンスを取得
	TimeManager* timeMgr = TimeManager::GetInstance();

	// 目を消す
	if (moveStage_ == 0) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage0Time_.GetElapsedRatio();
		info->eyeColor.x = Easing::lerp(startEyeColor_.x, endEyeColor_.x, rate);
		info->eyeColor.y = Easing::lerp(startEyeColor_.y, endEyeColor_.y, rate);
		info->eyeColor.z = Easing::lerp(startEyeColor_.z, endEyeColor_.z, rate);
		info->eyeColor.w = Easing::lerp(startEyeColor_.w, endEyeColor_.w, rate);
		// 時間を超えたら次の段階へ
		if (stage0Time_.GetIsExceeded()) moveStage_++;
	}

	// 規定の場所へ移動
	else if (moveStage_ == 1) {
		// 速度を更新
		velocity_ += acceleration_ * timeMgr->GetGameDeltaTime();
		// 速度の制限
		velocity_.x = Util::Clamp(velocity_.x, limitSpd_, -limitSpd_);
		velocity_.y = Util::Clamp(velocity_.y, limitSpd_, -limitSpd_);
		// 座標の更新
		info->position += velocity_ * timeMgr->GetGameDeltaTime();
	}
}

void EndGameOutro::Finalize(SubBossInfo* info)
{
	info;
}