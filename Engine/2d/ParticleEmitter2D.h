#pragma once
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "TimeManager.h"

#include <d3d12.h>
#include <wrl.h>
#include "Sprite.h"
#include <list>

struct SettingParticleEmitter {

};

// パーティクル1粒
struct Particle {
    Vector2 position{}; //座標
    bool isAlive{};
    bool isDraw{};

    float time_toCurrent{}; // 生成->現在までの時間
    float time_toDead{};    // 生成->死ぬまでの時間（余命）

    float scale_current{};  // スケール - 現在
    float scale_start{};    // スケール - 最初
    float scale_end{};      // スケール - 最後

    float alpha{};
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
#pragma endregion

#pragma region メンバ変数
private:
	// カメラ
	static Camera* sCamera_;

	// インスタンス
	TimeManager* ptr_timeManager_ = nullptr;

	// 最大頂点数
	const uint16_t MAX_VERTEX = 1024;

    // 発生範囲の中心座標
    Vector2 emit_center_{};
    // 発生範囲の大きさ
    Vector2 emit_length_{};

	// パーティクルコンテナ
	std::list<std::unique_ptr<Particle>> particles_;
	// テクスチャハンドル
	uint16_t textureHandle_ = 0;
    // スプライト(パーティクル描画用)
    std::unique_ptr<Sprite> sprite_{};

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
    ParticleEmitter2D(void) = default;
    ~ParticleEmitter2D(void) = default;

	// 基本処理
	void Initialize(const Vector2& arg_EmitCenter_, const Vector2& arg_EmitLength_, uint16_t arg_textureHandle);
	void Update();
	void MatUpdate();
	void ImGuiUpdate();
	void Draw();
	void Finalize();

	// パーティクルの追加
	void AddParticle(std::unique_ptr<Particle> instance);

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
    void SetPosition(const Vector2& inPos) { emit_center_ = inPos; }
#pragma endregion
};