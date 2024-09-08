#pragma once
#include "BaseEnemy.h"
#include "EnemyStatus.h"

class FloatingEnemy : public BaseEnemy
{
#pragma region メンバ変数
private:
	// 敵関連
	EnemyStatus::State state_ = EnemyStatus::State::Normal;// 状態
	Vector2 position_ = Vector2();// 座標
	Vector2 size_ = Vector2(64.0f, 64.0f);// サイズ
	float rotation_ = 0.0f;// 回転角度
	Vector2 moveVec_ = Vector2();// 動く方向
	float moveSpd_ = 0.0f;// 移動速度
	float rotaSpd_ = 0.0f;// 回転速度

	// 一回目殴られた時に使う変数
	Vector2 firstBeatenVec_ = Vector2(0.0f, 1.0f);// 殴られた時の方向
	float firstBeatenMoveSpd_ = 20.0f;// 殴った時の移動速度
	float firstBeatenRotaSpd_ = 30.0f;// 殴った時の回転速度

	// ノックバックしている時に使う変数
	Vector2 knockVec_ = Vector2(0.0f, -1.0f);
	float knockFirstSpd_ = 20.0f;// ノックバックした時の最初の速度
	float knockAddSpd_ = 0.5f;// 徐々に加算される速度
	float knockFirstRotaSpd_ = 30.0f;// 最初の回転速度
	float knockAddRotaSpd_ = 0.75f;// 徐々に加算される回転速度
#pragma endregion

#pragma region メンバ関数
public:
	// 各基本処理
	void Initialize(const Vector2& inPos, uint16_t tex) override;
	void Update() override;
	void MatUpdate() override;
	void Draw() override;
	void Finalize() override;
	void ImGuiUpdate(ImGuiManager* imGuiMgrPtr) override;

private:
	// 状態別処理
	static void (FloatingEnemy::*stateTable[]) ();
	void Normal();
	void FirstBeaten();
	void KnockBack();
	void SecondBeaten();
#pragma endregion
};