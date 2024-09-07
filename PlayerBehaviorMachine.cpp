#include "PlayerBehaviorMachine.h"
#include <cassert>

PlayerBehaviorMachine::PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr)
{
    Initialize(arg_commonInfomationPtr);
}

void PlayerBehaviorMachine::Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior)
{
    statePtr_ = nullptr;
    behaviorFactory_.Initialize(arg_commonInfomationPtr);
    Set_Behavior(arg_firstBehavior);
}

void PlayerBehaviorMachine::Update(void)
{
    assert(statePtr_);

    NextStateCheck();

    // ��ԍX�V
    statePtr_->Execute();
}

void PlayerBehaviorMachine::NextStateCheck(void)
{
    if (behavior_next_ == behavior_current_) { return; }

    // ������state������ΏI������
    statePtr_->Exit();
    // �㏑��
    statePtr_.reset();
    statePtr_ = behaviorFactory_.Create(behavior_next_);
    // ����������
    statePtr_->Entry();
}
