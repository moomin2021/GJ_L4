#pragma once
#include <functional>
#include "ColliderTag.h"
#include "ColliderShape.h"
#include <any>
#include <unordered_map>

class M_ColliderManager;

class ICollider
{
public:
    //>> ��`
    friend M_ColliderManager;

    //>> �R���X�g���N�^
    ICollider(void) = default;
    ICollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr);
    virtual ~ICollider(void) = default;

    //>> �֐�
    // ���O�̐ݒ�/�R�[���o�b�N�֐��̓o�^/�R���C�_�[�}�l�[�W���[��ptr�擾
    virtual void Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr);
    virtual void Finalize(void);

    // �������Փ˂�����
    bool IsTrigger_Col(void) { return is_col_ && !is_colPre_; } // �� == true && �O == false
    bool IsDetect_Col(void) { return is_col_; }                 // �� == true
    bool IsRelease_Col(void) { return !is_col_ && is_colPre_; } // �� == false && �O == true

    // Id(size_t)�ƏՓ˂�����
    bool IsTrigger_Id(size_t arg_id) { return IsExist_Cur(arg_id) && !IsExist_Pre(arg_id); } // �� == true && �O == false
    bool IsDetect_Id(size_t arg_id) { return IsExist_Cur(arg_id); }                          // �� == true
    bool IsRelease_Id(size_t arg_id) { return !IsExist_Cur(arg_id) && IsExist_Pre(arg_id); } // �� == false && �O == true

    // "Name"�ƏՓ˂�����
    bool IsTrigger_Name(const std::string& arg_name) { return IsExist_Cur(arg_name) && !IsExist_Pre(arg_name); } // �� == true && �O == false
    bool IsDetect_Name(const std::string& arg_name) { return IsExist_Cur(arg_name); }                            // �� == true
    bool IsRelease_Name(const std::string& arg_name) { return !IsExist_Cur(arg_name) && IsExist_Pre(arg_name); } // �� == false && �O == true

    // std::vector��std::list�Ƃ������g���z��̂ݎw��
    template <template <class, class> class T>
    T<ICollider*, std::allocator<ICollider*>> Extract_Colliders(const std::string& arg_name);
    // �ڐG�������R���C�_�[��P�̂Ŏ擾�B��������ꍇ�A�擪�Ɍ��m�������̂�Ԃ��B
    ICollider* Extract_Collider(const std::string& arg_name) { return *GetCollider(arg_name, colliders_); } // ��O�X���[�̏ꍇcolliders_.end()�ł���

    // ���[�U�[�p|���C�ɓ���R���C�_�[�o�^�֐�
    void Bookmark_Add(ICollider* const arg_collierPtr) { bookmarks_.push_back(arg_collierPtr); }
    // ���[�U�[�p|���C�ɓ���R���C�_�[�����֐�
    void Bookmark_Remove(ICollider* const arg_collierPtr) { bookmarks_.remove(arg_collierPtr); }
    // ���[�U�[�p|���C�ɓ���R���C�_�[�擾�֐�
    ICollider* Bookmark_GetCollider(const std::string& arg_name) { return *GetCollider(arg_name, bookmarks_); } // ��O�X���[�̏ꍇbookmarks_.end()�ł���

    // ���[�U�[�p|�`���������o�^�֐�
    void Data_Add(const std::string& arg_key, const std::any& arg_any) { datas_.emplace(arg_key, arg_any); }
    // ���[�U�[�p|�`��������񖕏��֐�
    void Data_Remove(const std::string& arg_key) { datas_.erase(arg_key); }
    // ���[�U�[�p|�`���������S�폜�֐�
    void Data_Clear(void) { datas_.clear(); }
    // ���[�U�[�p|�`���������擾�֐�
    template<class T>
    T Data_Get(const std::string& arg_key);

