#include "PlayerBehaviorMachine.h"

PlayerBehaviorMachine::PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr)
{
    Initialize(arg_commonInfomationPtr);
}

void PlayerBehaviorMachine::Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr)
{
    statePtr_ = nullptr;
    behaviorFactory_.Initialize(arg_commonInfomationPtr);
}

void PlayerBehaviorMachine::Update(void)
{
    // null�`�F�b�N
    if (!statePtr_) { return; }

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
