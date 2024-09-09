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
    ptr_playerCommonInfomation_ = arg_commonInfomationPtr;

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
    std::string strBehavior{};
    auto behavior = Get_Behavior();
    bool canJump = ptr_playerCommonInfomation_->get()->can_jump;
    bool isGround = ptr_playerCommonInfomation_->get()->is_ground;

    // IDLE
    if (behavior == PB_IDLE)
    {
        strBehavior = "PB_IDLE -> ";

        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { strBehavior += "PB_MOVE"; behaviorLog_.push_back(strBehavior); }
        if (isMove) { Set_Behavior(PB_MOVE); return; }

        bool isJump = Key::GetInstance()->TriggerKey(DIK_SPACE) && canJump && isGround;
        if (isJump) { strBehavior += "PB_JUMP"; behaviorLog_.push_back(strBehavior); }
        if (isJump) { Set_Behavior(PB_JUMP); return; }

        bool isAttack = Key::GetInstance()->TriggerKey(DIK_F);
        if (isAttack) { strBehavior += "PB_ATTACK"; behaviorLog_.push_back(strBehavior); }
        if (isAttack) { Set_Behavior(PB_ATTACK); return; }
    }

    // JUMP
    else if (behavior == PB_JUMP)
    {
        strBehavior = "PB_JUMP -> ";

        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { strBehavior += "PB_MOVE"; behaviorLog_.push_back(strBehavior); }
        if (isMove) { Set_Behavior(PB_MOVE); return; }

        bool isAttack = Key::GetInstance()->TriggerKey(DIK_F);
        if (isAttack) { strBehavior += "PB_ATTACK";  behaviorLog_.push_back(strBehavior); }
        if (isAttack) { Set_Behavior(PB_ATTACK); return; }

        // 何も入力が無ければIDLE
        bool noInput = !isMove && !isAttack;
        if (noInput) { strBehavior += "PB_IDLE"; behaviorLog_.push_back(strBehavior); }
        if (noInput) { Set_Behavior(PB_IDLE); }
    }

    // MOVE
    else if (behavior == PB_MOVE)
    {
        strBehavior = "PB_MOVE -> ";

        bool isJump = Key::GetInstance()->TriggerKey(DIK_SPACE) && canJump && isGround;
        if (isJump) { strBehavior += "PB_JUMP";  behaviorLog_.push_back(strBehavior); }
        if (isJump) { Set_Behavior(PB_JUMP); return; }

        bool isAttack = Key::GetInstance()->TriggerKey(DIK_F);
        if (isAttack) { strBehavior += "PB_ATTACK"; behaviorLog_.push_back(strBehavior); }
        if (isAttack) { Set_Behavior(PB_ATTACK); return; }

        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { return; }

        // 何も入力が無ければIDLE
        bool noInput = !isJump &&!isMove && !isAttack;
        if (noInput) { strBehavior += "PB_IDLE"; behaviorLog_.push_back(strBehavior); }
        if (noInput) { Set_Behavior(PB_IDLE); }
    }

    // ATTACK
    else if (behavior == PB_ATTACK)
    {
        strBehavior = "PB_MOVE -> ";

        // 攻撃アニメーション終了まで待機するならここにif文(!is_endAnimetion) {return;}

        bool isJump = Key::GetInstance()->TriggerKey(DIK_SPACE) && canJump && isGround;
        if (isJump) { strBehavior += "PB_JUMP";  behaviorLog_.push_back(strBehavior); }
        if (isJump) { Set_Behavior(PB_JUMP); return; }

        bool isMove = Key::GetInstance()->PushKey(DIK_A) || Key::GetInstance()->PushKey(DIK_D) || Key::GetInstance()->PushKey(DIK_W) || Key::GetInstance()->PushKey(DIK_S);
        if (isMove) { strBehavior += "PB_MOVE"; behaviorLog_.push_back(strBehavior); }
        if (isMove) { Set_Behavior(PB_MOVE); return; }

        // 何も入力が無ければIDLE
        bool noInput = !isJump && !isMove;
        if (noInput) { strBehavior += "PB_IDLE"; behaviorLog_.push_back(strBehavior); }
        if (noInput) { Set_Behavior(PB_IDLE); }
    }
}
