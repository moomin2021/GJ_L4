#include "Player.h"
#include "Texture.h"
#include "CollisionChecker.h"
#include "ImGuiManager.h"
#include "Key.h"

Player::~Player(void)
{
    commonInfomation_->collider.Finalize();
}

void Player::Initialize(M_ColliderManager* arg_colliderManagerPtr)
{
    // スマートポインタの生成
    commonInfomation_ = std::make_shared<PlayerCommonInfomation>();
    commonInfomation_->position = { 300,540 };

    // 初期設定
    behaviorMachine_.Initialize(&commonInfomation_);

    // スプライト
    sprite0_ = std::make_unique<Sprite>();
    sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    // 重力
    commonInfomation_->gravity.Initialize(commonInfomation_->kGravity_max, commonInfomation_->kGravity_add);

    //** コライダー
    // メンバ変数の設定
    commonInfomation_->collider.square_.center = commonInfomation_->position;
    commonInfomation_->collider.square_.length = commonInfomation_->kLength;
    // ローカル変数
    std::string name = "Player";
    auto callback = std::bind(&Player::CallBack, this);
    // 初期化関数
    commonInfomation_->collider.Initialize(name, callback, arg_colliderManagerPtr);
}

void Player::Update(void)
{
    behaviorMachine_.Update();
    sprite0_->SetPosition(commonInfomation_->position);

    commonInfomation_->Update();
    commonInfomation_->position += behaviorMachine_.Get_PlayerBehaviorPtr()->Gravity();

    auto& myCol = commonInfomation_->collider;
    auto imgui = ImGuiManager::GetInstance();
    imgui->BeginWindow("player");
    imgui->Text("player_pos : [%f][%f]", myCol.square_.center.x, myCol.square_.center.y);
    imgui->Text("player_size: [%f][%f]", myCol.square_.length.x, myCol.square_.length.y);
    imgui->Text("player_minX: [%f][%f]", myCol.square_.center.x - myCol.square_.length.x / 2, myCol.square_.center.y);
    imgui->EndWindow();

}

void Player::MatUpdate(void)
{
    sprite0_->MatUpdate();
}

void Player::Draw(void)
{
    auto texture = LoadTexture("hae.png");
    sprite0_->Draw(texture);
}

void Player::CallBack(void)
{
    auto& myCol = commonInfomation_->collider;
    auto imgui = ImGuiManager::GetInstance();
    imgui->BeginWindow("player");
    Vector2 pushbackv{};

    if (myCol.IsDetect_Name("BossRect0"))
    {
        auto* const contacted = myCol.Extract_Collider("BossRect0");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        pushbackv = pushBack;
    }
    if (myCol.IsDetect_Name("BossRect1"))
    {
        auto* const contacted = myCol.Extract_Collider("BossRect1");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        //if (Key::GetInstance()->TriggerKey(DIK_SPACE))
        //{
        //    int a = 0;
        //    a;
        //}

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        pushbackv = pushBack;
    }
    if (myCol.IsDetect_Name("BossRect2"))
    {
        auto* const contacted = myCol.Extract_Collider("BossRect2");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        pushbackv = pushBack;
    }
    if (myCol.IsDetect_Name("BossRect3"))
    {
        auto* const contacted = myCol.Extract_Collider("BossRect3");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        pushbackv = pushBack;

        imgui->Text("rect_pos : [%f][%f]", rect->square_.center.x, rect->square_.center.y);
        imgui->Text("rect_size: [%f][%f]", rect->square_.length.x, rect->square_.length.y);
        imgui->Text("rect_maxX: [%f][%f]", rect->square_.center.x + rect->square_.length.x / 2, rect->square_.center.y);
        imgui->Text("fill: [%f][%f]", rect->square_.center.x + rect->square_.length.x / 2 - myCol.square_.center.x - myCol.square_.length.x / 2, myCol.square_.center.y);
    }
    imgui->Text("pushback : [%f][%f]", pushbackv.x, pushbackv.y);
    imgui->EndWindow();
}
