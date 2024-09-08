#pragma once
#include "PlayerCommonInfomation.h"
#include <memory>

enum PlayerBehavior
{
    PB_DEFAULT = -1,

    PB_IDLE,
    PB_MOVE,
    PB_JUMP,
    PB_ATTACK,
};

class IPlayerBehavior
{
public:
    IPlayerBehavior(void) = default;
    IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation);
    virtual ~IPlayerBehavior(void) = default;

    // ��ԑJ�ڎ��̏���������
    virtual void Entry(void) = 0;
    // ���Y��Ԏ��̗l�q
    virtual void Execute(void) = 0;
    // ��ԑJ�ڑJ�ڑO�̏I������
    virtual void Exit(void) = 0;

    Vector2 Gravity(void);
protected:

    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

