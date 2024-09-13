#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Camera.h"
#include "Sprite.h"
#include <memory>

class GameClearScene : public BaseScene
{
private:
	// インスタンス
	Key* key_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	std::unique_ptr<Sprite> backGroundSprite_ = nullptr;
	int32_t backGroundTex = 0;

	// ブラック＆ホワイトアウト用の画像
	std::unique_ptr<Sprite> blackOutSprite_ = nullptr;
	int32_t blackOutTex_;

	float4 whiteBaseColor = { 1,1,1,1 };
	float4 baseInColor = { 1,1,1,1 };
	float4 baseOutColor = { 1,1,1,0 };
	float alphaValue_ = 0.01f;

	bool IsChageScene_ = false;
	bool IsStartScene_ = false;

public:
	// コンストラクタとデストラクタ
	GameClearScene(IScene* sceneIf);
	~GameClearScene() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void Draw();
	void Finalize();
};

