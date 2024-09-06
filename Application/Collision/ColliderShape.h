#pragma once
#include "Vector2.h"

enum Shape
{
    SHAPE_INTERFACE,
    SHAPE_RECT,
    SHAPE_CIRCLE
};

struct Square
{
    Vector2 center;
    Vector2 length;
    float radian;
};

//‰~
struct Circle {
    Vector2 center;
    float radius;
};