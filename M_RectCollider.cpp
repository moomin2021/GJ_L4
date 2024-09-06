#include "M_RectCollider.h"

M_RectCollider::M_RectCollider(void)
{
    shape_ = SHAPE_RECT;
}

M_RectCollider::M_RectCollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    shape_ = SHAPE_RECT;
    ICollider::Initialize(arg_name, arg_callback, arg_colMPtr);
}

void M_RectCollider::Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    ICollider::Initialize(arg_name, arg_callback, arg_colMPtr);
}
