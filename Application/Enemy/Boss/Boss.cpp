#include "Boss.h"
#include "WinAPI.h"
#include "Texture.h"
#include "ImGuiManager.h"

Boss::Boss() : bossColCenter_(4), bossColLength_(4), bossCol_(4) {}

void Boss::Initialize(M_ColliderManager* colMgrPtr)
{
	// 当たり判定管理クラスのポインタを受け取る
	pColMgr_ = colMgrPtr;

	// テクスチャ読み込み
	bossT_ = LoadTexture("wallKariOnly.png");
	debugT_ = LoadTexture("white.png");

	// 座標とサイズ設定
	WinAPI* winApi = WinAPI::GetInstance();
	Vector2 winSize = { (float)winApi->GetWidth(), (float)winApi->GetHeight() };

	// --ボス関連-- //
	// HPの設定
	nowHP_ = maxHP_;
	// 中心座標の設定
	bossPos_ = { winSize.x / 2.0f, winSize.y / 2.0f };
	// サイズの設定
	bossSize_ = winSize;
	// ボスのスプライトの生成、設定
	bossS_ = std::make_unique<Sprite>();
	bossS_->SetPosition(bossPos_);
	bossS_->SetSize(bossSize_);
	bossS_->SetAnchorPoint({ 0.5f, 0.5f });

	// --当たり判定関連-- //
	// 各コライダーの中心座標の設定
	bossColCenter_[0] = { winSize.x / 2.0f, 70.0f };
	bossColCenter_[1] = { winSize.x - 45.0f, winSize.y / 2.0f };
	bossColCenter_[2] = { winSize.x / 2.0f, winSize.y - 70.0f };
	bossColCenter_[3] = { 45.0f, winSize.y / 2.0f };
	// 各コライダーのサイズの設定
	bossColLength_[0] = { winSize.x, 140.0f };
	bossColLength_[1] = { 90.0f, winSize.y };
	bossColLength_[2] = { winSize.x, 140.0f };
	bossColLength_[3] = { 90.0f, winSize.y };
	// 各コライダーの設定
	for (size_t i = 0; i < 4; i++) {
		bossCol_[i].Initialize(colMgrPtr, bossColCenter_[i], bossColLength_[i], i);
	}
}

void Boss::Update()
{
	for (auto& it : bossCol_) it.Update();
}

void Boss::MatUpdate()
{
	bossS_->MatUpdate();
	for (auto& it : bossCol_) it.MatUpdate();
}

void Boss::Draw()
{
	bossS_->Draw(bossT_);

	// デバック
	for (auto& it : bossCol_) it.Draw(isDisplayCol_);
}

void Boss::Finalize()
{
}

void Boss::ImGuiUpdate(ImGuiManager* pImGuiMgr)
{
	// 当たり判定を表示するか
	pImGuiMgr->CheckBox("当たり判定表示", isDisplayCol_);
}

void Boss::CollisionCallBack()
{

}