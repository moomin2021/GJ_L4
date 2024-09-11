#include "Shake.h"
#include "Util.h"

void Shake::SetShake(const Vector2& intensity, float duration)
{
	intensity_ = intensity;
	shakeDuration_ = duration;
	elapsedTime_ = 0.0f;
	offset_ = Vector2();
}

void Shake::Update(float deltaTime)
{
	// 経過時間が設定した持続時間より小さいなら
	if (elapsedTime_ < shakeDuration_)
	{
		// 時間経過処理
		elapsedTime_ += deltaTime;
		// シェイク
		Vector2 shakeAmount = Vector2();
		shakeAmount.x = intensity_.x * (1.0f - (elapsedTime_ / shakeDuration_));
		shakeAmount.y = intensity_.y * (1.0f - (elapsedTime_ / shakeDuration_));
		// ランダム
		Vector2 rnd = { (float)(Util::GetRandomInt(0, 1) % 2) * 2 - 1 , (float)(Util::GetRandomInt(0, 1) % 2) * 2 - 1 };
		offset_.x = rnd.x * shakeAmount.x;
		offset_.y = rnd.y * shakeAmount.y;
	}

	else
	{
		offset_ = Vector2();
	}
}