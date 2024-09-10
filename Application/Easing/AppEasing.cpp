#include "AppEasing.h"
#include "math.h"
#include <algorithm>

AppEasing::AppEasing():
	timer_(0),timeRate_(0),
	limitTimer_(0),IsEnd_(false)
{
}

AppEasing::AppEasing(const int32_t limitTime):
	timer_(0), timeRate_(0),
	limitTimer_(limitTime), powNum_(1), IsEnd_(false)
{
}

AppEasing::AppEasing(const int32_t limitTimer, const float powNum):
	timer_(0), timeRate_(0),
	limitTimer_(limitTimer), powNum_(powNum), IsEnd_(false)
{
}

void AppEasing::Update()
{
	timer_++;
	if (timeRate_ >= 1)
	{
		IsEnd_ = true;
	}

	timer_ = std::min(timer_, limitTimer_);
	timeRate_ = std::min((float)timer_ / limitTimer_, (float)1);
}

void AppEasing::Reset()
{
	timer_ = 0;
	timeRate_ = 0;
	IsEnd_ = false;
}

void AppEasing::SetEaseLimitTime(const int32_t limitTime)
{
	limitTimer_ = limitTime;
}

void AppEasing::SetEaseType(const EaseType easeType)
{
	easeType_ = easeType;
}

void AppEasing::SetPowNum(const float powNum)
{
	powNum_ = powNum;
}

void AppEasing::SetIsEnd(const bool isEnd)
{
	IsEnd_ = isEnd;
}

int32_t AppEasing::GetTimer()
{
	return timer_;
}

int32_t AppEasing::GetLimitTime()
{
	return limitTimer_;
}

AppEasing::EaseType AppEasing::GetEaseType()
{
	return easeType_;
}

bool AppEasing::GetIsEnd()
{
	return IsEnd_;
}

float AppEasing::Lerp(const float startPos, const float endPos)
{
	float dis = endPos - startPos;
	return dis * timeRate_ + startPos;
}

Vector3 AppEasing::Lerp(const Vector3& start, const Vector3& end)
{
	Vector3 dis = end - start;
	return dis * timeRate_ + start;
}

//追加
float AppEasing::In(float start, float end)
{
	float move = end - start;
	return start + (move * timeRate_ * timeRate_);
}

float AppEasing::Out(float start, float end)
{
	
	float move = end - start;
	return start + (move * (1 - (1 - timeRate_) * (1 - timeRate_)));
}

Vector3 AppEasing::OutVec3(Vector3 start, Vector3 end)
{
	Vector3 Vec;
	float x = Out(static_cast <float>(start.x), static_cast <float>(end.x));
	float y = Out(static_cast <float>(start.y), static_cast <float>(end.y));
	float z = Out(static_cast <float>(start.z), static_cast <float>(end.z));

	Vec = { (float)x,(float)y,(float)z };

	return Vec;
}

float AppEasing::InOut(float start, float end)
{
	float move = end - start;
	if (timeRate_ < 0.5)
	{
		return start + (move * (2 * timeRate_ * timeRate_));
	}
	else
	{
		return start + move * (1 - (((-2 * timeRate_ + 2) * (-2 * timeRate_ + 2)) / 2));
	}
}

Vector3 AppEasing::InOut(Vector3 start, Vector3 end)
{
	Vector3 Vec;
	float x = InOut(static_cast <float>(start.x), static_cast <float>(end.x));
	float y = InOut(static_cast <float>(start.y), static_cast <float>(end.y));
	float z = InOut(static_cast <float>(start.z), static_cast <float>(end.z));

	Vec = { (float)x,(float)y,(float)z };

	return Vec;
}

float AppEasing::In_Back(float start, float end)
{
	
	float move = end - start;
	float c1 = 1.70158f;
	float c3 = (c1 + 1);
	return start + (move * (c3 * timeRate_ * timeRate_ * timeRate_ - c1 * timeRate_ * timeRate_));
}

float AppEasing::Out_Back(float start, float end)
{
	float move = end - start;
	float c1 = 1.70158f;
	float c3 = (c1 + 1);
	return start + (move * (1 + c3 * ((timeRate_ - 1) * (timeRate_ - 1) * (timeRate_ - 1)) + c1 * ((timeRate_ - 1) * (timeRate_ - 1))));
}

float AppEasing::InOut_Back(float start, float end)
{
	float move = end - start;
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;

	if (timeRate_ < 0.5f)
	{
		return start + move * ((((2 * timeRate_) * (2 * timeRate_)) * ((c2 + 1) * 2 * timeRate_ - c2)) / 2);
	}
	else
	{
		return start + move * ((((2 * timeRate_ - 2) * (2 * timeRate_ - 2)) * ((c2 + 1) * (timeRate_ * 2 - 2) + c2) + 2) / 2);
	}
}

