#pragma once
#include "Vector2.h"
#include "float4.h"
#include "M_CircleCollider.h"
#include "Camera.h"

class Player;
struct SubBossInfo {
	// 座標とサイズと回転度
	Vector2 position = Vector2();	// サブボスの座標
	Vector2 size = Vector2();		// サブボスのサイズ
	float rotation = 0.0f;			// サブボスの回転度
	float4 mainColor = float4();	// 本体の色
	float4 eyeColor = float4();		// 目の色

	// 動作に関する情報
	Vector2 moveVec = Vector2();	// 移動方向
	float moveSpd = 0.0f;			// 移動速度
	float rotateSpd = 0.0f;			// 回転速度

	// コライダー
	M_CircleCollider collider;

	// 震えの値
	Vector2 shakeOffset = Vector2();

	// 床と衝突しているか
	bool isGroundCol = false;

	// プレイヤーのポインタ
	Player* playerPtr = nullptr;

	// カメラのポインタ
	Camera* cameraPtr = nullptr;

	// 移動処理
	void Move(float deltaTime);
	// 回転処理
	void Rotate(float deltaTime);
};