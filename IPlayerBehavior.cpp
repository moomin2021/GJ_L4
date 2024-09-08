#include "IPlayerBehavior.h"

IPlayerBehavior::IPlayerBehavior(const std::shared_ptr<PlayerCommonInfomation>& arg_commonInfomation)
{
    commonInfomation_ = arg_commonInfomation;
}

Vector2 IPlayerBehavior::Gravity(void)
{
    return Vector2(0, commonInfomation_->gravity.current_);
}
