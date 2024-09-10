#include "Player.h"
#include "Texture.h"
#include "CollisionChecker.h"
#include "ImGuiManager.h"
#include "Key.h"
#include "Pad.h"
#include "imgui.h"
#include <fstream>

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
    commonInfomation_->png_playerAttack = LoadDivTexture("playerKariSwing.png", static_cast<int16_t>(commonInfomation_->kNum_AttackSprite_max));

    commonInfomation_->sprite_player = std::make_unique<Sprite>();
    commonInfomation_->sprite_player->SetSize(commonInfomation_->kSprite_Length_player);
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_idle);
    commonInfomation_->sprite_player->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_collider = std::make_unique<Sprite>();
    commonInfomation_->sprite_collider->SetPosition(commonInfomation_->position);
    commonInfomation_->sprite_collider->SetSize(commonInfomation_->kCollision_Length_playerCollider);
    commonInfomation_->sprite_collider->SetAnchorPoint({ 0.5f, 0.5f });
    commonInfomation_->sprite_collider->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });

    commonInfomation_->sprite_attackCollider = std::make_unique<Sprite>();
    commonInfomation_->sprite_attackCollider->SetPosition(commonInfomation_->position + commonInfomation_->kCollision_positionOffset_playerCollider_attack);
    commonInfomation_->sprite_attackCollider->SetSize(commonInfomation_->kCollision_Length_playerCollider_attack);
    commonInfomation_->sprite_attackCollider->SetAnchorPoint({ 0.5f, 0.5f });
    commonInfomation_->sprite_attackCollider->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    // 重力
    commonInfomation_->gravity.Initialize(commonInfomation_->kGravity_max, commonInfomation_->kGravity_add);

    //** コライダー
    // メンバ変数の設定
    commonInfomation_->collider.square_.center = commonInfomation_->position;
    commonInfomation_->collider.square_.length = commonInfomation_->kCollision_Length_playerCollider;
    // ローカル変数
    std::string name = "Player";
    auto callback = std::bind(&Player::Callback, this);
    // 初期化関数
    commonInfomation_->collider.Initialize(name, callback, arg_colliderManagerPtr);

    // 操作ボタン
    // key
    commonInfomation_->keyBind.move_up = DIK_W;
    commonInfomation_->keyBind.move_down = DIK_S;
    commonInfomation_->keyBind.move_left = DIK_A;
    commonInfomation_->keyBind.move_right = DIK_D;
    commonInfomation_->keyBind.jump = DIK_SPACE;
    commonInfomation_->keyBind.attack = DIK_F;

    // controller
    commonInfomation_->controllerBind.attack = BUTTON::PAD_B;
    commonInfomation_->controllerBind.jump = BUTTON::PAD_A;

}

void Player::Update(void)
{
    // 移動記録の更新
    commonInfomation_->move.Update();
    // 状態管理クラスの更新
    behaviorMachine_.Update();

    // Sprite|プレイヤーの座標更新
    commonInfomation_->sprite_player->SetPosition(commonInfomation_->position);
    // Sprite|プレイヤーコライダーの座標更新
    commonInfomation_->sprite_collider->SetPosition(commonInfomation_->position);

    // プレイヤーの向きが右の時は、オフセット値を反転
    Vector2 offset = commonInfomation_->kCollision_positionOffset_playerCollider_attack;
    if (commonInfomation_->move.direction_current == DIRECTION_RIGHT) { offset.x *= -1; }
    // Sprite|プレイヤー攻撃コライダーの座標更新
    commonInfomation_->sprite_attackCollider->SetPosition(commonInfomation_->position + offset);

    // プレイヤー共通情報の更新
    commonInfomation_->Update();
    
    // 重力の加算
    const Vector2& gravity = behaviorMachine_.Get_PlayerBehaviorPtr()->Gravity();
    commonInfomation_->position += gravity;
    // どの程度移動したか記録する
    commonInfomation_->move.velocity_current += gravity;

    DrawImGUi();
}

void Player::MatUpdate(void)
{
    commonInfomation_->sprite_player->MatUpdate();
    commonInfomation_->sprite_collider->MatUpdate();
    commonInfomation_->sprite_attackCollider->MatUpdate();
}

void Player::Draw(void)
{
    bool isBehaviorAttack = behaviorMachine_.Get_Behavior() == PB_ATTACK;

    if (isBehaviorAttack)
    {
        commonInfomation_->sprite_player->Draw(commonInfomation_->png_playerAttack[commonInfomation_->num_attackSprite]);
    }
    else
    {
        commonInfomation_->sprite_player->Draw(png_hae_);
    }


    // 当たり判定表示
    if (commonInfomation_->is_drawCollider)
    {
        commonInfomation_->sprite_collider->Draw(png_white_);
        isBehaviorAttack ?
            commonInfomation_->sprite_attackCollider->Draw(png_white_) :
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
            ImVec4 darkRed = { 1,0,0,1 };
            ImVec4 darkEmerald = { 0,1,0,1 };

            std::vector<std::string> behaviors{};
            std::istringstream iss(str);
            std::string s{};
            size_t num{};
            while (std::getline(iss, s, '/'))
            {
                // 左
                if (s == "PB_JUMP") { ImGui::TextColored(darkRed, s.c_str()); }
                else if (s == "PB_ATTACK") { ImGui::TextColored(darkEmerald, s.c_str()); }
                else { ImGui::Text(s.c_str()); }

                if (num >= 1) { break; }
                ImGui::SameLine();
                ImGui::Text(" -> ");
                ImGui::SameLine();
                num++;
            }
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

        commonInfomation_->move.can_jump = true;
        commonInfomation_->move.is_ground = true;

        pushbackv = pushBack;
    }
    else
    {
        // 地面に触れていない。※現時点での"床"は"Boss2"のみ
        commonInfomation_->move.is_ground = false;
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

    commonInfomation_->move.velocity_current += pushbackv;

    // 押し出し後に座標を合わせる
    commonInfomation_->sprite_player->SetPosition(commonInfomation_->position);
}
