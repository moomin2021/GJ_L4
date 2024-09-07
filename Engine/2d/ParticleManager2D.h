#pragma once
#include "ParticleEmitter2D.h"

#include <vector>

class ParticleManager2D
{
#pragma region メンバ変数
private:
	std::vector<ParticleEmitter2D> emitter_ = {};
#pragma endregion

#pragma region メンバ関数
public:
	// インスタンス取得
	static ParticleManager2D* GetInstance();

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void DrawBack();
	void DrawFront();

private:
	// コンストラクタとデストラクタ
	ParticleManager2D() {}
	~ParticleManager2D() {}
#pragma endregion

#pragma region 特殊関数
public:
	ParticleManager2D(const ParticleManager2D&) = delete;				// コピーコンストラクタ禁止
	ParticleManager2D& operator = (const ParticleManager2D&) = delete;	// コピー代入演算子禁止
#pragma endregion
};