#pragma once
#include <memory>
#include <list>
#include "Vector2.h"
#include "float4.h"
#include "Sprite.h"

struct Particle2D
{
    Particle2D(void) = default;
    virtual ~Particle2D(void) = default;

    virtual void Initialize(void);
    virtual void Initialize(const Vector2& arg_anchorPoint, const Vector2& arg_size, const Vector2& arg_position, const float4& arg_color, const Vector2& arg_scale, float arg_rotate, float arg_timeToDead);
    virtual void Update(void);
    virtual void Draw(void);

    bool isAlive{};
    bool isDraw{};

    Vector2 position_current{}; //座標 - 現在
    Vector2 position_start{};   //座標 - 最初
    Vector2 position_end{};     //座標 - 最後

    float time_toCurrent{}; // 生成->現在までの時間
    float time_toDead{};    // 生成->死ぬまでの時間（余命）

    Vector2 size{};   // サイズ

    Vector2 scale_current{};  // スケール - 現在
    Vector2 scale_start{};    // スケール - 最初
    Vector2 scale_end{};      // スケール - 最後

    float rotate_current{}; // 回転 - 現在
    float rotate_start{};   // 回転 - 最初
    float rotate_end{};     // 回転 - 最後

    float4 color_current{}; // カラー - 現在
    float4 color_start{};   // カラー - 最初
    float4 color_end{};     // カラー - 最後

    uint16_t textureHandle_;
    std::unique_ptr<Sprite> sprite;
};

class ParticleMan
{
public:
    ParticleMan(void) = default;
    ~ParticleMan(void) = default;

    void Update(void);
    void Draw(void);
    void AddParticle(std::unique_ptr<Particle2D> arg_particle) { particles_.push_back(std::move(arg_particle)); }

    std::list<std::unique_ptr<Particle2D>> particles_;
};

