#pragma once
#include "ColliderShape.h"
#include "ICollider.h"
#include "M_ColliderManager.h"

struct M_CircleCollider final : public ICollider
{
public:
    //>> �R���X�g���N�^
    M_CircleCollider(void);
    M_CircleCollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr);
    ~M_CircleCollider(void) override = default;

    void Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr) override;

    //>> �ϐ�
    Circle circle_;
};

