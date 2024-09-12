#pragma once
#include "Vector2.h"
#include "TimeManager.h"

#include <vector>

class Player;
namespace EnemyStatus {
	enum class MinionState {
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

	// 群衆AIに必要なパラメーター
	struct CrowdStats {
		float maxSpeed = 0.0f;
		float maxForce = 0.0f;
		float separationDistance = 0.0f;
		float neighborRadius = 0.0f;
	};

	// 雑魚敵の基礎的なパラメーター
	struct MinionStats {
		MinionState state = MinionState::Normal;// 状態
		Vector2 position = Vector2();			// 座標
		Vector2 velocity = Vector2();			// 速度
		Vector2 acceleration = Vector2();		// 加速度
		float dampingFactor = 0.3f;				// 減衰率 (慣性による速度の減衰)
		float attackPower = 20.0f;				// プレイヤーへのダメージ
		bool isAlive = true;					// 生存フラグ
		CrowdStats crowdStats;					// 群衆パラメーター
	};

	// 雑魚敵に必要な情報
	struct MinionData {
		// プレイヤーのポインタ
		Player* playerPtr = nullptr;
		// 時間管理クラスのポインタ
		TimeManager* timeMgrPtr = nullptr;
		// テクスチャのポインタ
		std::vector<uint16_t> textures;
	};
}