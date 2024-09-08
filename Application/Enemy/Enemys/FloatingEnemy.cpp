#include "FloatingEnemy.h"

void FloatingEnemy::Initialize(const Vector2& inPos)
{
	// 座標の設定
	position_ = inPos;

	// スプライトの生成、設定
	sprite_ = std::make_unique<Sprite>();
	sprite_->SetPosition(position_);
	sprite_->SetSize(size_);
	sprite_->SetAnchorPoint({ 0.5f, 0.5f });
}

void FloatingEnemy::Update()
{
}

void FloatingEnemy::MatUpdate()
{
	sprite_->MatUpdate();
}

void FloatingEnemy::Draw()
{
	sprite_->Draw(texture_);
}

void FloatingEnemy::Finalize()
{
}

void FloatingEnemy::ImGuiUpdate(ImGuiManager* imGuiMgrPtr)
{
	// 座標の表示
	imGuiMgrPtr->Text("座標 = { %f, %f }", position_.x, position_.y);
}