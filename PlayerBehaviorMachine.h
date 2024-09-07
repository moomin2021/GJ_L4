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

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    void Update(void);

private:
    // ��ԑJ�ڏ����𖞂����Ă��邩�m�F���A�J�ڂ���
    void NextStateCheck(void);

    //>> �ϐ�
    PlayerBehavior behavior_current_;
    PlayerBehavior behavior_next_;
    std::unique_ptr<IPlayerBehavior> statePtr_;
    PlayerBehaviorFactory behaviorFactory_;
};

