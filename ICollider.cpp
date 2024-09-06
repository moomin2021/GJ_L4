#include "ICollider.h"
#include <cassert>
#include "M_ColliderManager.h"

ICollider::ICollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    Initialize(arg_name, arg_callback, arg_colMPtr);
}

void ICollider::Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    // メンバへの代入
    name_ = arg_name;
    callback_ = arg_callback;
    colMPtr_ = arg_colMPtr;
    assert(colMPtr_);
    colMPtr_->Register(this);

    // コライダーを有効にする
    is_active_ = true;
}

void ICollider::Finalize(void)
{
    assert(colMPtr_);

    colMPtr_->UnRegister(this);
}

bool ICollider::IsSameCollider(size_t arg_id, std::list<ICollider*> arg_list)
{
    // IDで全検索
    for (const ICollider* const col : arg_list)
    {
        // 名前が一致していればtrue
        if (col->id_ == arg_id) { return true; }
    }

    return false;
}

bool ICollider::IsSameCollider(const std::string& arg_name, std::list<ICollider*> arg_list)
{
    // 名前で全検索
    for (const ICollider* const col : arg_list)
    {
        // 名前が一致していればtrue
        if (col->name_ == arg_name) { return true; }
    }

    return false;
}

std::list<ICollider*>::iterator ICollider::GetCollider(const std::string& arg_name, std::list<ICollider*> arg_list)
{
    // IDで全検索
    for (auto it = arg_list.begin(); it != arg_list.end(); it++)
    {
        // 名前が一致していればtrue
        if ((*it)->name_ == arg_name) { return it; }
    }

    return arg_list.end();
}

void ICollider::Execute_UpdateColFlags(void)
{
    // 1フレーム前の結果を保存
    collidersPre_ = colliders_; // 配列: コライダーptrのlist
    is_colPre_ = is_col_;       // フラグ: 衝突判定のbool

    // 現在フレームの結果用に初期化
    is_col_ = false;
    colliders_.clear();
}

void ICollider::Execute_Callback(void)
{
    // nullptrなら実行しない
    if (!callback_) { return; }

    // 実行
    callback_();
}
