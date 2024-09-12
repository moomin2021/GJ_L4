#pragma once
#include "Vector2.h"

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
}