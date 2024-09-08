#pragma once
#include <memory>
#include "PlayerBehaviorMachine.h"
#include "PlayerCommonInfomation.h"
#include "Sprite.h"

class Player
{
public:
    Player(void) = default;
    ~Player(void) = default;

    void Initialize(void);
    void Update(void);
    void MatUpdate(void);
    void Draw(void);

    std::unique_ptr<Sprite> sprite0_ = nullptr;
    PlayerBehaviorMachine behaviorMachine_;
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

