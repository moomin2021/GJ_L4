#pragma once
#include "ColliderShape.h"
#include <utility>

namespace CollisionChecker
{
    // 2�����̉�]�^���B��]�̒��S,���݈ʒu,��]�p�x
    Vector2 Rotate2d(const Vector2& arg_center, const Vector2& arg_pos, float arg_radian);
    Vector2 RotateVec2(const Vector2& arg_vec2, float arg_radian);

    //-OBB--------------------------------------------------
    // ��]�����`���m�̓����蔻��
    bool Check_OBB2OBB(const Square& arg_sq1, const Square& arg_sq2);
    bool Check_OBB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    bool Check_OBB2Circle(const Square& arg_sq, const Circle& arg_c);

    //-AABB-------------------------------------------------
    // ��`���m�̓����蔻��i��]�͍l������Ȃ��j
    bool Check_AABB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    // ��`�Ɖ~�̓����蔻��
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
    // ��`���m�̉����߂��i��]�͍l������Ȃ��j
    Vector2 PushBack_AABB2AABB(const Square& arg_sq1, const Square& arg_sq2);
    // ��`�Ɖ~�̉����߂�
    Vector2 PushBack_AABB2Circle(const Square& arg_sq, const Circle& arg_c);
}

