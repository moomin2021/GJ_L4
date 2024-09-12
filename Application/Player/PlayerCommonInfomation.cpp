#include "PlayerCommonInfomation.h"
#include <filesystem>
#include <fstream>

void PlayerCommonInfomation::Input(void)
{
    std::filesystem::path path = "./Resources/";
    std::filesystem::path name = "settings";
    auto full = path / name;
    std::fstream fs{ full };

    if (fs.is_open() == false) { return; }

    // 読込
    std::string line{};
    while (std::getline(fs, line))
    {
        // #から始まっていない場合スキップ
        if (line.starts_with("#") == false) { continue; }

        // 文字見つからなかったらスキップ
        size_t pos_colon = line.find(':');
        if (pos_colon == std::string::npos) { continue; }
        std::string str = line.substr(0, pos_colon);

        // 先に値を取得
        std::string value{};
        std::string value2{};
        value = line.substr(pos_colon + 2, 8);
        size_t pos_comma = line.find(',');
        size_t pos_semicolon = line.find(';');
        if (pos_comma != std::string::npos) { value2 = line.substr(pos_comma + 1, pos_semicolon - pos_comma); }

        if (value2.empty())
        {
            // Move
            if (str == "#kMoveSpeed") { kMoveSpeed = std::stof(value); }

            // Gravity
            else if (str == "#kGravity_max") { kGravity_max = std::stof(value); }
            else if (str == "#kGravity_add") { kGravity_add = std::stof(value); }

            // Jump
            else if (str == "#kJumpPower") { kJumpPower = std::stof(value); }

            // Sprite
            else if (str == "#kNum_IdleSprite_max") { kNum_IdleSprite_max = static_cast<int32_t>(std::stof(value)); }
            else if (str == "#kNum_AttackSprite_max") { kNum_AttackSprite_max = static_cast<int32_t>(std::stof(value)); }

            // Time
            else if (str == "#kTime_IdleInterval_max") { kTime_IdleInterval_max = std::stof(value); }
            else if (str == "#kTime_IdleAnimation_max") { kTime_IdleAnimation_max = std::stof(value); }
            else if (str == "#kTime_AttackInterval_max") { kTime_AttackInterval_max = std::stof(value); }
            else if (str == "#kTime_AttackAnimation_max") { kTime_AttackAnimation_max = std::stof(value); }
            else if (str == "#kTime_Invincible_max") { kTime_Invincible_max = std::stof(value); }
            else if (str == "#kTime_Easing_hp_content_shadow_max") { kTime_Easing_hp_content_shadow_max = std::stof(value); }
        }
        else
        {
            // Sprite
            if (str == "#kSprite_AnchorPoint_player_idle") { kSprite_AnchorPoint_player_idle = { std::stof(value), std::stof(value2) }; }
            else if (str == "#kSprite_AnchorPoint_player_attack") { kSprite_AnchorPoint_player_attack = { std::stof(value), std::stof(value2) }; }
            else if (str == "#kSprite_Length_player") { kSprite_Length_player = { std::stof(value), std::stof(value2) };}

            // Collider
            else if (str == "#kCollision_Length_playerCollider") 
            {
                kCollision_Length_playerCollider = { std::stof(value), std::stof(value2) };}
            else if (str == "#kCollision_Length_playerCollider_attack") { kCollision_Length_playerCollider_attack = { std::stof(value), std::stof(value2) };}
            else if (str == "#kCollision_positionOffset_playerCollider_attack") { kCollision_positionOffset_playerCollider_attack = { std::stof(value), std::stof(value2) }; }
        }
    }
}

void PlayerCommonInfomation::Output(void)
{
    std::filesystem::path path = "./Resources/";
    std::filesystem::path name = "settings";
    auto full = path / name;


    std::ofstream ofs{ full };
    ofs << "// Player" << std::endl;
    ofs << "#kHealth_max: " + std::to_string(kHealth_max) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Move" << std::endl;
    ofs << "#kMoveSpeed: " + std::to_string(kMoveSpeed) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Gravity" << std::endl;
    ofs << "#kGravity_max: " + std::to_string(kGravity_max) + ";" << std::endl;
    ofs << "#kGravity_add: " + std::to_string(kGravity_add) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Jump" << std::endl;
    ofs << "#kJumpPower: " + std::to_string(kJumpPower) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Sprite" << std::endl;
    ofs << "#kSprite_AnchorPoint_player_idle: " + std::to_string(kSprite_AnchorPoint_player_idle.x) + "," + std::to_string(kSprite_AnchorPoint_player_idle.y) + ";" << std::endl;
    ofs << "#kSprite_AnchorPoint_player_attack: " + std::to_string(kSprite_AnchorPoint_player_attack.x) + "," + std::to_string(kSprite_AnchorPoint_player_attack.y) + ";" << std::endl;
    ofs << "#kSprite_Length_player: " + std::to_string(kSprite_Length_player.x) + "," + std::to_string(kSprite_Length_player.y) + ";" << std::endl;
    ofs << std::endl;
    ofs << "#kNum_IdleSprite_max: " + std::to_string(kNum_IdleSprite_max) + ";" << std::endl;
    ofs << "#kNum_AttackSprite_max: " + std::to_string(kNum_AttackSprite_max) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Collider" << std::endl;
    ofs << "#kCollision_Length_playerCollider: " + std::to_string(kCollision_Length_playerCollider.x) + "," + std::to_string(kCollision_Length_playerCollider.y) + ";" << std::endl;
    ofs << "#kCollision_Length_playerCollider_attack: " + std::to_string(kCollision_Length_playerCollider_attack.x) + "," + std::to_string(kCollision_Length_playerCollider_attack.y) + ";" << std::endl;
    ofs << "#kCollision_positionOffset_playerCollider_attack: " + std::to_string(kCollision_positionOffset_playerCollider_attack.x) + "," + std::to_string(kCollision_positionOffset_playerCollider_attack.y) + ";" << std::endl;
    ofs << std::endl;

    ofs << "// Time" << std::endl;
    ofs << "#kTime_IdleInterval_max: " + std::to_string(kTime_IdleInterval_max) + ";" << std::endl;
    ofs << "#kTime_IdleAnimation_max: " + std::to_string(kTime_IdleAnimation_max) + ";" << std::endl;
    ofs << "#kTime_AttackInterval_max: " + std::to_string(kTime_AttackInterval_max) + ";" << std::endl;
    ofs << "#kTime_AttackAnimation_max: " + std::to_string(kTime_AttackAnimation_max) + ";" << std::endl;
    ofs << "#kTime_Invincible_max: " + std::to_string(kTime_Invincible_max) + ";" << std::endl;
    ofs << "#kTime_Easing_hp_content_shadow_max: " + std::to_string(kTime_Invincible_max) + ";" << std::endl;
    ofs << std::endl;
}

void PlayerCommonInfomation::Update(void)
{
    collider.square_.center = position;
    gravity.Update();
    health_rate_ = health_current / (std::max)(kHealth_max, 1.f); // 0除算ケア
}
