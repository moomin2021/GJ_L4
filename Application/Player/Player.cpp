#include "Player.h"
#include "Texture.h"
#include "CollisionChecker.h"
#include "ImGuiManager.h"
#include "Key.h"
#include "Pad.h"
#include "imgui.h"
#include <fstream>
#include "Util.h"
#include "Easing.h"
#include "TimeManager.h"

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
    png_player_ = LoadTexture("playerKari.png");
    png_HPBar_frame_ = LoadTexture("HpBarFrame.png");
    png_HPBar_content_ = LoadTexture("HpBarContents.png");
    png_HPBar_content_shadow_ = LoadTexture("HpBarContentsShadow.png");
    png_SPBar_frame_ = LoadTexture("SpBarFrame.png");
    png_SPBar_content_ = LoadTexture("SpBarContents.png");
    png_operationSheet_ = LoadTexture("operationSheet_224x64.png");
    png_operationSheet_divide_ = LoadDivTexture("operationSheet_224x64.png", 3);

    sprite_operationSheet_ = std::make_unique<Sprite>();
    sprite_operationSheet_->SetSize({ 672,64 });
    sprite_operationSheet_->SetPosition({ 90,1000 });
    sprite_operationSheet_->SetColor({ 1.0f, 1.0f, 1.0f, 0.4f });

    for (size_t i{}; i < 3; i++)
    {
        sprite_operationSheet_divides_[i] = std::make_unique<Sprite>();
        sprite_operationSheet_divides_[i]->SetSize({ 224,64 });
        sprite_operationSheet_divides_[i]->SetPosition({ 90 + (float)i * 224,1000});
        sprite_operationSheet_divides_[i]->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });
    }


    png_white_debug = LoadTexture("white.png");
    png_frame_debug = LoadTexture("frame.png");
    commonInfomation_->png_playerIdle = LoadDivTexture("playerWait.png", static_cast<int16_t>(commonInfomation_->kNum_IdleSprite_max));
    commonInfomation_->png_playerMove = LoadDivTexture("playerRun.png", static_cast<int16_t>(commonInfomation_->kNum_MoveSprite_max));
    commonInfomation_->png_playerAttack = LoadDivTexture("playerKariSwing.png", static_cast<int16_t>(commonInfomation_->kNum_AttackSprite_max));
    commonInfomation_->png_playerSpecial = LoadDivTexture("playerKariSwing.png", static_cast<int16_t>(commonInfomation_->kNum_SpecialSprite_max));

    commonInfomation_->sprite_player = std::make_unique<Sprite>();
    commonInfomation_->sprite_player->SetSize(commonInfomation_->kSprite_Length_player);
    commonInfomation_->sprite_player->SetAnchorPoint(commonInfomation_->kSprite_AnchorPoint_player_idle);
    commonInfomation_->sprite_player->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_player_hpFrame = std::make_unique<Sprite>();
    commonInfomation_->sprite_player_hpFrame->SetSize({ 419,82 });
    commonInfomation_->sprite_player_hpFrame->SetPosition({ 90,12 });
    commonInfomation_->sprite_player_hpFrame->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_player_hpContent = std::make_unique<Sprite>();
    commonInfomation_->sprite_player_hpContent->SetSize({ 302,62 });
    commonInfomation_->sprite_player_hpContent->SetPosition({ 193,21 });
    commonInfomation_->sprite_player_hpContent->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_player_hpContent_shadow = std::make_unique<Sprite>();
    commonInfomation_->sprite_player_hpContent_shadow->SetSize({ 302,62 });
    commonInfomation_->sprite_player_hpContent_shadow->SetPosition({ 193,21 });
    commonInfomation_->sprite_player_hpContent_shadow->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_player_spFrame = std::make_unique<Sprite>();
    commonInfomation_->sprite_player_spFrame->SetSize({ 512,42 });
    commonInfomation_->sprite_player_spFrame->SetPosition({ 90,100 });
    commonInfomation_->sprite_player_spFrame->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    commonInfomation_->sprite_player_spContent = std::make_unique<Sprite>();
    commonInfomation_->sprite_player_spContent->SetSize({ 399,27 });
    commonInfomation_->sprite_player_spContent->SetPosition({ 193,108 });
    commonInfomation_->sprite_player_spContent->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });

    // DEBUG
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

    commonInfomation_->sprite_specialCollider = std::make_unique<Sprite>();
    commonInfomation_->sprite_specialCollider->SetPosition(commonInfomation_->position + commonInfomation_->kCollision_positionOffset_playerCollider_special);
    commonInfomation_->sprite_specialCollider->SetSize(commonInfomation_->kCollision_Length_playerCollider_special);
    commonInfomation_->sprite_specialCollider->SetAnchorPoint({ 0.5f, 0.5f });
    commonInfomation_->sprite_specialCollider->SetColor({ 1.0f, 0.0f, 0.0f, 1.f });

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
    commonInfomation_->keyBind.special = DIK_G;

    // controller
    commonInfomation_->controllerBind.special = BUTTON::PAD_X;
    commonInfomation_->controllerBind.attack = BUTTON::PAD_B;
    commonInfomation_->controllerBind.jump = BUTTON::PAD_A;

    commonInfomation_->Input();
    commonInfomation_->health_current = commonInfomation_->kHealth_max;
    commonInfomation_->sp_current = commonInfomation_->kSp_max;
}

