#include "SubBossInfo.h"

void SubBossInfo::Move(float deltaTime)
{
	position += moveVec * moveSpd * deltaTime;
}

void SubBossInfo::Rotate(float deltaTime)
{
	rotation += rotateSpd * deltaTime;
}