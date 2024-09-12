#include "SubBossAttackState.h"
#include "TimeManager.h"
#include "Easing.h"
#include "Util.h"

#include "Player.h"

void DescentDiveState::Initialize(SubBossInfo* info)
{
	presetTargetPos_ = info->position;
	targetPos_ = Vector2(960.0f, 400.0f);

	// ステージ1で使う変数
	moveInfoS1_.maxSpd_ = 400.0f;
	moveInfoS1_.acceleration = 50.0f;

	// ステージ3で使う変数
	diveInfo_.derection = Vector2(0.0f, 1.0f);
	diveInfo_.acceleration = 400.0f;
	diveInfo_.maxSpd_ = 400.0f;
}

void DescentDiveState::Update(SubBossInfo* info)
{
	// 時間管理クラスのインスタンスを取得
	TimeManager* timeMgr = TimeManager::GetInstance();

	// 規定の場所へ移動
	if (attackStage_ == 0) {
		// 時間の加算
		stage0Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage0Time_.GetElapsedRatio();
		info->position.x = Easing::Quint::easeOut(presetTargetPos_.x, targetPos_.x, rate);
		info->position.y = Easing::Quint::easeOut(presetTargetPos_.y, targetPos_.y, rate);
		// 時間を超えたら次の段階へ
		if (stage0Time_.GetIsExceeded()) attackStage_++;
	}

	// プレイヤーを追いかける
	else if (attackStage_ == 1) {
		// 時間の加算
		stage1Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 時間を超えたら次の段階へ
		if (stage1Time_.GetIsExceeded()) attackStage_++;

		// 移動方向の計算
		Vector2 boss2PlayerVec = info->playerPtr->Get_CommonInfomation()->position - info->position;
		// X軸だけを抽出
		boss2PlayerVec.y = 0.0f;
		// 速度の加算
		moveInfoS1_.speed = Util::Clamp(moveInfoS1_.speed + moveInfoS1_.acceleration, moveInfoS1_.maxSpd_, 0.0f);
		// X軸のボスとプレイヤーの距離が速度より近いなら速度を変更
		if (fabsf(boss2PlayerVec.x) <= moveInfoS1_.speed) moveInfoS1_.speed = fabsf(boss2PlayerVec.x);
		boss2PlayerVec.normalize();
		// 座標の変更
		info->position += boss2PlayerVec * moveInfoS1_.speed * timeMgr->GetGameDeltaTime();
	}

	// 震える
	else if (attackStage_ == 2) {
		// シェイク処理
		shakeTime_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 時間を超えたらリセット
		if (shakeTime_.GetIsExceeded()) {
			shakeTime_.elapsedTime = 0.0f;
			shakeDir_ *= -1.0f;
			// 座標の設定
			info->shakeOffset = shakeDir_;
		}

		// 時間の加算
		stage2Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 時間を超えたら次の段階へ
		if (stage2Time_.GetIsExceeded()) {
			info->shakeOffset = Vector2();
			attackStage_++;
			// ダメージの変更
			info->collider.Data_Remove("Damage");
			info->collider.Data_Add("Damage", 30.0f);
		}
	}

	// 突進
	else if (attackStage_ == 3) {
		// ボスが床と衝突していたら
		if (info->isGroundCol)
		{
			attackStage_++;
			presetTargetPos_ = info->position;
			targetPos_ = info->position;
			targetPos_.y = 400.0f;
			// ダメージの変更
			info->collider.Data_Remove("Damage");
			info->collider.Data_Add("Damage", 5.0f);
			// シェイク設定
			info->cameraPtr->SetShake(Vector2(10.0f, 10.0f), 1.0f);
			return;
		}

		// 突進処理
		diveInfo_.speed += diveInfo_.acceleration * timeMgr->GetGameDeltaTime();
		diveInfo_.speed = Util::Clamp(diveInfo_.speed, diveInfo_.maxSpd_, 0.0f);
		info->position += diveInfo_.derection * diveInfo_.speed;
	}

	// 待機
	else if (attackStage_ == 4)
	{
		// 時間の加算
		stage4Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 時間を超えたら次の段階へ
		if (stage4Time_.GetIsExceeded())
		{
			info->shakeOffset = Vector2();
			attackStage_++;
		}
	}

	// 規定の位置までもどる
	else if (attackStage_ == 5)
	{
		// 時間の加算
		stage5Time_.elapsedTime += timeMgr->GetGameDeltaTime();
		// 座標移動
		float rate = stage5Time_.GetElapsedRatio();
		info->position.x = Easing::Quint::easeOut(presetTargetPos_.x, targetPos_.x, rate);
		info->position.y = Easing::Quint::easeOut(presetTargetPos_.y, targetPos_.y, rate);
		// 時間を超えたら次の段階へ
		if (stage5Time_.GetIsExceeded())
		{
			attackStage_++;
			isAttackEnd_ = true;
		}
	}
}

void DescentDiveState::Finalize(SubBossInfo* info)
{
	info = info;
}