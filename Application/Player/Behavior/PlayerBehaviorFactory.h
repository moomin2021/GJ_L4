#pragma once
#include "IPlayerBehavior.h"

class PlayerBehaviorFactory
{
public:
    //>> �֐�
    PlayerBehaviorFactory(void) = default;
    PlayerBehaviorFactory(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    ~PlayerBehaviorFactory(void) = default;

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    std::unique_ptr<IPlayerBehavior> Create(PlayerBehavior arg_state);

private:
    //>> �ϐ�
    std::shared_ptr<PlayerCommonInfomation>* ptr_playerCommonInfomation_{};
};

