#pragma once
#include <memory>
#include "PlayerBehaviorMachine.h"
#include "PlayerCommonInfomation.h"
#include "Sprite.h"
#include "M_ColliderManager.h"
#include <vector>
#include <array>

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
    void Damage(float arg_damage);
    void Callback(void);

    ;
    PlayerBehaviorMachine behaviorMachine_;
    std::shared_ptr<PlayerCommonInfomation> commonInfomation_;

    int32_t png_player_{};
    int32_t png_HPBar_frame_{};
    int32_t png_HPBar_content_{};
    int32_t png_HPBar_content_shadow_{};
    bool is_easingShadow_{};
    float ease_shadow_start_{};

    float kTime_lightUpButton_max_ = 0.4f;
    std::array<float,3> timer_lightUpButtons_{};
    int32_t png_operationSheet_{};
    std::vector<uint16_t> png_operationSheet_divide_{};
    std::unique_ptr<Sprite> sprite_operationSheet_{};
    std::array<std::unique_ptr<Sprite>, 3> sprite_operationSheet_divides_{};
    std::array<bool,3> operationButtons_{};

    int32_t png_SPBar_frame_{};
    int32_t png_SPBar_content_{};

    int32_t png_white_debug{};
    int32_t png_frame_debug{};

public:
    PlayerCommonInfomation* Get_CommonInfomation(void) { return commonInfomation_.get(); }
};

