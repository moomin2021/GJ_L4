#include "PlayerBehaviorMachine.h"
#include <cassert>

PlayerBehaviorMachine::PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior)
{
    arg_firstBehavior;
    Initialize(arg_commonInfomationPtr, PlayerBehavior::PB_IDLE);
}

void PlayerBehaviorMachine::Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior)
{
    statePtr_ = nullptr;
    behaviorFactory_.Initialize(arg_commonInfomationPtr);
    Set_Behavior(arg_firstBehavior);

    behavior_next_ = PlayerBehavior::PB_DEFAULT;
    behavior_current_ = PlayerBehavior::PB_IDLE;
}

void PlayerBehaviorMachine::Update(void)
{
    assert(statePtr_);

    NextStateCheck();

    // 更新処理
    statePtr_->Execute();
}

void PlayerBehaviorMachine::NextStateCheck(void)
{
    if (behavior_next_ == behavior_current_) { return; }

    // 既存のstateがあれば終了処理
    statePtr_->Exit();
    // 上書き
    statePtr_.reset();
    statePtr_ = behaviorFactory_.Create(behavior_next_);
    // 初期化処理
    statePtr_->Entry();

    // 状態も変更
    behavior_current_ = behavior_next_;
}