void Player::Update(void)
{
    if (Key::GetInstance()->TriggerKey(DIK_R)) { commonInfomation_->Input(); }
    if (Key::GetInstance()->TriggerKey(DIK_O)) { commonInfomation_->Output(); }
    if (Key::GetInstance()->TriggerKey(DIK_H)) { Damage(20); }

    // 移動記録の更新
    commonInfomation_->move.Update();
    // 状態管理クラスの更新
    behaviorMachine_.Update();

    // Sprite|プレイヤーの座標更新
    commonInfomation_->sprite_player->SetPosition(commonInfomation_->position);
    // Sprite|プレイヤーコライダーの座標更新
    commonInfomation_->sprite_collider->SetPosition(commonInfomation_->position);
    // Sprite|プレイヤーのHPバーのサイズ更新
    Vector2 hpBarSize = { 302 * commonInfomation_->health_rate_, 62 };
    commonInfomation_->sprite_player_hpContent->SetSize(hpBarSize);
    // Sprite|プレイヤーのHPバー（影）のサイズ更新
    Vector2 hpBarShadowSize{};
    if (is_easingShadow_)
    {
        commonInfomation_->timer_easing_hp_content_shadow += TimeManager::GetInstance()->GetGameDeltaTime();
        commonInfomation_->timer_easing_hp_content_shadow = (std::min)(commonInfomation_->timer_easing_hp_content_shadow, commonInfomation_->kTime_Easing_hp_content_shadow_max);
        float elapsed = commonInfomation_->timer_easing_hp_content_shadow / commonInfomation_->kTime_Easing_hp_content_shadow_max;
        elapsed = Util::Clamp(elapsed, 1.0f, 0.0f);
        elapsed = Easing::Cubic::easeOut(ease_shadow_start_, commonInfomation_->sprite_player_hpContent->GetSize().x, elapsed);
        hpBarShadowSize = { elapsed, 62 };

        if (commonInfomation_->timer_easing_hp_content_shadow >= commonInfomation_->kTime_Easing_hp_content_shadow_max) { is_easingShadow_ = false; }
    }
    commonInfomation_->sprite_player_hpContent_shadow->SetSize(hpBarShadowSize);

    // プレイヤーの向きが右の時は、オフセット値を反転 *ATTACK/SPECIAL
    Vector2 offset_attack = commonInfomation_->kCollision_positionOffset_playerCollider_attack;
    if (commonInfomation_->move.direction_current == DIRECTION_RIGHT) { offset_attack.x *= -1; }
    Vector2 offset_special = commonInfomation_->kCollision_positionOffset_playerCollider_special;
    if (commonInfomation_->move.direction_current == DIRECTION_RIGHT) { offset_special.x *= -1; }
    // Sprite|プレイヤー攻撃コライダーの座標更新
    commonInfomation_->sprite_attackCollider->SetPosition(commonInfomation_->position + offset_attack);
    commonInfomation_->sprite_specialCollider->SetPosition(commonInfomation_->position + offset_special);

    // プレイヤー共通情報の更新
    commonInfomation_->Update();

    // 重力の加算
    const Vector2& gravity = behaviorMachine_.Get_PlayerBehaviorPtr()->Gravity();
    commonInfomation_->position += gravity;
    // どの程度移動したか記録する
    commonInfomation_->move.velocity_current += gravity;
    // コライダーの更新
    commonInfomation_->collider.square_.center = commonInfomation_->position;

    auto ptr_key = Key::GetInstance();
    auto ptr_pad = Pad::GetInstance();
    bool isGround = commonInfomation_->move.is_ground;
    bool isJumped = commonInfomation_->move.is_jumped;

    bool isSpecial{};
    isSpecial = ptr_key->TriggerKey(commonInfomation_->keyBind.special);
    isSpecial = (std::max)(ptr_pad->GetTriggerButton((BUTTON)commonInfomation_->controllerBind.special), isSpecial);
    if (operationButtons_[0] == false) { operationButtons_[0] = isSpecial; }
    else if (timer_lightUpButtons_[0] >= kTime_lightUpButton_max_)
    {
        timer_lightUpButtons_[0] = 0.f;
        operationButtons_[0] = isSpecial;
    }


    bool isAttack{};
    isAttack = ptr_key->TriggerKey(commonInfomation_->keyBind.attack);
    isAttack = (std::max)(ptr_pad->GetTriggerButton((BUTTON)commonInfomation_->controllerBind.attack), isAttack);
    if (operationButtons_[1] == false) { operationButtons_[1] = isAttack; }
    else if (timer_lightUpButtons_[1] >= kTime_lightUpButton_max_)
    {
        timer_lightUpButtons_[1] = 0.f;
        operationButtons_[1] = isAttack;
    }


    bool isJump{};
    isJump = ptr_key->TriggerKey(commonInfomation_->keyBind.jump) && isJumped && isGround;
    isJump = (std::max)(ptr_pad->GetTriggerButton((BUTTON)commonInfomation_->controllerBind.jump) && isJumped && isGround, isJump);
    if (isJump) { isJump = isJump; }
    if (operationButtons_[2] == false) { operationButtons_[2] = isJump; }
    else if (timer_lightUpButtons_[2] >= kTime_lightUpButton_max_)
    {
        timer_lightUpButtons_[2] = 0.f;
        operationButtons_[2] = isJump;
    }

    for (size_t i = 0; i < operationButtons_.size(); i++)
    {
        if (operationButtons_[i] == false) { continue; }
        timer_lightUpButtons_[i] += TimeManager::GetInstance()->GetGameDeltaTime();
    }

#ifdef _DEBUG
    DrawImGUi();
#endif // _DEBUG
}

