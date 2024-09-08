#pragma once
#include <memory>
#include "PlayerBehaviorMachine.h"
#include "PlayerCommonInfomation.h"
#include "Sprite.h"
#include "M_ColliderManager.h"
#include <vector>

class Player
{
public:
    Player(void) = default;
    ~Player(void);

    void Initialize(M_ColliderManager* arg_colliderManagerPtr);
    void Update(void);
    void MatUpdate(void);
    void Draw(void);

private:
    void DrawImGUi(void);
    void Callback(void);

    std::unique_ptr<Sprite> sprite0_ = nullptr;
    PlayerBehaviorMachine behaviorMachine_;
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

