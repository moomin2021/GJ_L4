#include <memory>
#include "PlayerBehaviorFactory.h"
#include "PlayerBehavior_Idle.h"
#include "PlayerBehavior_Move.h"
#include "PlayerBehavior_Jump.h"

PlayerBehaviorFactory::PlayerBehaviorFactory(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr)
{
    Initialize(arg_commonInfomationPtr);
}

void PlayerBehaviorFactory::Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr)
{
    ptr_playerCommonInfomation_ = arg_commonInfomationPtr;
}

std::unique_ptr<IPlayerBehavior> PlayerBehaviorFactory::Create(PlayerBehavior arg_state)
{
    if (arg_state == PlayerBehavior::PB_IDLE) { return std::make_unique<PlayerBehavior_Idle>(*ptr_playerCommonInfomation_); }
    else if (arg_state == PlayerBehavior::PB_MOVE) { return std::make_unique<PlayerBehavior_Move>(*ptr_playerCommonInfomation_); }
    else if (arg_state == PlayerBehavior::PB_JUMP) { return std::make_unique<PlayerBehavior_Jump>(*ptr_playerCommonInfomation_); }

    return nullptr;
}
