#pragma once
#include "IPlayerBehavior.h"

class PlayerBehaviorFactory
{
public:
    //>> ä÷êî
    PlayerBehaviorFactory(void) = default;
    PlayerBehaviorFactory(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    ~PlayerBehaviorFactory(void) = default;

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    std::unique_ptr<IPlayerBehavior> Create(PlayerBehavior arg_state);

private:
    //>> ïœêî
    std::shared_ptr<PlayerCommonInfomation>* ptr_playerCommonInfomation_{};
};

