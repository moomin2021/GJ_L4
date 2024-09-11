#pragma once
#include "Vector2.h"
#include "Gravity.h"
#include "M_RectCollider.h"
#include "Sprite.h"
#include <memory>
#include "TimeManager.h"
#include "Direction.h"
#include "Move.h"

struct Keyboard_Bind
{
    // MOVE
    uint8_t move_up;
    uint8_t move_down;
    uint8_t move_left;
    uint8_t move_right;

    // JUMP
    uint8_t jump;

    // ATTACK
    uint8_t attack;
};

struct Controller_Bind
{
    // JUMP
    uint16_t jump;

    // ATTACK
    uint16_t attack;

    // special
    uint16_t special;
};

struct PlayerCommonInfomation
{
    //-Const-------------------------
    // Move
    const float kMoveSpeed = 5.f;

    // Gravity
    const float kGravity_max = 20.0f;
    const float kGravity_add = 0.8f;

    // Jump
    const float kJumpPower = -20.f;

    // Sprite
    const Vector2 kSprite_AnchorPoint_player_idle = { 0.6f,0.63f };
    const Vector2 kSprite_AnchorPoint_player_attack = { 0.6f,0.63f };
    const Vector2 kSprite_Length_player = { 130,75 };

    const int32_t kNum_IdleSprite_max = 4;
    const int32_t kNum_AttackSprite_max = 5;

    // Collider
    const Vector2 kCollision_Length_playerCollider = { 60,55 };
    const Vector2 kCollision_Length_playerCollider_attack = { 100,100 };
    const Vector2 kCollision_positionOffset_playerCollider_attack = { -70 , 0 };

    // Time
    const float kTime_IdleInterval_max = 1.2f; // sec
    const float kTime_IdleAnimation_max = 0.4f; // sec
    const float kTime_AttackInterval_max = 20.f; // sec
    const float kTime_AttackAnimation_max = 0.2f; // sec
    const float kTime_Invincible_max = 20.f;     // sec

    //-Variable-----------------------------

    Vector2 position{};
    Gravity gravity{};
    Move move{};

    // Time
    //*IDLE
    int32_t num_idleSprite{};
    float timer_idleInterval{};
    float timer_idleAnimation{}; // sec
    //*ATTACK
    int32_t num_attackSprite{};
    float timer_attackInterval{};
    float timer_attackAnimation{}; // sec
    float timer_invincible{};

    // Collider
    M_ColliderManager* ptr_colliderManager{};
    M_RectCollider collider{};

    // sprite
    std::vector<uint16_t> png_playerIdle{};
    std::vector<uint16_t> png_playerAttack{};
    std::unique_ptr<Sprite> sprite_player = nullptr;

    bool is_drawCollider{};
    std::unique_ptr<Sprite> sprite_collider = nullptr;
    std::unique_ptr<Sprite> sprite_attackCollider = nullptr;

    Keyboard_Bind keyBind;
    Controller_Bind controllerBind;

    void Update(void);
};

