#pragma once
#include "PlayerCommonInfomation.h"
#include <memory>

enum PlayerBehavior
{
    PB_IDLE,
    PB_WALK,
    PB_JUMP,
};

class IPlayerBehavior
{
public:
    IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation) : commonInfomation_(arg_commonInfomation) {}
    virtual ~IPlayerBehavior(void) = default;

    // 状態遷移時の初期化処理
    virtual void Entry(void) = 0;
    // 当該状態時の様子
    virtual void Execute(void) = 0;
    // 状態遷移遷移前の終了処理
    virtual void Exit(void) = 0;

private:
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

