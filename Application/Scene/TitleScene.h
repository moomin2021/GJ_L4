#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "AppEasing.h"
#include <memory>

class TitleScene : public BaseScene
{
#pragma region メンバ変数
private:
	enum TitleSprites
	{
		TitleWall,
		WallFontTex,
		DaFontTex,
		Point1Tex,
		DaDaTex,
		Point2Tex,
		DaDaDaTex,
		BoTex,

		TitleSpriteSize,
	};

	enum TitleFontState
	{
		WallFontPhase,
		DaPhase,
		DaDaPhase,
		DaDaDaPhase,
	};

	// インスタンス
	Key* key_ = nullptr;

	// Imguiインスタンス
	ImGuiManager* pImGuiMgr_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// スプライト


	std::vector<std::unique_ptr<Sprite>> titleSprites_;

	// テクスチャ
	int32_t texture_ = 0;

	// 壁のフォントテクスチャ
	std::vector<uint16_t> wallFontTex_;

	
	int wallFontAnimeCount;
	int wallFontAnimeCountMax;
	int wallFontCurrentTexNum;
	int wallFontCurrentTexNumMax;
	int wallFontAnimetionTimer;
	int wallFontAnimetionTimeLimit;

	// タイトルのスプライトのデフォルト座標
	std::vector<Vector2> titleSpriteDefaultPos_;

	// タイトルのスプライトのデフォルトサイズ
	std::vector<Vector2> titleSpriteDefaultSize_;

	// タイトルのスプライトの現在のスケール
	std::vector<Vector2> titleSpriteCurrentScale_;

	// タイトルのスプライトのデフォルトスケール
	std::vector<Vector2> titleSpriteDefaultScale_;

	// タイトルのスプライトの変化スケール
	std::vector<Vector2> titleSpriteChangeScale_;

	// 回転
	std::vector<float> titleSpriteRotation_;

	// カラー
	std::vector<float4> titleSpriteColor_;

	// タイトルの文字のテクスチャたち
	std::vector<int32_t> titleTextures_;

	int32_t titleStartKeyTex_ = 0;
	int32_t wallOnlyTex = 0;
	int32_t backGroundTex = 0;

	std::unique_ptr<Sprite> titleStartKeySprite_ = nullptr;
	std::unique_ptr<Sprite> wallOnlySprite_ = nullptr;
	std::unique_ptr<Sprite> backGroundSprite_ = nullptr;

	Vector2 startKeySpritePos_;
	Vector2 startKeySpriteDefultPos_;
	float4 startKeySpriteColor_;

	Vector2 wallSpritePos_;

	Vector2 startKeySpriteSize_;
	Vector2 wallSpriteSize_;

	int debugNum = 0;

	TitleFontState fontState_= WallFontPhase;

	// Daのパラメータ
	AppEasing easeDa_;
	bool IsBigDa_;

	// DaDaのパラメータ
	AppEasing easeDaDa_;
	bool IsBigDaDa_;

	// DaDaDaのパラメータ
	AppEasing easeDaDaDa_;
	AppEasing easeBo_;
	float boRotaDefult;
	bool IsBigDaDaDa_;

	// スタートキーのパラメータ
	float sinCount;
	float sinCountMax;
	float sinSwingValue;

	// チェンジフラグ
	bool IsChangeScene_;
	float alphaLossValue_;

#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	TitleScene(IScene* sceneIf);
	~TitleScene() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();

	// パッケージ関数

	// タイトルフォントの遷移更新処理
	void TitleFontStateUpdate();

	// タイトルシーンチェンジ時の処理
	void TitleChangeSceneUpdate();

	// Imguiの更新処理
	void ImGuiUpdate();

	float Sin_ZeroToOne(float pos, float maxCount, float nowCount, float swingWidth);
#pragma endregion
};
