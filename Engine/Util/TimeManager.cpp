#include "TimeManager.h"
#include "Util.h"

TimeManager* TimeManager::GetInstance()
{
	static TimeManager instance;
	return &instance;
}

void TimeManager::Initialize()
{
	// インスタンス取得
	imGuiMgr_ = ImGuiManager::GetInstance();

	// 現在の時間でoldTime_を初期化
	oldTime_ = std::chrono::system_clock::now();
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

void TimeManager::ImGuiUpdate()
{
#ifdef _DEBUG
	imGuiMgr_->BeginWindow("TimeManager");

	imGuiMgr_->Text("DeltaTime = %f", deltaTime_);
	imGuiMgr_->Text("GameDeltaTime = %f", gameDeltaTime_);
	imGuiMgr_->InputFloat("ゲーム速度", gameSpd_, 0.1f, 1.0f);

	static float gameTime = 0.0f;
	gameTime += deltaTime_;
	imGuiMgr_->Text("ゲーム開始から%f秒", gameTime);
	imGuiMgr_->EndWindow();
#endif
}