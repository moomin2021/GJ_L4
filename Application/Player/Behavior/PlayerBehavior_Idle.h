#pragma once
#include "IPlayerBehavior.h"
class PlayerBehavior_Idle : public IPlayerBehavior
{
public:
    PlayerBehavior_Idle(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation) : IPlayerBehavior(arg_commonInfomation) {}
    ~PlayerBehavior_Idle(void) override = default;

    // 状態遷移時の初期化処理
    virtual void Entry(void) override;
    // 当該状態時の様子
    virtual void Execute(void) override;
    // 状態遷移遷移前の終了処理
    virtual void Exit(void) override;
};

