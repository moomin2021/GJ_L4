#include "Boss.h"
#include "WinAPI.h"
#include "Texture.h"

void Boss::Initialize()
{
	// テクスチャ読み込み
	bossT_ = LoadTexture("wallKariOnly.png");

	// 座標とサイズ設定
	WinAPI* winApi = WinAPI::GetInstance();
	bossPos_ = { winApi->GetWidth() / 2.0f, winApi->GetHeight() / 2.0f };
	bossSize_ = { (float)winApi->GetWidth(), (float)winApi->GetHeight() };

	// --スプライト-- //
	// ボスのスプライト
	bossS_ = std::make_unique<Sprite>();
	bossS_->SetPosition(bossPos_);
	bossS_->SetSize(bossSize_);
	bossS_->SetAnchorPoint({ 0.5f, 0.5f });
}

void Boss::Update()
{

}

void Boss::MatUpdate()
{
	bossS_->MatUpdate();
}

void Boss::Draw()
{
	bossS_->Draw(bossT_);
}

void Boss::Finalize()
{
}
