#pragma once
#include <vector>
#include <string>

namespace Util {

	struct TimeInfo {
		// 設定時間
		float setTime = 0.0f;
		// 経過時間
		float elapsedTime = 0.0f;

		// 経過した割合を返す
		float GetElapsedRatio();
		// 経過時間が設定時間を超えたか
		bool GetIsExceeded();
	};

	const float PI = 3.141592654f;

	// --ここから自作関数-- //

	/// <summary>
	/// 入れた値が最大値を上回っていたら最大値を返し、最小値を下回っていたら最小値を返す。
	/// どちらにも当てはまらない場合は、値をそのまま返す
	/// </summary>
	/// <param name="value"> 値 </param>
	/// <param name="max"> 最大値 </param>
	/// <param name="min"> 最小値 </param>
	/// <returns></returns>
	int Clamp(int value, int max, int min);

	/// <summary>
	/// 入れた値が最大値を上回っていたら最大値を返し、最小値を下回っていたら最小値を返す。
	/// どちらにも当てはまらない場合は、値をそのまま返す
	/// </summary>
	/// <param name="value"> 値 </param>
	/// <param name="max"> 最大値 </param>
	/// <param name="min"> 最小値 </param>
	/// <returns></returns>
	float Clamp(float value, float max, float min);

	/// <summary>
	/// 入れた値を比較し大きい値を返す
	/// </summary>
	/// <param name="value0"> 値 </param>
	/// <param name="value1"> 値 </param>
	/// <returns></returns>
	float Max(float value0, float value1);

	/// <summary>
	/// 入れた値を比較し小さい値を返す
	/// </summary>
	/// <param name="value0"> 値 </param>
	/// <param name="value1"> 値 </param>
	/// <returns></returns>
	float Min(float value0, float value1);

	/// <summary>
	/// 弧度法の値を度数法にして返す
	/// </summary>
	/// <param name="radian"> 弧度法の値 </param>
	/// <returns></returns>
	float Radian2Degree(float radian);

	/// <summary>
	/// 度数法の値を弧度法にして返す
	/// </summary>
	/// <param name="degree"> 度数法の値 </param>
	/// <returns></returns>
	float Degree2Radian(float degree);

	/// <summary>
	/// std::stringからWideCharに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::vector<wchar_t> StringToWideChar(const std::string& str);

	/// <summary>
	/// 指定された範囲内でランダムな整数を返す
	/// </summary>
	/// <param name="min"> 最小値 </param>
	/// <param name="max"> 最大値 </param>
	/// <returns> 整数値 </returns>
	uint16_t GetRandomInt(uint16_t min, uint16_t max);

	/// <summary>
	/// 指定された範囲内でランダムな少数値を返す
	/// </summary>
	/// <param name="min"> 最小値 </param>
	/// <param name="max"> 最大値 </param>
	/// <returns> 小数値 </returns>
	float GetRandomFloat(float min, float max);

	/// <summary>
	/// 現在時刻を取得[s]
	/// </summary>
	/// <returns> 時間(s) </returns>
	uint64_t GetTimeSec();

	/// <summary>
	/// 現在時刻を取得[ms]
	/// </summary>
	/// <returns> 時間(ms) </returns>
	uint64_t GetTimrMSec();

	/// <summary>
	/// 小数点の四捨五入
	/// </summary>
	/// <param name="value"> 値 </param>
	/// <param name="num"> 小数点第何位 </param>
	/// <returns></returns>
	float Round(float value, uint8_t num);

	float NormalizeAngle(float angle);
} // namespace MathUtility