private:
    // ���X�g���Ɉ�v������̂����邩�������s��
    bool IsSameCollider(size_t arg_id, std::list<ICollider*> arg_list);                                 // id
    bool IsSameCollider(const std::string& arg_name, std::list<ICollider*> arg_list);                   // ���O
    // internal
    std::list<ICollider*>::iterator GetCollider(const std::string& arg_name, std::list<ICollider*> arg_list);                   // ���O

    // �R���C�_�[���X�g���Ɉ�v������̂����邩�������s��
    bool IsExist_Cur(size_t arg_id) { return IsSameCollider(arg_id, colliders_); }                             // ��F id����
    bool IsExist_Cur(const std::string& arg_name) { return IsSameCollider(arg_name, colliders_); }             // ��F ���O����
    bool IsExist_Pre(size_t arg_id) { return IsSameCollider(arg_id, collidersPre_); }                          // �OF id����
    bool IsExist_Pre(const std::string& arg_name) { return IsSameCollider(arg_name, collidersPre_); }          // �OF ���O����

    void Record_Collider(ICollider* const arg_colPtr) { colliders_.push_back(arg_colPtr); }

    void Execute_UpdateColFlags(void);
    void Execute_Callback(void);

    //>> �ϐ�
    // �d�����p
    size_t id_{};
    // ���ʖ�
    std::string name_;
    // �L���t���O
    bool is_active_{};

    // �ڐG���m
    bool is_col_{};
    bool is_colPre_{};
    // �ڐG�R���C�_�[s
    std::list<ICollider*> colliders_;
    std::list<ICollider*> collidersPre_;
    // �R�[���o�b�N�֐�
    std::function<void(void)> callback_;
    // ���C�ɓ���o�^�R���C�_�[
    std::list<ICollider*> bookmarks_;
    // �^�O
    ColliderTag context_;
    // �`���������
    std::unordered_map<std::string, std::any> datas_;

protected:
    M_ColliderManager* colMPtr_{};
    Shape shape_{};

public:
    //>> getter
    bool Get_IsActive(void) { return is_active_; }
    Shape Get_Shape(void) { return shape_; }
    const std::list<ICollider*>& Get_Colliders(void) { return colliders_; }
    const std::string& Get_Name(void) { return name_; }
    // �^�O�ϐ��ɃA�N�Z�X���邽�ߎQ�Ɠn��
    ColliderTag& Get_Context(void) { return context_; }

    //>> setter
    void Set_IsCol(bool arg_isCol) { is_col_ = arg_isCol; }
    void Set_IsActive(bool arg_isActive) { is_active_ = arg_isActive; }

};

template <template <class, class> class T>
inline T<ICollider*, std::allocator<ICollider*>> ICollider::Extract_Colliders(const std::string& arg_name)
{
    // �e���v���[�g�R���e�i�̐���
    T<ICollider*, std::allocator<ICollider*>> container{};

    // colliders��S����
    for (const auto& collider : colliders_)
    {
        // �w�肳�ꂽ���O�ƈ�v���Ă��Ȃ��ꍇ�A���̃C���X�^���X������
        if (collider->name_ != arg_name) { continue; }
        // �w�肳�ꂽ���O�̃R���C�_�[���R���e�i�ɐς�
        container.push_back(collider);
    }

    // �ςݏI������R���e�i��Ԃ��B
    return container;
}

template<class T>
inline T ICollider::Data_Get(const std::string& arg_key)
{
    // ���L�����Ƃ��N���肤��B
    // �����ŗ�O�X���[�����������ꍇ�Akey�̒l���ԈႦ�Ă���\��������B
    // �����ŗ�O�X���[�����������ꍇ�AData_Get�֐������s���Ă���R���C�_�[���ԈႦ�Ă���\��������B
    auto& a = datas_[arg_key];
    // �����ŗ�O�X���[�����������ꍇ�A�n���^���ԈႦ�Ă���\��������B
    return std::any_cast<T>(a);
}

