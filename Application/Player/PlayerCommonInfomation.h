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

    // special
    uint8_t special;
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
    void Input(void);
    void Output(void);

    //-Const-------------------------
    // Player
    float kHealth_max = 100;
    float kSp_max = 10;
    
    // Move
    float kMoveSpeed = 100.f;

    // Gravity
    float kGravity_max = 20.0f;
    float kGravity_add = 0.8f;

    // Jump
    float kJumpPower = -20.f;

    // Sprite
    Vector2 kSprite_AnchorPoint_player_idle = { 0.6f,0.63f };
    Vector2 kSprite_AnchorPoint_player_move = { 0.6f,0.63f };
    Vector2 kSprite_AnchorPoint_player_attack = { 0.6f,0.63f };
    Vector2 kSprite_AnchorPoint_player_special = { 0.6f,0.63f };
    Vector2 kSprite_Length_player = { 130,75 };

    int32_t kNum_IdleSprite_max = 4;
    int32_t kNum_MoveSprite_max = 8; 
    int32_t kNum_AttackSprite_max = 5; 
    int32_t kNum_SpecialSprite_max = 5;

    // Collider
    Vector2 kCollision_Length_playerCollider = { 60,55 };
    Vector2 kCollision_Length_playerCollider_attack = { 100,100 };
    Vector2 kCollision_positionOffset_playerCollider_attack = { -70 , 0 };
    Vector2 kCollision_Length_playerCollider_special = { 100,100 };
    Vector2 kCollision_positionOffset_playerCollider_special = { -70 , 0 };

    // Time
    float kTime_IdleInterval_max = 1.2f;        // sec
    float kTime_IdleAnimation_max = 0.4f;       // sec
    float kTime_MoveInterval_max = 0.f;         // sec
    float kTime_MoveAnimation_max = 1.f;       // sec
    float kTime_AttackInterval_max = 20.f;      
    float kTime_AttackAnimation_max = 0.2f;     
    float kTime_SpecialInterval_max = 20.f;
    float kTime_SpecialAnimation_max = 0.2f;
    float kTime_Invincible_max = 20.f;          // sec
    float kTime_Easing_hp_content_shadow_max = 2.2f;

    //-Variable-----------------------------
    // Player
    float health_current{};
    float health_rate_{};
    float sp_current{};
    float sp_rate_{};
    float attackPower{};
    float specialPower{};
    Vector2 position{};
    Gravity gravity{};
    Move move{};

    // Time
    //*IDLE
    int32_t num_idleSprite{};
    float timer_idleInterval{};
    float timer_idleAnimation{}; // sec
    //*MOVE
    int32_t num_moveSprite{};
    float timer_moveInterval{};
    float timer_moveAnimation{}; // sec
    //*ATTACK
    int32_t num_attackSprite{};
    float timer_attackInterval{};
    float timer_attackAnimation{}; // sec
    //*SPECIAL
    int32_t num_specialSprite{};
    float timer_specialInterval{};
    float timer_specialAnimation{}; // sec
    float timer_invincible{};
    // Player
    float timer_easing_hp_content_shadow{};

    // Collider
    M_ColliderManager* ptr_colliderManager{};
    M_RectCollider collider{};

    // sprite
    std::vector<uint16_t> png_playerIdle{};
    std::vector<uint16_t> png_playerMove{};
    std::vector<uint16_t> png_playerAttack{};
    std::vector<uint16_t> png_playerSpecial{};
    std::unique_ptr<Sprite> sprite_player = nullptr;
    std::unique_ptr<Sprite> sprite_player_hpFrame = nullptr;
    std::unique_ptr<Sprite> sprite_player_hpContent = nullptr;
    std::unique_ptr<Sprite> sprite_player_hpContent_shadow = nullptr;
    std::unique_ptr<Sprite> sprite_player_spFrame = nullptr;
    std::unique_ptr<Sprite> sprite_player_spContent = nullptr;

    bool is_drawCollider{};
    std::unique_ptr<Sprite> sprite_collider = nullptr;
    std::unique_ptr<Sprite> sprite_attackCollider = nullptr;
    std::unique_ptr<Sprite> sprite_specialCollider = nullptr;

    Keyboard_Bind keyBind;
    Controller_Bind controllerBind;

    void Update(void);
};

