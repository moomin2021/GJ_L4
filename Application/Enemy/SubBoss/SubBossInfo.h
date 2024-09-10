#pragma once
#include "Vector2.h"

class Player;
struct SubBossInfo {
	// 座標とサイズと回転度
	Vector2 position = Vector2();	// サブボスの座標
	Vector2 size = Vector2();		// サブボスのサイズ
	float rotation = 0.0f;			// サブボスの回転度

	// 動作に関する情報
	Vector2 moveVec = Vector2();	// 移動方向
	float moveSpd = 0.0f;			// 移動速度
	float rotateSpd = 0.0f;			// 回転速度

	// プレイヤーのポインタ
	Player* playerPtr = nullptr;

	// 移動処理
	void Move(float deltaTime);
	// 回転処理
	void Rotate(float deltaTime);
};