float AppEasing::Out_Bounce(float start, float end)
{
	float move = end - start;
	float n1 = 7.5625f;
	float d1 = 2.75f;
	if (timeRate_ < 1 / d1) {
		return start + move * (n1 * timeRate_ * timeRate_);
	}
	else if (timeRate_ < 2 / d1) {
		return start + move * (n1 * (timeRate_ -= 1.5f / d1) * timeRate_ + 0.75f);
	}
	else if (timeRate_ < 2.5f / d1) {
		return start + move * (n1 * (timeRate_ -= 2.25f / d1) * timeRate_ + 0.9375f);
	}
	else {
		return start + move * (n1 * (timeRate_ -= 2.625f / d1) * timeRate_ + 0.984375f);
	}
}

float AppEasing::In_Bounce(float start, float end)
{
	float move = end - start;
	float n1 = 7.5625f;
	float d1 = 2.75f;
	timeRate_ = 1 - timeRate_;
	if (timeRate_ < 1 / d1) {
		return start + move * (1 - (n1 * timeRate_ * timeRate_));
	}
	else if (timeRate_ < 2 / d1) {
		return start + move * (1 - (n1 * (timeRate_ -= 1.5f / d1) * timeRate_ + 0.75f));
	}
	else if (timeRate_ < 2.5f / d1) {
		return start + move * (1 - (n1 * (timeRate_ -= 2.25f / d1) * timeRate_ + 0.9375f));
	}
	else {
		return start + move * (1 - (n1 * (timeRate_ -= 2.625f / d1) * timeRate_ + 0.984375f));
	}

}

float AppEasing::InOut_Bounce(float start, float end)
{
	float move = end - start;
	float n1 = 7.5625f;
	float d1 = 2.75f;
	if (timeRate_ < 0.5f)
	{
		timeRate_ = 1 - timeRate_ * 2;
		if (timeRate_ < 1 / d1) {
			return start + move * ((1 - (n1 * timeRate_ * timeRate_)) / 2);
		}
		else if (timeRate_ < 2 / d1) {
			return start + move * ((1 - (n1 * (timeRate_ -= 1.5f / d1) * timeRate_ + 0.75f)) / 2);
		}
		else if (timeRate_ < 2.5f / d1) {
			return start + move * ((1 - (n1 * (timeRate_ -= 2.25f / d1) * timeRate_ + 0.9375f)) / 2);
		}
		else {
			return start + move * ((1 - (n1 * (timeRate_ -= 2.625f / d1) * timeRate_ + 0.984375f)) / 2);
		}
	}
	else
	{
		timeRate_ = timeRate_ * 2 - 1;
		if (timeRate_ < 1 / d1) {
			return start + move * ((n1 * timeRate_ * timeRate_) / 2 + 0.5f);
		}
		else if (timeRate_ < 2 / d1) {
			return start + move * ((n1 * (timeRate_ -= 1.5f / d1) * timeRate_ + 0.75f) / 2 + 0.5f);
		}
		else if (timeRate_ < 2.5f / d1) {
			return start + move * ((n1 * (timeRate_ -= 2.25f / d1) * timeRate_ + 0.9375f) / 2 + 0.5f);
		}
		else {
			return start + move * ((n1 * (timeRate_ -= 2.625f / d1) * timeRate_ + 0.984375f) / 2 + 0.5f);
		}
	}
}


float AppEasing::easeOutCubic(float start, float end){
	float x = (float)1 - (float)pow(1 - timeRate_, 3);

	return start + (end - start) * x;
}


float AppEasing::easeInCirc(float start, float end){

	float x = (float)1 - (float)sqrt(1 - pow(timeRate_, 2));

	return start + (end - start) * x;
}

Vector2 AppEasing::easeInCircVec2(Vector2 start, Vector2 end)
{
	Vector2 Vec;
	float x = easeInCirc(start.x, end.x);
	float y = easeInCirc(start.y, end.y);

	Vec = { static_cast <float>(x),static_cast <float>(y)};

	return Vec;
}

Vector3 AppEasing::easeInCircVec3(Vector3 start, Vector3 end)
{
	Vector3 Vec;
	float x = easeInCirc(start.x, end.x);
	float y = easeInCirc(start.y, end.y);
	float z = easeInCirc(start.z, end.z);

	Vec = { static_cast <float>(x),static_cast <float>(y),static_cast <float>(z) };

	return Vec;
}

float AppEasing::LerpBezireQuadratic(const float& start, const float& contRollP, const float& end)
{
	float p1, p2, p3;
	p1 = Lerp(start, contRollP);
	p2 = Lerp(contRollP, end);
	p3 = Lerp(p1, p2);

	return p3;
}

