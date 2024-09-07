#pragma once
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "TimeManager.h"

#include <d3d12.h>
#include <wrl.h>
#include <deque>

struct SettingParticleEmitter {

};

class ParticleEmitter2D
{
private:
	// エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
#pragma region 構造体
	// 頂点データ
	struct Vertex {
		Vector3 pos;
		float scale;
	};

	// 定数バッファ用
	struct ConstBufferData {
		Matrix4 matWorld;
		Matrix4 matProj;
	};

	// パーティクル1粒
	struct Particle {
		Vector2 position = {};	// 座標
		float nowTime = 0.0f;	// 生成されてからの生存時間
		float aliveTime = 0.0f;	// 生存時間
		float nowScale = 0.0f;	// 現在スケール
		float startScale = 1.0f;// 初期スケール
		float endScale = 1.0f;	// 最終スケール
	};
#pragma endregion

#pragma region メンバ変数
private:
	// カメラ
	static Camera* sCamera_;

	// インスタンス
	TimeManager* timeMgr_ = nullptr;

	// 最大頂点数
	const uint16_t MAX_VERTEX = 1024;

	// 発生座標
	Vector3 position_ = { 0.0f, 0.0f, 0.0f };

	// パーティクルコンテナ
	std::deque<Particle> particles_;

	// テクスチャハンドル
	uint16_t textureHandle_ = 0;

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff_ = nullptr;
	ConstBufferData* constMap_ = nullptr;

	// 頂点データ
	D3D12_VERTEX_BUFFER_VIEW vertexView_{};	// 頂点バッファービュー
	ComPtr<ID3D12Resource> vertexBuff_ = nullptr;		// 頂点バッファ

	// インデックスデータ
	D3D12_INDEX_BUFFER_VIEW indexView_{};	// インデックスバッファビュー
	ComPtr<ID3D12Resource> indexBuff_ = nullptr;	// インデックスバッファ
#pragma endregion

#pragma region メンバ関数
public:
	// コンストラクタとデストラクタ
	ParticleEmitter2D() {}
	~ParticleEmitter2D() {}

	// 基本処理
	void Initialize();
	void Update();
	void MatUpdate();
	void ImGuiUpdate();
	void Draw();
	void Finalize();

	// パーティクルの追加
	void AddParticle(const Vector2& inPos, float time, float startScale, float endScale);

private:
	void CreateConstBuff();	// 定数バッファ生成
	void CreateVertexBuff();// 頂点バッファ生成
	void CreateIndexBuff();	// インデックスバッファ生成
#pragma endregion

#pragma region セッター関数
public:
	/// <summary>
	/// カメラの設定
	/// </summary>
	/// <param name="camera"> カメラのポインタ </param>
	static void SetCamera(Camera* camera) { sCamera_ = camera; }

	/// <summary>
	/// テクスチャハンドルの設定
	/// </summary>
	/// <param name="handle"> ハンドル </param>
	void SetTextureHandle(uint16_t handle) { textureHandle_ = handle; }

	/// <summary>
	/// パーティクル発生座標の設定
	/// </summary>
	/// <param name="inPos"> 座標 </param>
	void SetPosition(const Vector2& inPos) { position_ = { inPos.x, inPos.y, 0.0f }; }
#pragma endregion
};