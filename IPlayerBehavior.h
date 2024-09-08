#pragma once
#include "PlayerCommonInfomation.h"
#include <memory>

enum PlayerBehavior
{
    PB_DEFAULT = -1,

    PB_IDLE,
    PB_WALK,
    PB_JUMP,
};

class IPlayerBehavior
{
public:
    IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation) : commonInfomation_(arg_commonInfomation) {}
    virtual ~IPlayerBehavior(void) = default;

    // ��ԑJ�ڎ��̏���������
    virtual void Entry(void) = 0;
    // ���Y��Ԏ��̗l�q
    virtual void Execute(void) = 0;
    // ��ԑJ�ڑJ�ڑO�̏I������
    virtual void Exit(void) = 0;

private:
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

