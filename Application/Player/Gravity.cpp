#include "Gravity.h"
#include <algorithm>

void Gravity::Initialize(float arg_max, float arg_add, float arg_current)
{
    max_ = arg_max;
    add_ = arg_add;
    current_ = arg_current;
}

void Gravity::Update(void)
{
    current_ += add_;
    current_ = std::min(current_, max_);
}
