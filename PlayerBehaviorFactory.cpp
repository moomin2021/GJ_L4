#include "PlayerBehaviorFactory.h"

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
    if (arg_state == PlayerBehavior::PB_IDLE) { return nullptr; }
    else if (arg_state == PlayerBehavior::PB_WALK) { return nullptr; }
    else if (arg_state == PlayerBehavior::PB_JUMP) { return nullptr; }

    return nullptr;
}
