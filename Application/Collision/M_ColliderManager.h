#pragma once
#include "ICollider.h"

class M_ColliderManager
{
public:
    //>> コンストラクタ
    M_ColliderManager(void) : is_active_(true) {}
    ~M_ColliderManager(void) = default;

    //>> 関数
    void Update(void);

    void Register(ICollider* arg_collider);
    void UnRegister(ICollider* arg_collider) { colliders_.remove(arg_collider); }

private:
    void Collision(ICollider* arg_col1, ICollider* arg_col2);

    //--Rect_to------------------------------------------
    bool Rect2Rect(ICollider* arg_col1, ICollider* arg_col2);
    bool Rect2Circle(ICollider* arg_col1, ICollider* arg_col2);

    //>> 変数
    std::list<ICollider*> colliders_;
    std::list< std::list<ICollider*>::iterator> colliders_executeCallback_;
    size_t countId_ = 1; // ※0スタートはありえない

    bool is_active_{};

public:
    void Set_IsActive(bool arg_isActive) { is_active_ = arg_isActive; }
    bool Get_IsActive(void) { return is_active_; }
};

