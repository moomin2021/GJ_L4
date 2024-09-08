#include "FloatingEnemy.h"
#include "Key.h"

using namespace EnemyStatus;

void FloatingEnemy::Initialize(size_t id, const Vector2& inPos, uint16_t tex, M_ColliderManager* colMgrPtr)
{
	// 座標の設定
	position_ = inPos;
	// テクスチャの設定
	texture_ = tex;
	// IDの設定
	id_ = id;

	// スプライトの生成、設定
	sprite_ = std::make_unique<Sprite>();
	sprite_->SetPosition(position_);
	sprite_->SetSize(size_);
	sprite_->SetAnchorPoint({ 0.5f, 0.5f });

	// コライダーの設定
	collider_.circle_.center = position_;
	collider_.circle_.radius = 32.0f;
	std::string name = "FloatingEnemy_" + std::to_string(id);
	auto callback = std::bind(&FloatingEnemy::CollisionCallBack, this);
	collider_.Initialize(name, callback, colMgrPtr);
}

void FloatingEnemy::Update()
{
	collider_.circle_.center = position_;

	// 状態別更新処理
	(this->*stateTable[(size_t)state_])();

	// 座標の更新
	position_ += moveVec_ * moveSpd_;
	rotation_ += rotaSpd_;

	// スプライトの更新
	sprite_->SetPosition(position_);
	sprite_->SetRotation(rotation_);
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
	imGuiMgrPtr->Text("ID = %d, 座標 = { %f, %f }", id_, position_.x, position_.y);
}

void FloatingEnemy::CollisionCallBack()
{
	// あたった瞬間
	//if (collider_.IsTrigger_Col()) {
	//	if (state_ == State::FirstBeaten) {
	//		state_ = State::KnockBack;
	//		moveVec_ = knockVec_;
	//		moveSpd_ = knockFirstSpd_;
	//		rotaSpd_ = knockFirstRotaSpd_;
	//	}
	//}

	if (collider_.IsDetect_Name("Boss")) {
		if (state_ == State::FirstBeaten) {
			state_ = State::KnockBack;
			moveVec_ = knockVec_;
			moveSpd_ = knockFirstSpd_;
			rotaSpd_ = knockFirstRotaSpd_;
		}
	}
}

void (FloatingEnemy::* FloatingEnemy::stateTable[]) () = {
	&FloatingEnemy::Normal,
	&FloatingEnemy::FirstBeaten,
	&FloatingEnemy::KnockBack,
	&FloatingEnemy::SecondBeaten,
};

void FloatingEnemy::Normal()
{
	if (Key::GetInstance()->TriggerKey(DIK_SPACE)) {
		state_ = State::FirstBeaten;
		moveVec_ = firstBeatenVec_;
		moveSpd_ = firstBeatenMoveSpd_;
		rotaSpd_ = firstBeatenRotaSpd_;
	}
}

void FloatingEnemy::FirstBeaten()
{
	if (Key::GetInstance()->TriggerKey(DIK_SPACE)) {
		state_ = State::KnockBack;
		moveVec_ = knockVec_;
		moveSpd_ = knockFirstSpd_;
		rotaSpd_ = knockFirstRotaSpd_;
	}
}

void FloatingEnemy::KnockBack()
{
	moveSpd_ -= knockAddSpd_;
	rotaSpd_ -= knockAddRotaSpd_;
}

void FloatingEnemy::SecondBeaten()
{
}
