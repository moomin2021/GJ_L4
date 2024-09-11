#include "ICollider.h"
#include <cassert>
#include "M_ColliderManager.h"

ICollider::ICollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    Initialize(arg_name, arg_callback, arg_colMPtr);
}

void ICollider::Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr)
{
    // �����o�ւ̑��
    name_ = arg_name;
    callback_ = arg_callback;
    colMPtr_ = arg_colMPtr;
    assert(colMPtr_);
    colMPtr_->Register(this);

    // �R���C�_�[��L���ɂ���
    is_active_ = true;
}

void ICollider::Finalize(void)
{
    assert(colMPtr_);

    colMPtr_->UnRegister(this);
}

bool ICollider::IsSameCollider(size_t arg_id, std::list<ICollider*> arg_list)
{
    // ID�őS����
    for (const ICollider* const col : arg_list)
    {
        // ���O����v���Ă����true
        if (col->id_ == arg_id) { return true; }
    }

    return false;
}

bool ICollider::IsSameCollider(const std::string& arg_name, std::list<ICollider*> arg_list)
{
    // ���O�őS����
    for (const ICollider* const col : arg_list)
    {
        // ���O����v���Ă����true
        if (col->name_ == arg_name) { return true; }
    }

    return false;
}

std::list<ICollider*>::iterator ICollider::GetCollider(const std::string& arg_name, std::list<ICollider*>& arg_list)
{
    // ID�őS����
    for (auto it = arg_list.begin(); it != arg_list.end(); it++)
    {
        // ���O����v���Ă����true
        if ((*it)->name_ == arg_name) { return it; }
    }

    return arg_list.end();
}

void ICollider::Execute_UpdateColFlags(void)
{
    // 1�t���[���O�̌��ʂ�ۑ�
    collidersPre_ = colliders_; // �z��: �R���C�_�[ptr��list
    is_colPre_ = is_col_;       // �t���O: �Փ˔����bool

    // ���݃t���[���̌��ʗp�ɏ�����
    is_col_ = false;
    colliders_.clear();
}

void ICollider::Execute_Callback(void)
{
    // nullptr�Ȃ���s���Ȃ�
    if (!callback_) { return; }

    // ���s
    callback_();
}
