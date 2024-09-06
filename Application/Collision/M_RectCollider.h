#pragma once
#include "ColliderShape.h"
#include "ICollider.h"
#include "M_ColliderManager.h"

struct M_RectCollider final : public ICollider
{
public:
    //>> コンストラクタ
    M_RectCollider(void);
    M_RectCollider(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr);
    ~M_RectCollider(void) override = default;

    void Initialize(const std::string& arg_name, const std::function<void(void)>& arg_callback, M_ColliderManager* arg_colMPtr) override;

    //>> 変数
    Square square_;
};

