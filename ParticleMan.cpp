#include "ParticleMan.h"
#include "TimeManager.h"

void Particle2D::Initialize(void)
{
    isAlive = true;
    isDraw = true;

    sprite = std::make_unique<Sprite>();
}

void Particle2D::Update(void)
{
    if (isAlive == false) { return; }

    // 死亡時刻を上回っていたら、生存フラグOFF
    if (time_toCurrent >= time_toDead) { isAlive = false; }
    // 時間加算
    time_toCurrent += TimeManager::GetInstance()->GetGameDeltaTime();
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

void ParticleMan::MatUpdate(void)
{
    for (auto it = particles_.begin(); it != particles_.end(); it++) { (*it)->MatUpdate(); }
}

void ParticleMan::Draw(void)
{
    for (auto it = particles_.begin(); it != particles_.end(); it++) 
    { 
        (*it)->Draw(); }
}

void ParticleMan::AddParticle(std::unique_ptr<Particle2D> arg_particle, const Vector2& arg_pos_start, const Vector2& arg_pos_end)
{
    bool isZero_start = arg_pos_start.x == 0 && arg_pos_start.y == 0;
    bool isZero_end = arg_pos_end.x == 0 && arg_pos_end.y == 0;

    if (!isZero_start) { arg_particle->position_start = arg_pos_start; }
    if(!isZero_end) { arg_particle->position_end = arg_pos_end; }

    arg_particle->Initialize();
    particles_.push_back(std::move(arg_particle));
}