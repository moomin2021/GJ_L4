#include "M_CircleCollider.h"

M_CircleCollider::M_CircleCollider(void)
{
    shape_ = SHAPE_CIRCLE;
}

M_CircleCollider::M_CircleCollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    shape_ = SHAPE_CIRCLE;
    ICollider::Initialize(arg_name, arg_callback, arg_colMPtr);
}

void M_CircleCollider::Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    ICollider::Initialize(arg_name, arg_callback, arg_colMPtr);
}
