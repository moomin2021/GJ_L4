#include "SmokeEffect.h"
#include "Texture.h"
#include"Util.h"

void SmokeEffect::Initialize(void)
{
	time_toDead = Util::GetRandomFloat(10, 15);

	position_end.x += Util::GetRandomFloat(-4, 4);
	position_end.y += Util::GetRandomFloat(-4, 4);

	size = { 64,64 };

	scale_start = { 0,0 };
	scale_end = { Util::GetRandomFloat(1,2),Util::GetRandomFloat(1,2) };

	rotate_start = Util::GetRandomFloat(-30, 30);
	rotate_end = rotate_start + Util::GetRandomFloat(-30, 30);

	color_start = { 1,1,1,1 };
	color_end = { 1,1,1,0 };

	mEaseRota.SetEaseLimitTime((int32_t)time_toDead);
	mEaseRota.SetPowNum(3);
	mEaseRota.Reset();

	textureHandle_= LoadTexture("smoke.png");

}

void SmokeEffect::Update(void)
{
	time_toDead++;

	float timeRate = time_toCurrent / time_toDead;

	float length = Util::GetRandomFloat(1, 4);



	Vector2 posVel = position_end - position_start;

	posVel.normalize();
	posVel *= length;

	// 値の更新

	// 座標
	position_current = posVel * timeRate;

	// スケール
	scale_current = (scale_end-scale_start) * timeRate;

	// 回転
	rotate_current = mEaseRota.LerpPow(rotate_start, rotate_end);

	// 色
	color_current = (color_end-color_start) * timeRate;

	// 値のセット
	sprite->SetPosition(position_current);
	sprite->SetSize(size * scale_current);
	sprite->SetRotation(rotate_current);
	sprite->SetColor(color_current);

	// 時間になったら消す
	Particle2D::Update();
}
