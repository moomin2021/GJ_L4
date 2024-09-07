#pragma once
#include "IPlayerBehavior.h"
#include "PlayerBehaviorFactory.h"

class PlayerBehaviorMachine
{
public:
    //>> 関数
    PlayerBehaviorMachine(void) = default;
    PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    ~PlayerBehaviorMachine(void) = default;

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr);
    void Update(void);

private:
    // 状態遷移条件を満たしているか確認し、遷移する
    void NextStateCheck(void);

    //>> 変数
    PlayerBehavior behavior_current_;
    PlayerBehavior behavior_next_;
    std::unique_ptr<IPlayerBehavior> statePtr_;
    PlayerBehaviorFactory behaviorFactory_;
};

