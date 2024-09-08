#pragma once
#include "IPlayerBehavior.h"
#include "PlayerBehaviorFactory.h"

class PlayerBehaviorMachine
{
public:
    //>> �֐�
    PlayerBehaviorMachine(void) = default;
    PlayerBehaviorMachine(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior = PlayerBehavior::PB_IDLE);
    ~PlayerBehaviorMachine(void) = default;

    void Initialize(std::shared_ptr<PlayerCommonInfomation>* arg_commonInfomationPtr, PlayerBehavior arg_firstBehavior = PlayerBehavior::PB_IDLE);
    void Update(void);

private:
    // 状態遷移条件を満たしているか確認し、遷移する
    void NextStateCheck(void);
    void BehaviorInput(void);

    //>> 変数
    PlayerBehavior behavior_current_;
    PlayerBehavior behavior_next_;
    std::unique_ptr<IPlayerBehavior> statePtr_;
    PlayerBehaviorFactory behaviorFactory_;

    // imgui
    std::vector<std::string> behaviorLog_{}; // 一瞬しか表示されない状態を見やすくする
public:
    void Set_Behavior(PlayerBehavior arg_nextBehavior) { behavior_next_ = arg_nextBehavior; }

    PlayerBehavior Get_Behavior(void) { return behavior_current_; }
    IPlayerBehavior* Get_PlayerBehaviorPtr(void) { return statePtr_.get(); }
    std::vector<std::string>& Get_ImGui_BehaviorLog(void) { return behaviorLog_; }
};

