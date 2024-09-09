#include "Player.h"
#include "Texture.h"
#include "CollisionChecker.h"
#include "ImGuiManager.h"
#include "Key.h"
#include "imgui.h"

Player::~Player(void)
{
    commonInfomation_->collider.Finalize();
}

void Player::Initialize(M_ColliderManager* arg_colliderManagerPtr)
{
    // スマートポインタの生成
    commonInfomation_ = std::make_shared<PlayerCommonInfomation>();
    commonInfomation_->position = { 300,540 };
    commonInfomation_->ptr_colliderManager = arg_colliderManagerPtr;

    // 初期設定
    behaviorMachine_.Initialize(&commonInfomation_);

    // スプライト
    png_hae_ = LoadTexture("hae.png");
    png_white_ = LoadTexture("white.png");
    png_frame_ = LoadTexture("frame.png");

    sprite0_ = std::make_unique<Sprite>();
    sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_collider = std::make_unique<Sprite>();
    commonInfomation_->sprite_collider->SetPosition(commonInfomation_->position);
    commonInfomation_->sprite_collider->SetSize(commonInfomation_->kLength_collider);
    commonInfomation_->sprite_collider->SetAnchorPoint({ 0.5f, 0.5f });
    commonInfomation_->sprite_collider->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });

    commonInfomation_->sprite_attackCollider = std::make_unique<Sprite>();
    commonInfomation_->sprite_attackCollider->SetPosition(commonInfomation_->position + commonInfomation_->kOffset_attackCollider);
    commonInfomation_->sprite_attackCollider->SetSize(commonInfomation_->kLength_attackCollider);
    commonInfomation_->sprite_attackCollider->SetAnchorPoint({ 0.5f, 0.5f });
    commonInfomation_->sprite_attackCollider->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    // 重力
    commonInfomation_->gravity.Initialize(commonInfomation_->kGravity_max, commonInfomation_->kGravity_add);

    //** コライダー
    // メンバ変数の設定
    commonInfomation_->collider.square_.center = commonInfomation_->position;
    commonInfomation_->collider.square_.length = commonInfomation_->kLength_collider;
    // ローカル変数
    std::string name = "Player";
    auto callback = std::bind(&Player::Callback, this);
    // 初期化関数
    commonInfomation_->collider.Initialize(name, callback, arg_colliderManagerPtr);
}

void Player::Update(void)
{
    behaviorMachine_.Update();
    sprite0_->SetPosition(commonInfomation_->position);
    commonInfomation_->sprite_collider->SetPosition(commonInfomation_->position);
    commonInfomation_->sprite_attackCollider->SetPosition(commonInfomation_->position + commonInfomation_->kOffset_attackCollider);

    commonInfomation_->Update();
    commonInfomation_->position += behaviorMachine_.Get_PlayerBehaviorPtr()->Gravity();

    DrawImGUi();
}

void Player::MatUpdate(void)
{
    sprite0_->MatUpdate();
    commonInfomation_->sprite_collider->MatUpdate();
    commonInfomation_->sprite_attackCollider->MatUpdate();
}

void Player::Draw(void)
{
    bool isBehaviorAttack = behaviorMachine_.Get_Behavior() == PB_ATTACK;
    isBehaviorAttack ?
        sprite0_->SetColor({ 1.0f, 0.0f, 0.0f, 1.f }) :
        sprite0_->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });
    sprite0_->Draw(png_hae_);

    // 当たり判定表示
    if (commonInfomation_->is_drawCollider)
    {
        commonInfomation_->sprite_collider->Draw(png_white_);
        isBehaviorAttack ?
            commonInfomation_->sprite_attackCollider->Draw(png_white_):
            commonInfomation_->sprite_attackCollider->Draw(png_frame_);
    }
}

void Player::DrawImGUi(void)
{
    auto& myCol = commonInfomation_->collider;
    auto imgui = ImGuiManager::GetInstance();
    imgui->BeginWindow("player");
    ImGui::SeparatorText("behavior");
    auto getBehavior = behaviorMachine_.Get_Behavior();
    std::string strBehavior = "current: ";
    if (getBehavior == PlayerBehavior::PB_DEFAULT) { strBehavior += "PB_DEFAULT"; }
    else if (getBehavior == PlayerBehavior::PB_IDLE) { strBehavior += "PB_IDLE"; }
    else if (getBehavior == PlayerBehavior::PB_MOVE) { strBehavior += "PB_MOVE"; }
    else if (getBehavior == PlayerBehavior::PB_JUMP) { strBehavior += "PB_JUMP"; }
    else if (getBehavior == PlayerBehavior::PB_ATTACK) { strBehavior += "PB_ATTACK"; }
    imgui->Text(strBehavior.c_str());
    static bool isShowLog{};
    imgui->CheckBox("Show Log", isShowLog);
    if (isShowLog)
    {
        ImGui::Begin("behaviorLog", nullptr, ImGuiWindowFlags_NoTitleBar);
        ImGui::SeparatorText("Behavior Log");
        auto& log = behaviorMachine_.Get_ImGui_BehaviorLog();
        for (const auto& str : log)
        {
            imgui->Text(str.c_str());
        }
        if (ImGui::Button("clear")) { log.clear(); }
        ImGui::End();
    }
    ImGui::Spacing();
    ImGui::SeparatorText("collider");
    // 当たり判定表示
    if (ImGui::Button("isShowCol")) { commonInfomation_->is_drawCollider = !commonInfomation_->is_drawCollider; }
    imgui->Text("player_pos : [%f][%f]", myCol.square_.center.x, myCol.square_.center.y);
    imgui->Text("player_size: [%f][%f]", myCol.square_.length.x, myCol.square_.length.y);
    imgui->Text("player_minX: [%f][%f]", myCol.square_.center.x - myCol.square_.length.x / 2, myCol.square_.center.y);
    imgui->EndWindow();
}

void Player::Callback(void)
{
    auto& myCol = commonInfomation_->collider;
    auto imgui = ImGuiManager::GetInstance();
    imgui->BeginWindow("player");
    Vector2 pushbackv{};

    if (myCol.IsDetect_Name("Boss0"))
    {
        auto* const contacted = myCol.Extract_Collider("Boss0");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        pushbackv = pushBack;
    }
    if (myCol.IsDetect_Name("Boss1"))
    {
        auto* const contacted = myCol.Extract_Collider("Boss1");

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
    if (myCol.IsDetect_Name("Boss2"))
    {
        auto* const contacted = myCol.Extract_Collider("Boss2");

        M_RectCollider* rect = static_cast<M_RectCollider*>(contacted);

        Vector2 pushBack = CollisionResponse::PushBack_AABB2AABB(myCol.square_, rect->square_);
        commonInfomation_->position += pushBack;
        commonInfomation_->collider.square_.center = commonInfomation_->position;

        commonInfomation_->can_jump = true;
        commonInfomation_->is_ground = true;

        pushbackv = pushBack;
    }
    else
    {
        // 地面に触れていない。※現時点での"床"は"Boss2"のみ
        commonInfomation_->is_ground = false;
    }

    if (myCol.IsDetect_Name("Boss3"))
    {
        auto* const contacted = myCol.Extract_Collider("Boss3");

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
