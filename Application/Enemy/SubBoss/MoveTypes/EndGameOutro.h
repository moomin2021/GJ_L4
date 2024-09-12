#pragma once
#include "SubBossMoveState.h"

class EndGameOutro : public SubBossMoveState {
#pragma region メンバ変数
private:
	
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	EndGameOutro() {}
	~EndGameOutro() {}

	// 基本処理
	void Initialize(SubBossInfo* info) override;
	void Update(SubBossInfo* info) override;
	void Finalize(SubBossInfo* info) override;
#pragma endregion
};