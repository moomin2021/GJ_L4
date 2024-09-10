#include "PlayerBehavior_Idle.h"

void PlayerBehavior_Idle::Entry(void)
{
    // 絵のずれをアンカーポイントで無理矢理補正
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_idle);
}

void PlayerBehavior_Idle::Execute(void)
{
}

void PlayerBehavior_Idle::Exit(void)
{
}
