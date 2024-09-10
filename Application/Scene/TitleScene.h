#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"
#include "ImGuiManager.h"

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

	};

	// インスタンス
	Key* key_ = nullptr;

	// Imguiインスタンス
	ImGuiManager* pImGuiMgr_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// スプライト
	std::unique_ptr<Sprite> sprite0_ = nullptr;
	std::unique_ptr<Sprite> sprite1_ = nullptr;

	std::vector<std::unique_ptr<Sprite>> titleSprites_;

	// テクスチャ
	int32_t texture_ = 0;

	// 壁のフォントテクスチャ
	std::vector<uint16_t> wallFontTex_;

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

	// タイトルの文字のテクスチャたち
	std::vector<int32_t> titleTextures_;
	int32_t titleWallTex_ = 0;
	int32_t titleWallFontTex = 0;
	int32_t boFontTex_ = 0;
	int32_t daTex_ = 0;
	int32_t daDaTex_ = 0;
	int32_t daDaDaTex_ = 0;
	int32_t pointFontTex_ = 0;

	int debugNum = 0;

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

	void ImGuiUpdate();
#pragma endregion
};
