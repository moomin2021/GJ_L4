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

    // ó‘Ô‘JˆÚ‚Ì‰Šú‰»ˆ—
    virtual void Entry(void) = 0;
    // “–ŠYó‘Ô‚Ì—lq
    virtual void Execute(void) = 0;
    // ó‘Ô‘JˆÚ‘JˆÚ‘O‚ÌI—¹ˆ—
    virtual void Exit(void) = 0;

private:
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

