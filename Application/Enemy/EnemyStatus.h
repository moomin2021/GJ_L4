#pragma once
#include "Vector2.h"

#include <vector>

class Player;
namespace EnemyStatus {
	enum class State {
		Normal,
		FirstBeaten,
		KnockBack,
		SecondBeaten
	};

	// 雑魚敵のタイプ
	enum class MinionType {
		Leader,
		Follower,
	};

	// 雑魚敵の基礎的なパラメーター
	struct MinionStats {
		Vector2 position = Vector2();		// 座標
		Vector2 velocity = Vector2();		// 速度
		Vector2 acceleration = Vector2();	// 加速度
		float dampingFactor = 0.0f;			// 減衰率 (慣性による速度の減衰)
		float attackPower = 20.0f;			// プレイヤーへのダメージ
		bool isAlive = true;				// 生存フラグ
	};

	// 雑魚敵に必要な情報
	struct MinionData {
		// プレイヤーのポインタ
		Player* playerPtr = nullptr;
		// テクスチャのポインタ
		std::vector<uint16_t> textures;
	};
}