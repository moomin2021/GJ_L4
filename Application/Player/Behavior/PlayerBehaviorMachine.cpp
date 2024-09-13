#include "PlayerBehaviorMachine.h"
#include <cassert>
#include "Key.h"
#include "Pad.h"

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

    if (behaviorLog_.size() >= 100) { behaviorLog_.clear(); }
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
    if (ptr_playerCommonInfomation_->get()->health_current <= 0) { return; }

    std::string strBehavior{};
    auto behavior = Get_Behavior();
    bool canJump = ptr_playerCommonInfomation_->get()->move.can_jump;
    bool isGround = ptr_playerCommonInfomation_->get()->move.is_ground;

    Key* ptr_key = Key::GetInstance();
    Pad* ptr_pad = Pad::GetInstance();
    const auto& keyBind = ptr_playerCommonInfomation_->get()->keyBind;
    const auto& controllerBind = ptr_playerCommonInfomation_->get()->controllerBind;

    // IDLE
    if (behavior == PB_IDLE)
    {
        strBehavior = "PB_IDLE/";

        bool isMove{};
        isMove = ptr_key->PushKey(keyBind.move_left) || ptr_key->PushKey(keyBind.move_right) || ptr_key->PushKey(keyBind.move_up) || ptr_key->PushKey(keyBind.move_down);
        isMove = (std::max)(ptr_pad->GetLStick().x != 0 || ptr_pad->GetLStick().y != 0, isMove);
        if (isMove)
        {
            strBehavior += "PB_MOVE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_MOVE);
            return;
        }

        bool isJump{};
        isJump = ptr_key->TriggerKey(keyBind.jump) && canJump && isGround;
        isJump = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.jump) && canJump && isGround, isJump);
        if (isJump)
        {
            strBehavior += "PB_JUMP";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_JUMP);
            return;
        }

        bool isSpecial{};
        isSpecial = ptr_key->TriggerKey(keyBind.special);
        isSpecial = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.special), isSpecial);
        if (isSpecial)
        {
            strBehavior += "PB_SPECIAL";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_SPECIAL);
            return;
        }

        bool isAttack{};
        isAttack = ptr_key->TriggerKey(keyBind.attack);
        isAttack = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.attack), isAttack);
        if (isAttack)
        {
            strBehavior += "PB_ATTACK";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_ATTACK);
            return;
        }
    }

    // JUMP
    else if (behavior == PB_JUMP)
    {
        strBehavior = "PB_JUMP/";

        bool isMove{};
        isMove = ptr_key->PushKey(keyBind.move_left) || ptr_key->PushKey(keyBind.move_right) || ptr_key->PushKey(keyBind.move_up) || ptr_key->PushKey(keyBind.move_down);
        isMove = (std::max)(ptr_pad->GetLStick().x != 0 || ptr_pad->GetLStick().y != 0, isMove);
        if (isMove)
        {
            strBehavior += "PB_MOVE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_MOVE);
            return;
        }

        bool isSpecial{};
        isSpecial = ptr_key->TriggerKey(keyBind.special);
        isSpecial = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.special), isSpecial);
        if (isSpecial)
        {
            strBehavior += "PB_SPECIAL";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_SPECIAL);
            return;
        }

        bool isAttack{};
        isAttack = ptr_key->TriggerKey(keyBind.attack);
        isAttack = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.attack), isAttack);
        if (isAttack)
        {
            strBehavior += "PB_ATTACK";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_ATTACK);
            return;
        }

        // 何も入力が無ければIDLE
        bool noInput = !isMove && !isAttack;
        if (noInput)
        {
            strBehavior += "PB_IDLE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_IDLE);
        }
    }

    // MOVE
    else if (behavior == PB_MOVE)
    {
        strBehavior = "PB_MOVE/";

        bool isJump{};
        isJump = ptr_key->TriggerKey(keyBind.jump) && canJump && isGround;
        isJump = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.jump) && canJump && isGround, isJump);
        if (isJump)
        {
            strBehavior += "PB_JUMP";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_JUMP);
            return;
        }

        bool isSpecial{};
        isSpecial = ptr_key->TriggerKey(keyBind.special);
        isSpecial = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.special), isSpecial);
        if (isSpecial)
        {
            strBehavior += "PB_SPECIAL";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_SPECIAL);
            return;
        }

        bool isAttack{};
        isAttack = ptr_key->TriggerKey(keyBind.attack);
        isAttack = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.attack), isAttack);
        if (isAttack)
        {
            strBehavior += "PB_ATTACK";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_ATTACK);
            return;
        }

        bool isMove{};
        isMove = ptr_key->PushKey(keyBind.move_left) || ptr_key->PushKey(keyBind.move_right) || ptr_key->PushKey(keyBind.move_up) || ptr_key->PushKey(keyBind.move_down);
        isMove = (std::max)(ptr_pad->GetLStick().x != 0 || ptr_pad->GetLStick().y != 0, isMove);
        if (isMove) { return; }

        // 何も入力が無ければIDLE
        bool noInput = !isJump && !isMove && !isAttack;
        if (noInput)
        {
            strBehavior += "PB_IDLE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_IDLE);
        }
    }

    // ATTACK
    else if (behavior == PB_ATTACK)
    {
        strBehavior = "PB_ATTACK/";

        // 攻撃アニメーション終了まで待機するならここにif文(!is_endAnimetion) {return;}
        auto max = ptr_playerCommonInfomation_->get()->kTime_AttackAnimation_max;
        auto cur = ptr_playerCommonInfomation_->get()->timer_attackAnimation;
        if (cur < max) { return; }

        bool isJump{};
        isJump = ptr_key->TriggerKey(keyBind.jump) && canJump && isGround;
        isJump = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.jump) && canJump && isGround, isJump);
        if (isJump)
        {
            strBehavior += "PB_JUMP";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_JUMP);
            return;
        }

        bool isMove{};
        isMove = ptr_key->PushKey(keyBind.move_left) || ptr_key->PushKey(keyBind.move_right) || ptr_key->PushKey(keyBind.move_up) || ptr_key->PushKey(keyBind.move_down);
        isMove = (std::max)(ptr_pad->GetLStick().x != 0 || ptr_pad->GetLStick().y != 0, isMove);
        if (isMove)
        {
            strBehavior += "PB_MOVE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_MOVE);
            return;
        }

        // 何も入力が無ければIDLE
        bool noInput = !isJump && !isMove;
        if (noInput)
        {
            strBehavior += "PB_IDLE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_IDLE);
        }
    }

    // SPECIAL
    else if (behavior == PB_SPECIAL)
    {
        strBehavior = "PB_SPECIAL/";

        // 攻撃アニメーション終了まで待機するならここにif文(!is_endAnimetion) {return;}
        auto max = ptr_playerCommonInfomation_->get()->kTime_SpecialAnimation_max;
        auto cur = ptr_playerCommonInfomation_->get()->timer_specialAnimation;
        if (cur < max) { return; }

        bool isJump{};
        isJump = ptr_key->TriggerKey(keyBind.jump) && canJump && isGround;
        isJump = (std::max)(ptr_pad->GetTriggerButton((BUTTON)controllerBind.jump) && canJump && isGround, isJump);
        if (isJump)
        {
            strBehavior += "PB_JUMP";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_JUMP);
            return;
        }

        bool isMove{};
        isMove = ptr_key->PushKey(keyBind.move_left) || ptr_key->PushKey(keyBind.move_right) || ptr_key->PushKey(keyBind.move_up) || ptr_key->PushKey(keyBind.move_down);
        isMove = (std::max)(ptr_pad->GetLStick().x != 0 || ptr_pad->GetLStick().y != 0, isMove);
        if (isMove)
        {
            strBehavior += "PB_MOVE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_MOVE);
            return;
        }

        // 何も入力が無ければIDLE
        bool noInput = !isJump && !isMove;
        if (noInput)
        {
            strBehavior += "PB_IDLE";
            behaviorLog_.push_back(strBehavior);
            Set_Behavior(PB_IDLE);
        }
    }
}
