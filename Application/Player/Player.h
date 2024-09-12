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

    ;
    PlayerBehaviorMachine behaviorMachine_;
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;

    int32_t png_player_{};
    int32_t png_HPBar_frame_{};
    int32_t png_HPBar_content_{};
    int32_t png_HPBar_content_shadow_{};
    int32_t png_SPBar_frame_{};
    int32_t png_SPBar_content_{};

    int32_t png_white_debug{};
    int32_t png_frame_debug{};

public:
    PlayerCommonInfomation* Get_CommonInfomation(void) { return commonInfomation_.get(); }
};

