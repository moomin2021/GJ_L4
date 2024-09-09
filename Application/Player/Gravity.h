#pragma once

struct Gravity
{
public:
    Gravity(void) = default;
    ~Gravity(void) = default;

    void Initialize(float arg_max, float arg_add, float arg_current = 0.f);
    void Update(void);

    float max_;
    float add_;
    float current_;

    void Set_Current(float arg_currentGravity) { current_ = arg_currentGravity; }
};

