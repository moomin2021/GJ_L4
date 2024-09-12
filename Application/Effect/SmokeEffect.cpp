#include "SmokeEffect.h"
#include "Texture.h"
#include"Util.h"

void SmokeEffect::Initialize(void)
{
	time_toDead = Util::GetRandomInt(20, 25);

	uint16_t posRangeMin = 0;
	uint16_t posRangeMax = 50;
	position_end.x += Util::GetRandomInt(posRangeMin, posRangeMax) - posRangeMax;
	position_end.y += Util::GetRandomInt(posRangeMin, posRangeMax) - posRangeMax;

	size = { 64,64 };

	scale_start = { 0,0 };
	float scale = Util::GetRandomFloat(0.5f, 2);
	scale_end = { scale,scale };

	rotate_start = Util::GetRandomFloat(-30, 30);
	rotate_end = rotate_start;

	color_current = { 1,1,1,1 };
	color_start = { 1,1,1,1 };
	color_end = { 1,1,1,0 };

	mEaseRota.SetEaseLimitTime((int32_t)time_toDead);
	mEaseRota.SetPowNum(3);
	mEaseRota.Reset();

	textureHandle_ = LoadTexture("smoke.png");

	Particle2D::Initialize();
	sprite->SetAnchorPoint({ 0.5f, 0.5f });

	float length = Util::GetRandomFloat(50, 100);

	Vector2 posVel = position_end - position_start;

	posVel = posVel.normalize();
	posVel *= length;

	endPos_ = position_start + posVel;
}

void SmokeEffect::Update(void)
{
	//float timeRate = time_toCurrent / time_toDead;


	

	// 値の更新

	// 座標
	position_current = mEaseRota.OutPow(position_start, endPos_);

	// スケール
	scale_current = mEaseRota.OutPow(scale_start, scale_end);

	// 回転
	rotate_current = mEaseRota.OutPow(rotate_start, rotate_end);

	// 色
	color_current.w = mEaseRota.OutPow(color_start.w, color_end.w);

	mEaseRota.Update();

	// 値のセット
	sprite->SetPosition(position_current);
	sprite->SetSize(size * scale_current);
	sprite->SetRotation(rotate_current);
	sprite->SetColor(color_current);

	// 時間になったら消す
	Particle2D::Update();
}
