#include "IPlayerBehavior.h"

IPlayerBehavior::IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation)
{
    commonInfomation_ = arg_commonInfomation;
}
