#include "TimeManager.h"

TimeManager* TimeManager::GetInstance()
{
	static TimeManager instance;
	return &instance;
}

void TimeManager::Update()
{
	// 現在の時間を取得
	std::chrono::system_clock::time_point nowTime = std::chrono::system_clock::now();

	// デルタタイムの計算
	deltaTime_ = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(nowTime - oldTime_).count() / 1000000.0f);

	// 現在の時間を1フレーム前の時間として保存
	oldTime_ = nowTime;

	// ゲームデルタタイムの計算
	gameDeltaTime_ = deltaTime_ * gameSpd_;
}