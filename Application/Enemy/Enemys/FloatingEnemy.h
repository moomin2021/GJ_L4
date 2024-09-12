#pragma once
#include "BaseEnemy.h"
#include "EnemyStatus.h"
#include "M_CircleCollider.h"
#include "TimeManager.h"

class FloatingEnemy : public BaseEnemy
{
#pragma region メンバ変数
private:
	// インスタンス
	TimeManager* pTimeMgr_ = nullptr;
	Player* pPlayer_ = nullptr;

	// 敵関連
	size_t id_ = 0;
	EnemyStatus::State state_ = EnemyStatus::State::Normal;// 状態
	Vector2 position_ = Vector2();// 座標
	Vector2 size_ = Vector2(64.0f, 64.0f);// サイズ
	float rotation_ = 0.0f;// 回転角度
	float frontRotation_ = 0.0f;
	Vector2 moveVec_ = Vector2();// 動く方向
	float moveSpd_ = 0.0f;// 移動速度
	float rotaSpd_ = 0.0f;// 回転速度
	M_CircleCollider collider_;
	float color_ = 0.0f;
	float addColor_ = 0.8f;

	// 通常時に使う変数
	float normalRotaSpd_ = 50.0f;

	// 一回目殴られた時に使う変数
	Vector2 firstBeatenVec_ = Vector2(0.0f, 1.0f);// 殴られた時の方向
	float firstBeatenMoveSpd_ = 800.0f;// 殴った時の移動速度
	float firstBeatenRotaSpd_ = 800.0f;// 殴った時の回転速度

	// ノックバックしている時に使う変数
	Vector2 knockVec_ = Vector2(0.0f, -1.0f);
	float knockFirstSpd_ = 600.0f;// ノックバックした時の最初の速度
	float knockAddSpd_ = 300.0f;// 徐々に加算される速度
	float knockFirstRotaSpd_ = 600.0f;// 最初の回転速度
	float knockAddRotaSpd_ = 300.0f;// 徐々に加算される回転速度

	// 二回目殴られた時に使う変数
	Vector2 secondBeatenVec_ = Vector2(0.0f, 0.0f);// 殴られた時の方向
	float secondBeatenMoveSpd_ = 1000.0f;// 殴った時の移動速度
	float secondBeatenRotaSpd_ = 1000.0f;// 殴った時の回転速度

	// 時間
	float nowTime_ = 0.0f;
	float aliveTime_ = 4.0f;

    int32_t particleFrame_{};
#pragma endregion

#pragma region メンバ関数
public:
	// 各基本処理
	void Initialize(size_t id, const Vector2& inPos, std::vector<uint16_t> texs, M_ColliderManager* colMgrPtr, Player* playerPtr) override;
	void Update() override;
	void MatUpdate() override;
	void Draw() override;
	void Finalize() override;
	void ImGuiUpdate(ImGuiManager* imGuiMgrPtr) override;

private:
	// 衝突時のコールバック関数
	void CollisionCallBack();

	// 状態別処理
	static void (FloatingEnemy::*stateTable[]) ();
	void Normal();
	void FirstBeaten();
	void KnockBack();
	void SecondBeaten();
#pragma endregion
};