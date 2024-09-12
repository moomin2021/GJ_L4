#pragma once
#include "ParticleMan.h"
#include "AppEasing.h"

class SmokeEffect:
	public Particle2D
{
public:
	SmokeEffect(void) = default;
	~SmokeEffect(void)override = default;

	void Initialize(void)override;

	void Update(void)override;

private:// メンバー変数
	AppEasing mEaseRota;

	Vector2 endPos_;
};

