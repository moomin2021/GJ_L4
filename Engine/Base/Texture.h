#pragma once
#include <d3d12.h>
#include <DirectXTex.h>
#include <wrl.h>
#include <string>
#include <map>

enum class DescSIZE : uint8_t {
	SRV = 0,
	RTV = 1,
	DSV = 2,
};

class Texture {
private:
	// エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
#pragma region メンバ変数
private:
	// 読み込んだ回数
	uint16_t indexCounter_ = 0;

	std::vector<uint32_t> descSize_ = {};

	// テクスチャバッファ
	std::map<const std::string, ComPtr<ID3D12Resource>> texBuff_;

	// テクスチャハンドル
	std::map<const std::string, uint16_t> texIndex_;

	std::map<uint16_t, const std::string> texName_;

	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;

	std::vector<ID3D12Resource*> intermediateResources_;
#pragma endregion

#pragma region メンバ関数
public:
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns> インスタンス </returns>
	static Texture* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	// 画像イメージを読み取る
	void LoadImageFile(const std::string filePath, DirectX::ScratchImage& scratchImage, DirectX::TexMetadata& metadata);

	// テクスチャバッファを生成
	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata, D3D12_RESOURCE_DESC& texResourceDesc);

	// テクスチャバッファにデータを転送
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
	/// <summary>
	/// テクスチャを読み込み、ハンドルを取得する
	/// </summary>
	/// <param name="fileName"> 画像ファイル名 </param>
	/// <returns> 読み込んだ画像のハンドル </returns>
	uint16_t LoadTexture(const std::string fileName);

	/// <summary>
/// テクスチャを分割して読み込み、ハンドルを取得する
/// </summary>
/// <param name="fileName"> 画像ファイル名 </param>
/// <param name="xNum"> 画像の横向きに対する分割数 </param>
/// /// <returns> 読み込んだ画像のハンドル </returns>
	std::vector<uint16_t> LoadDivTexture(const std::string& fileName, int16_t xNum);

	void ReleaseIntermediateResources();

	uint16_t GetIndex();

#pragma region ゲッター関数
public:
	/// <summary>
	/// SRVデスクリプタヒープの取得
	/// </summary>
	/// <returns> SRVデスクリプタヒープ </returns>
	ID3D12DescriptorHeap* GetSRVHeap() { return srvHeap_.Get(); }

	ID3D12Resource* GetTexBuffer(uint16_t texHandle) { return texBuff_[texName_[texHandle]].Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(DescSIZE size, uint16_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(DescSIZE size, uint16_t index);
#pragma endregion

private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Texture();

	/// <summary>
	/// SRV用でスクリプタヒープ生成
	/// </summary>
	void CreateDescriptorHeap();

#pragma endregion

#pragma region 特殊関数
	// 禁止
	Texture(const Texture&) = delete;				// コピーコンストラクタ禁止
	Texture& operator = (const Texture&) = delete;	// コピー代入演算子禁止
#pragma endregion
};

/// <summary>
/// テクスチャを読み込み、ハンドルを取得する
/// </summary>
/// <param name="fileName"> 画像ファイル名 </param>
/// <returns> 読み込んだ画像のハンドル </returns>
uint16_t LoadTexture(const std::string fileName);

/// <summary>
/// テクスチャを分割して読み込み、ハンドルを取得する
/// </summary>
/// <param name="fileName"> 画像ファイル名 </param>
/// <param name="xNum"> 画像の横向きに対する分割数 </param>
/// /// <returns> 読み込んだ画像のハンドル </returns>
std::vector<uint16_t> LoadDivTexture(const std::string& fileName, int16_t xNum);