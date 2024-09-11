#pragma once
#include "ImGuiManager.h"

#include <chrono>

class TimeManager
{
#pragma region メンバ変数
private:
	// インスタンス
	ImGuiManager* imGuiMgr_ = nullptr;

	// 1フレの経過時間
	float deltaTime_ = 0.0f;	// スローやヒットストップの影響を受けないものに使う(UIなど)
	float gameDeltaTime_ = 0.0f;// スローやヒットストップを掛けるものに使う(例：プレイヤーや敵)

	// ゲーム速度
	float gameSpd_ = 1.0f;

	// 1フレ前の時間
	std::chrono::system_clock::time_point oldTime_;
#pragma endregion

#pragma region メンバ関数
public:
	// インスタンス取得
	static TimeManager* GetInstance();

	// 更新処理
	void Initialize();
	void Update();
	void ImGuiUpdate();

private:
	// コンストラクタとデストラクタ
	TimeManager() {}
	~TimeManager() {}
#pragma endregion

#pragma region 特殊関数
public:
	TimeManager(const TimeManager&) = delete;				// コピーコンストラクタ禁止
	TimeManager& operator = (const TimeManager&) = delete;	// コピー代入演算子禁止
#pragma endregion

#pragma region セッター関数
public:
	/// <summary>
	/// ゲーム速度を設定
	/// </summary>
	/// <param name="gameSpd"> ゲーム速度 </param>
	void SetGameSpd(float gameSpd) { gameSpd_ = gameSpd; }
#pragma endregion

#pragma region ゲッター関数
	/// <summary>
	/// デルタタイムの取得
	/// </summary>
	/// <returns> デルタタイム </returns>
	float GetDeltaTime() { return deltaTime_; }

	/// <summary>
	/// ゲームデルタタイムの取得
	/// </summary>
	/// <returns> ゲームデルタタイム </returns>
	float GetGameDeltaTime() { return gameDeltaTime_; }

	/// <summary>
	/// ゲーム速度の取得
	/// </summary>
	/// <returns> ゲーム速度 </returns>
	float GetGameSpd() { return gameSpd_; }
#pragma endregion
};