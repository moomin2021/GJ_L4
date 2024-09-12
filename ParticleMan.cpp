#include "ParticleMan.h"
#include "TimeManager.h"

void Particle2D::Initialize(void)
{
    isAlive = true;
    isDraw = true;

    sprite = std::make_unique<Sprite>();
}

void Particle2D::Initialize(const Vector2& arg_anchorPoint, const Vector2& arg_size, const Vector2& arg_position, const float4& arg_color, const Vector2& arg_scale, float arg_rotate, float arg_timeToDead)
{
    // flags
    isAlive = true;
    isDraw = true;

    // sprite settings
    sprite = std::make_unique<Sprite>();
    sprite->SetAnchorPoint(arg_anchorPoint);
    sprite->SetPosition(arg_anchorPoint);
    sprite->SetColor(arg_color);
    sprite->SetRotation(arg_rotate);

    Vector2 s = { arg_size.x * arg_scale.x, arg_size.y * arg_scale.y };
    sprite->SetSize(s);

    // time
    time_toDead = arg_timeToDead;

    // size
    size = s;

    // pos
    position_start = arg_position;
    position_current = arg_position;

    // color
    color_start = arg_color;
    color_current = arg_color;

    // scale
    scale_start = arg_scale;
    scale_current = arg_scale;

    // rot
    rotate_start = arg_rotate;
    rotate_current = arg_rotate;
}

void Particle2D::Update(void)
{
    if (isAlive == false) { return; }

    // 時間加算
    time_toCurrent += TimeManager::GetInstance()->GetGameDeltaTime();
    // 死亡時刻を上回っていたら、生存フラグOFF
    if (time_toCurrent >= time_toDead) { isAlive = false; }
}

void Particle2D::MatUpdate(void)
{
    if (isAlive == false) { return; }

    sprite->MatUpdate();
}

void Particle2D::Draw(void)
{
    if (isDraw == false) { return; }

    // 描画
    sprite->Draw(textureHandle_);
}

ParticleMan* ParticleMan::GetInstance(void)
{
    static ParticleMan ins;
    return &ins;
}

void ParticleMan::Update(void)
{
    for (auto it = particles_.begin(); it != particles_.end();)
    {
        // 生存フラグfalse
        if ((*it)->isAlive == false)
        {
            // インスタンス初期化
            it->reset();
            // 配列から削除
            it = particles_.erase(it);
            // 次のitへ
            continue;
        }

        // 更新処理
        (*it)->Update();
        // it加算
        it++;
        // 次のitへ
        continue;
    }
}

void ParticleMan::Draw(void)
{
    for (auto it = particles_.begin(); it != particles_.end(); it++) { (*it)->Draw(); }
}
