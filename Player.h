#pragma once
#include <memory>
#include "PlayerBehaviorMachine.h"
#include "PlayerCommonInfomation.h"

class Player
{
public:
    Player(void) = default;
    ~Player(void) = default;

    void Initialize(void);
    void Update(void);
    void Draw(void);

    PlayerBehaviorMachine behaviorMachine_;
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;
};

