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

}

void ParticleManager2D::Update()
{
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