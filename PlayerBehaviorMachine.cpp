#include "PlayerBehaviorMachine.h"
#include <cassert>
#include "Key.h"

PlayerBehaviorMachine::PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior)
{
    Initialize(arg_commonInfomationPtr, arg_firstBehavior);
}

void PlayerBehaviorMachine::Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior)
{
    behaviorFactory_.Initialize(arg_commonInfomationPtr);
    statePtr_ = behaviorFactory_.Create(arg_firstBehavior);

    behavior_next_ = PlayerBehavior::PB_DEFAULT;
    behavior_current_ = PlayerBehavior::PB_IDLE;
}

void PlayerBehaviorMachine::Update(void)
{
    assert(statePtr_);

    BehaviorInput();
    NextStateCheck();

    // 更新処理
    statePtr_->Execute();
}

void PlayerBehaviorMachine::NextStateCheck(void)
{
    if (behavior_next_ == PlayerBehavior::PB_DEFAULT) { return; }
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

void PlayerBehaviorMachine::BehaviorInput(void)
{
    auto behavior = Get_Behavior();

    // IDLE
    if (behavior == PB_IDLE)
    {
        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { Set_Behavior(PB_MOVE); return; }

        bool isJump = Key::GetInstance()->TriggerKey(DIK_SPACE);
        if (isJump) { Set_Behavior(PB_JUMP); return; }

    }

    // JUMP
    else if (behavior == PB_JUMP)
    {
        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { Set_Behavior(PB_MOVE); return; }

        // 何も入力が無ければIDLE
        if (!isMove) { Set_Behavior(PB_IDLE); }
    }

    // WALK
    else if (behavior == PB_MOVE)
    {
        bool isJump = Key::GetInstance()->TriggerKey(DIK_SPACE);
        if (isJump) { Set_Behavior(PB_JUMP); return; }

        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { return; }

        // 何も入力が無ければIDLE
        if (!isJump) { Set_Behavior(PB_IDLE); }
    }
}