void Player::MatUpdate(void)
{
    commonInfomation_->sprite_player->MatUpdate();
    commonInfomation_->sprite_player_hpFrame->MatUpdate();
    commonInfomation_->sprite_player_hpContent->MatUpdate();
    commonInfomation_->sprite_player_hpContent_shadow->MatUpdate();
    commonInfomation_->sprite_player_spFrame->MatUpdate();
    commonInfomation_->sprite_player_spContent->MatUpdate();
    commonInfomation_->sprite_collider->MatUpdate();
    commonInfomation_->sprite_attackCollider->MatUpdate();
    commonInfomation_->sprite_specialCollider->MatUpdate();
    sprite_operationSheet_->MatUpdate();
    for (size_t i{}; i < 3; i++)
    {
        sprite_operationSheet_divides_[i]->MatUpdate();
    }
}

void Player::Draw(void)
{
    switch (behaviorMachine_.Get_Behavior())
    {
    case PB_IDLE:
        commonInfomation_->sprite_player->Draw(commonInfomation_->png_playerIdle[commonInfomation_->num_idleSprite]);
        break;
    case PB_MOVE:
        commonInfomation_->sprite_player->Draw(commonInfomation_->png_playerMove[commonInfomation_->num_moveSprite]);
        break;
    case PB_ATTACK:
        commonInfomation_->sprite_player->Draw(commonInfomation_->png_playerAttack[commonInfomation_->num_attackSprite]);
        break;
    case PB_SPECIAL:
        commonInfomation_->sprite_player->Draw(commonInfomation_->png_playerSpecial[commonInfomation_->num_specialSprite]);
        break;
    default:
        commonInfomation_->sprite_player->Draw(png_player_);
        break;
    }

    commonInfomation_->sprite_player_hpContent_shadow->Draw(png_HPBar_content_shadow_);
    commonInfomation_->sprite_player_hpContent->Draw(png_HPBar_content_);
    commonInfomation_->sprite_player_hpFrame->Draw(png_HPBar_frame_);
    commonInfomation_->sprite_player_spContent->Draw(png_SPBar_content_);
    commonInfomation_->sprite_player_spFrame->Draw(png_SPBar_frame_);

    sprite_operationSheet_->Draw(png_operationSheet_);

    for (size_t i = 0; i < operationButtons_.size(); i++)
    {
        if (operationButtons_[i] == false) { continue; }

        sprite_operationSheet_divides_[i]->Draw(png_operationSheet_divide_[i]);
    }

    bool isBehaviorAttack = behaviorMachine_.Get_Behavior() == PB_ATTACK;
    bool isBehaviorSpecial = behaviorMachine_.Get_Behavior() == PB_SPECIAL;
    // 当たり判定表示
    if (commonInfomation_->is_drawCollider)
    {
        commonInfomation_->sprite_collider->Draw(png_white_debug);
        isBehaviorAttack ?
            commonInfomation_->sprite_attackCollider->Draw(png_white_debug) :
            commonInfomation_->sprite_attackCollider->Draw(png_frame_debug);
        isBehaviorSpecial ?
            commonInfomation_->sprite_specialCollider->Draw(png_white_debug) :
            commonInfomation_->sprite_specialCollider->Draw(png_frame_debug);
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
    else if (getBehavior == PlayerBehavior::PB_SPECIAL) { strBehavior += "PB_SPECIAL"; }
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
            ImVec4 Red = { 1,0,0,1 };
            ImVec4 Green = { 0,1,0,1 };
            ImVec4 Blue = { 0,1,0,1 };

            std::vector<std::string> behaviors{};
            std::istringstream iss(str);
            std::string s{};
            size_t num{};
            while (std::getline(iss, s, '/'))
            {
                // 左
                if (s == "PB_JUMP") { ImGui::TextColored(Red, s.c_str()); }
                else if (s == "PB_ATTACK") { ImGui::TextColored(Green, s.c_str()); }
                else if (s == "PB_SPECIAL") { ImGui::TextColored(Blue, s.c_str()); }
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

    imgui->BeginWindow("player_status");
    ImGui::SliderFloat("kMoveSpeed", &commonInfomation_->kMoveSpeed, 0, 500);

    ImGui::SliderFloat("kGravity_max", &commonInfomation_->kGravity_max, 0, 100);
    ImGui::SliderFloat("kGravity_add", &commonInfomation_->kGravity_add, 0, 100);

    ImGui::SliderFloat("kJumpPower", &commonInfomation_->kJumpPower, -100, 100);

    float* sprite_AnchorPoint_player_idle[2] = { &commonInfomation_->kSprite_AnchorPoint_player_idle.x, &commonInfomation_->kSprite_AnchorPoint_player_idle.y };
    ImGui::SliderFloat2("kSprite_AnchorPoint_player_idle", *sprite_AnchorPoint_player_idle, 0, 1);
    float* sprite_AnchorPoint_player_attack[2] = { &commonInfomation_->kSprite_AnchorPoint_player_attack.x, &commonInfomation_->kSprite_AnchorPoint_player_attack.y };
    ImGui::SliderFloat2("kSprite_AnchorPoint_player_attack", *sprite_AnchorPoint_player_attack, 0, 1);
    float* sprite_AnchorPoint_player_special[2] = { &commonInfomation_->kSprite_AnchorPoint_player_special.x, &commonInfomation_->kSprite_AnchorPoint_player_special.y };
    ImGui::SliderFloat2("kSprite_AnchorPoint_player_special", *sprite_AnchorPoint_player_special, 0, 1);
    float* sprite_Length_player[2] = { &commonInfomation_->kSprite_Length_player.x, &commonInfomation_->kSprite_Length_player.y };
    ImGui::SliderFloat2("kSprite_Length_player", *sprite_Length_player, 0, 300);

    float* collision_Length_playerCollider[2] = { &commonInfomation_->kCollision_Length_playerCollider.x, &commonInfomation_->kCollision_Length_playerCollider.y };
    ImGui::SliderFloat2("kCollision_Length_playerCollider", *collision_Length_playerCollider, 0, 100);
    float* collision_Length_playerCollider_attack[2] = { &commonInfomation_->kCollision_Length_playerCollider_attack.x, &commonInfomation_->kCollision_Length_playerCollider_attack.y };
    ImGui::SliderFloat2("kCollision_Length_playerCollider_attack", *collision_Length_playerCollider_attack, 0, 300);
    float* collision_positionOffset_playerCollider_attack[2] = { &commonInfomation_->kCollision_positionOffset_playerCollider_attack.x, &commonInfomation_->kCollision_positionOffset_playerCollider_attack.y };
    ImGui::SliderFloat2("kCollision_positionOffset_playerCollider_attack", *collision_positionOffset_playerCollider_attack, -100, 100);
    float* collision_Length_playerCollider_special[2] = { &commonInfomation_->kCollision_Length_playerCollider_special.x, &commonInfomation_->kCollision_Length_playerCollider_special.y };
    ImGui::SliderFloat2("kCollision_Length_playerCollider_special", *collision_Length_playerCollider_special, 0, 300);
    float* collision_positionOffset_playerCollider_special[2] = { &commonInfomation_->kCollision_positionOffset_playerCollider_special.x, &commonInfomation_->kCollision_positionOffset_playerCollider_special.y };
    ImGui::SliderFloat2("kCollision_positionOffset_playerCollider_special", *collision_positionOffset_playerCollider_special, -100, 100);
    ImGui::SliderFloat("kHealth_max", &commonInfomation_->kHealth_max, 1, 100);
    ImGui::SliderFloat("health_current", &commonInfomation_->health_current, 0, 100);

    imgui->EndWindow();
}

void Player::Damage(float arg_damage)
{
    // 既にイージングが開始されているか
    if (is_easingShadow_ == false)
    {
        is_easingShadow_ = true;
        // イージングの経過時間をリセット
        commonInfomation_->timer_easing_hp_content_shadow = 0.f;
        // イージングの初期地は、現在のHPバーの横幅とする
        ease_shadow_start_ = commonInfomation_->sprite_player_hpContent->GetSize().x;
    }
    else
    {
        // イージングの経過時間をリセット
        commonInfomation_->timer_easing_hp_content_shadow = 0.f;
        // イージングの初期地は、HP影の横幅とする
        ease_shadow_start_ = commonInfomation_->sprite_player_hpContent_shadow->GetSize().x;
    }

    // 現在HPから差し引く
    commonInfomation_->health_current -= arg_damage;
}

void Player::Callback(void)
{
    auto& myCol = commonInfomation_->collider;
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
        commonInfomation_->move.is_jumped = false;

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
    }

    commonInfomation_->move.velocity_current += pushbackv;

    // 押し出し後に座標を合わせる
    commonInfomation_->sprite_player->SetPosition(commonInfomation_->position);
}
