#include "Boss.h"
#include "WinAPI.h"
#include "Texture.h"
#include "ImGuiManager.h"

Boss::Boss() : bossColCenter_(4), bossColLength_(4), bossCol_(4), bossColS_(4) {}

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
	bossColCenter_[1] = { winSize.x - 140.0f, winSize.y / 2.0f };
	bossColCenter_[2] = { winSize.x / 2.0f, winSize.y - 160.0f };
	bossColCenter_[3] = { 40.0f, winSize.y / 2.0f };
	// 各コライダーのサイズの設定
	bossColLength_[0] = { winSize.x, 140.0f };
	bossColLength_[1] = { 80.0f, winSize.y };
	bossColLength_[2] = { winSize.x, 140.0f };
	bossColLength_[3] = { 80.0f, winSize.y };
	// 各コライダーの設定
	for (size_t i = 0; i < 4; i++) {
		bossCol_[i].square_.center = bossColCenter_[i];
		bossCol_[i].square_.length = bossColLength_[i];
		std::string name = "BossRect" + std::to_string(i);
		auto callback = std::bind(&Boss::CollisionCallBack, this);
		bossCol_[i].Initialize(name, callback, pColMgr_);
	}
	// 各コライダーのスプライト
	for (size_t i = 0; i < 4;i++) {
		bossColS_[i] = std::make_unique<Sprite>();
		bossColS_[i]->SetPosition(bossColCenter_[i]);
		bossColS_[i]->SetSize(bossColLength_[i]);
		bossColS_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		bossColS_[i]->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });
	}
}

void Boss::Update()
{

}

void Boss::MatUpdate()
{
	bossS_->MatUpdate();
	for (auto& it : bossColS_) it->MatUpdate();
}

void Boss::Draw()
{
	bossS_->Draw(bossT_);

	// デバック
	if (isDisplayCol_) {
		for (auto& it : bossColS_) it->Draw(debugT_);
	}
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