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
    virtual void Update(void);
    virtual void MatUpdate(void);
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

    uint16_t textureHandle_{};
    std::unique_ptr<Sprite> sprite;
};

class ParticleMan
{
public:
    static ParticleMan* GetInstance(void);

    void Update(void);
    void MatUpdate(void);
    void Draw(void);
    void AddParticle(std::unique_ptr<Particle2D> arg_particle, const Vector2& arg_pos_start = {}, const Vector2& arg_pos_end = {});

    std::list<std::unique_ptr<Particle2D>> particles_;

private:
    ParticleMan() {}
    ~ParticleMan() {}
    ParticleMan(const ParticleMan&) = delete;
    ParticleMan& operator = (const ParticleMan&) = delete;
};

