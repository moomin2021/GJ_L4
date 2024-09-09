#include "ParticleManager2D.h"
#include "PipelineManager.h"
#include "Util.h"
#include "Texture.h"

ParticleManager2D* ParticleManager2D::GetInstance()
{
	static ParticleManager2D instance;
	return &instance;
}

void ParticleManager2D::Initialize()
{
	e_ = std::make_unique<ParticleEmitter2D>();
	e_->Initialize();
	e_->SetPosition({ 500.0f, 500.0f });
	AddParticleEmitter(e_.get());
}

void ParticleManager2D::Update()
{
	Vector2 pos = { Util::GetRandomFloat(-100.0f, 100.0f), Util::GetRandomFloat(-100.0f, 100.0f) };
	e_->AddParticle(pos, 2.0f, 50.0f, 0.0f);
	for (auto& it : emitter_) it->Update();
	for (auto& it : emitter_) it->ImGuiUpdate();
}

void ParticleManager2D::MatUpdate()
{
	for (auto& it : emitter_) it->MatUpdate();
}

void ParticleManager2D::DrawBack()
{
	PipelineManager::PreDraw("Particle2D", D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
}

void ParticleManager2D::DrawFront()
{
	PipelineManager::PreDraw("Particle2D", D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	for (auto& it : emitter_) it->Draw();
}