#pragma once
#include "ColliderShape.h"
#include <utility>

namespace CollisionChecker
{
    // 2ŸŒ³‚Ì‰ñ“]‰^“®B‰ñ“]‚Ì’†S,Œ»İˆÊ’u,‰ñ“]Šp“x
    Vector2 Rotate2d(const Vector2& arg_center, const Vector2& arg_pos, float arg_radian);
    Vector2 RotateVec2(const Vector2& arg_vec2, float arg_radian);

    //-OBB--------------------------------------------------
    // ‰ñ“]‚·‚é‹éŒ`“¯m‚Ì“–‚½‚è”»’è
    bool Check_OBB2OBB(const Square& arg_sq1, const Square& arg_sq2);
    bool Check_OBB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    bool Check_OBB2Circle(const Square& arg_sq, const Circle& arg_c);

    //-AABB-------------------------------------------------
    // ‹éŒ`“¯m‚Ì“–‚½‚è”»’èi‰ñ“]‚Íl—¶‚³‚ê‚È‚¢j
    bool Check_AABB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    // ‹éŒ`‚Æ‰~‚Ì“–‚½‚è”»’è
    bool Check_AABB2Circle(const Square& arg_sq, const Circle& arg_c);
}

namespace CollisionResponse
{
    //-OBB--------------------------------------------------
    Vector2 ClosestPoint_OBB(const Square& arg_obb, const Vector2& arg_point);
    std::pair<Vector2, Vector2> Closest2Point_OBBs(const Square& arg_sq1, const Square& arg_sq2);
    Vector2 PushBack_OBB2OBB_SameRot(const Square& arg_sq1, const Square& arg_sq2);
    Vector2 PushBack_OBB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    Vector2 PushBack_OBB2Circle(const Square& arg_sq, const Circle& arg_c);

    //-AABB-------------------------------------------------
    // ‹éŒ`“¯m‚Ì‰Ÿ‚µ–ß‚µi‰ñ“]‚Íl—¶‚³‚ê‚È‚¢j
    Vector2 PushBack_AABB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    // ‹éŒ`‚Æ‰~‚Ì‰Ÿ‚µ–ß‚µ
    Vector2 PushBack_AABB2Circle(const Square& arg_sq, const Circle& arg_c);
}