Vector3 AppEasing::LerpBezireQuadratic(const Vector3& start, const Vector3& contRollP, const Vector3& end)
{

	Vector3 p1, p2, p3;
	p1 = Lerp(start, contRollP);
	p2 = Lerp(contRollP, end);
	p3 = Lerp(p1, p2);

	return p3;
}

Vector3 AppEasing::easeOutCircVec3(Vector3 start, Vector3 end)
{
	Vector3 InOutVec;
	float x = easeOutCubic(start.x, end.x);
	float y = easeOutCubic(start.y, end.y);
	float z = easeOutCubic(start.z, end.z);

	InOutVec = { x,y,z };

	return InOutVec;
}

// ラープ
float AppEasing::LerpPow(const float startPos, const float endPos)
{
	float dis = endPos - startPos;
	return dis * timeRate_ + startPos;
}
Vector2 AppEasing::LerpPow(const Vector2 startPos, const Vector2 endPos)
{
	Vector2 dis = endPos - startPos;
	return dis * timeRate_ + startPos;
}
Vector3 AppEasing::LerpPow(const Vector3 startPos, const Vector3 endPos)
{
	Vector3 dis = endPos - startPos;
	return dis * timeRate_ + startPos;
}

// イン
float AppEasing::InPow(const float startPos, const float endPos)
{
	float dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) + startPos;
}
Vector2 AppEasing::InPow(const Vector2 startPos, const Vector2 endPos)
{
	Vector2 dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) + startPos;
}
Vector3 AppEasing::InPow(const Vector3 startPos, const Vector3 endPos)
{
	Vector3 dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) + startPos;
}

// アウト
float AppEasing::OutPow(const float startPos, const float endPos)
{
	float dis = endPos - startPos;
	if ((int32_t)powNum_ % 2 == 1)
	{
		return dis * (powf(timeRate_ - 1, powNum_) + 1) + startPos;
	}
	return dis * -1 * (powf(timeRate_ - 1, powNum_) - 1) + startPos;
}
Vector2 AppEasing::OutPow(const Vector2 startPos, const Vector2 endPos)
{
	Vector2 dis = endPos - startPos;
	if ((int32_t)powNum_ % 2 == 1)
	{
		return dis * (powf(timeRate_ - 1, powNum_) + 1) + startPos;
	}
	return dis * -1 * (powf(timeRate_ - 1, powNum_) - 1) + startPos;
}
Vector3 AppEasing::OutPow(const Vector3 startPos, const Vector3 endPos)
{
	Vector3 dis = endPos - startPos;
	if ((int32_t)powNum_ % 2 == 1)
	{
		return dis * (powf(timeRate_ - 1, powNum_) + 1) + startPos;
	}
	return dis * -1 * (powf(timeRate_ - 1, powNum_) - 1) + startPos;
}

// インアウト
float AppEasing::InOutPow(const float startPos, const float endPos)
{
	float dis = (endPos - startPos);

	if (timeRate_ < 0.5f)
	{
		return dis / 2.f * powf(timeRate_ * 2.f, powNum_) + startPos;
	}
	return -dis / 2.f * (powf((1.f - (timeRate_ - 0.5f) * 2.f), powNum_) - 2.f) + startPos;

}
Vector2 AppEasing::InOutPow(const Vector2 startPos, const Vector2 endPos)
{
	Vector2 dis = (endPos - startPos) / 2;
	if (timeRate_ < 0.5f)
	{
		return InPow(startPos, endPos);
	}
	return OutPow(startPos, endPos);
}
Vector3 AppEasing::InOutPow(const Vector3 startPos, const Vector3 endPos)
{
	Vector3 dis = (endPos - startPos);

	if (timeRate_ < 0.5f)
	{
		return dis / 2.f * powf(timeRate_ * 2.f, powNum_) + startPos;
	}
	return -dis / 2.f * (powf((1.f - (timeRate_ - 0.5f) * 2.f), powNum_) - 2.f) + startPos;
}

// インバック
float AppEasing::InBackPow(const float startPos, const float endPos)
{
	const float back1 = 1.70154f;

	float dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) * ((back1 + 1.0f) * timeRate_ - back1) + startPos;
}
Vector2 AppEasing::InBackPow(const Vector2 startPos, const Vector2 endPos)
{
	const float back1 = 1.70154f;

	Vector2 dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) * ((back1 + 1.0f) * timeRate_ - back1) + startPos;
}
Vector3 AppEasing::InBackPow(const Vector3 startPos, const Vector3 endPos)
{
	const float back1 = 1.70154f;

	Vector3 dis = endPos - startPos;
	return dis * powf(timeRate_, powNum_) * ((back1 + 1.0f) * timeRate_ - back1) + startPos;
}