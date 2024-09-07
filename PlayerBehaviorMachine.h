#pragma once
#include "IPlayerBehavior.h"
#include "PlayerBehaviorFactory.h"

class PlayerBehaviorMachine
{
public:
    //>> �֐�
    PlayerBehaviorMachine(void) = default;
    PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    ~PlayerBehaviorMachine(void) = default;

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior = PlayerBehavior::PB_IDLE);
    void Update(void);

private:
    // ��ԑJ�ڏ����𖞂����Ă��邩�m�F���A�J�ڂ���
    void NextStateCheck(void);

    //>> �ϐ�
    PlayerBehavior behavior_current_;
    PlayerBehavior behavior_next_;
    std::unique_ptr<IPlayerBehavior> statePtr_;
    PlayerBehaviorFactory behaviorFactory_;

public:
    void Set_Behavior(PlayerBehavior arg_nextBehavior) { behavior_next_ = arg_nextBehavior; }
    PlayerBehavior Get_Behavior(PlayerBehavior arg_nextBehavior) { return behavior_current_; }
};

