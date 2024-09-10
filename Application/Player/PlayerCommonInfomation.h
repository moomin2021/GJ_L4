#pragma once
#include "Vector2.h"
#include "Gravity.h"
#include "M_RectCollider.h"
#include "Sprite.h"
#include <memory>
#include "TimeManager.h"
#include "Direction.h"

struct PlayerCommonInfomation
{
    //-Const-------------------------
    // Move
    const float kMoveSpeed = 5.f;

    // Gravity
    const float kGravity_max = 4.5f;
    const float kGravity_add = 0.1f;

    // Jump
    const float kJumpPower = -5.f;

    // Sprite
    const Vector2 kSprite_AnchorPoint_player_idle = { 0.5f,0.7f };
    const Vector2 kSprite_AnchorPoint_player_attack = { 0.6f,0.7f };
    const Vector2 kSprite_Length_player = { 130,75 };

    // Collider
    const Vector2 kCollision_Length_playerCollider = { 60,55 };
    const Vector2 kCollision_Length_playerCollider_attack = { 100,100 };
    const Vector2 kCollision_positionOffset_playerCollider_attack = { -70 , 0 };

    // Time
    const int32_t kNum_AttackSprite_max = 5;
    const float kTime_AttackAnimation_max = 1.f; // sec
    const float kTime_AttackInterval_max = 20.f; // sec
    const float kTime_Invincible_max = 20.f;     // sec

    //-Variable-----------------------------

    Direction direction{};
    Vector2 position{};
    Gravity gravity{};
    bool is_ground{};
    bool can_jump{};

    // Time
    int32_t num_attackSprite{};
    float timer_attackInterval{};
    float timer_attackAnimation{}; // sec
    float timer_invincible{};

    // Collider
    M_ColliderManager* ptr_colliderManager{};
    M_RectCollider collider{};

    // sprite
    std::vector<uint16_t> png_playerAttack{};
    std::unique_ptr<Sprite> sprite_player = nullptr;

    bool is_drawCollider{};
    std::unique_ptr<Sprite> sprite_collider = nullptr;
    std::unique_ptr<Sprite> sprite_attackCollider = nullptr;

    void Update(void);
};

