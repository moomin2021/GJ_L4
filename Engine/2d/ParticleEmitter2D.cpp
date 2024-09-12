#include "ParticleEmitter2D.h"
#include "DX12Cmd.h"
#include "Texture.h"
#include "Easing.h"
#include "ImGuiManager.h"
#include "Util.h"

#include <cassert>
#include <DirectXMath.h>

Camera* ParticleEmitter2D::sCamera_ = nullptr;

void ParticleEmitter2D::Initialize(const Vector2& arg_EmitCenter_, const Vector2& arg_EmitLength_, uint16_t arg_textureHandle)
{
    // インスタンス取得
    ptr_timeManager_ = TimeManager::GetInstance();

    CreateConstBuff();	// 定数バッファ生成
    CreateVertexBuff();	// 頂点バッファ生成
    CreateIndexBuff();	// インデックスバッファ生成

    // 
    emit_center_ = arg_EmitCenter_;
    emit_length_ = arg_EmitLength_;
    textureHandle_ = arg_textureHandle;

    sprite_ = std::make_unique<Sprite>();
}

void ParticleEmitter2D::Update()
{
    for (auto it = particles_.begin(); it!= particles_.end();)
    {
        // 生存確認
        if ((*it)->isAlive == false)
        {
            // 消す
            (*it).reset();
            it = particles_.erase(it);
            continue;
        }

        // 時間更新
        (*it)->time_toCurrent += ptr_timeManager_->GetDeltaTime();
        if ((*it)->time_toCurrent >= (*it)->time_toDead) { (*it)->isAlive = false; } // 次フレームで削除
    }

		//// スケールの更新
		//float elapsed = it.time_toCurrent / it.time_toDead;
		//elapsed = Util::Clamp(elapsed, 1.0f, 0.0f);
		//it.scale_current = Easing::lerp(it.scale_start, it.scale_end, elapsed);
}

void ParticleEmitter2D::MatUpdate()
{
	// 関数が成功したかどうかを判別する用変数
	HRESULT result;

	// 頂点バッファへデータ転送
	Vertex* vertMap = nullptr;
	result = vertexBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		// パーティクルの情報を1つずつ反映
		for (auto& it : particles_) {
			// 座標
			vertMap->pos = Vector3(it->position.x, it->position.y, 0.0f);
			vertMap->scale = it->scale_current;

			vertMap++;
		}

		vertexBuff_->Unmap(0, nullptr);
	}

#pragma region ワールド行列計算
	// 行列初期化
	Matrix4 matWorld = Matrix4Identity();

	// ワールド行列に平行移動を反映
    Vector3 pos = { emit_center_.x, emit_center_.y, 0.f };
	matWorld *= Matrix4Translate(pos);

#pragma endregion

#pragma region 定数バッファへのデータ転送
	// 行列
	constMap_->matWorld = matWorld;
	constMap_->matProj = sCamera_->GetMatOrthoGraphicPro();
#pragma endregion
}

void ParticleEmitter2D::ImGuiUpdate()
{
	ImGuiManager* imgui = ImGuiManager::GetInstance();

	imgui->BeginWindow("Particle");

	for (auto& it : particles_) imgui->Text("scale = %f", it->scale_current);
	for (auto& it : particles_) imgui->Text("現在の時間 = %f", it->time_toCurrent);

	imgui->EndWindow();
}

void ParticleEmitter2D::Draw()
{
	// コマンドリスト取得
	ID3D12GraphicsCommandList* cmdList = DX12Cmd::GetInstance()->GetCmdList();

	// インスタンス取得
	Texture* tex = Texture::GetInstance();

	// SRVヒープのハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE srvGPUHandle = tex->GetGPUDescriptorHandle(DescSIZE::SRV, textureHandle_);

	// 指定されたSRVをルートパラメータ1番に設定
	cmdList->SetGraphicsRootDescriptorTable(0, srvGPUHandle);

	// 定数バッファビュー（CBV）の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(1, constBuff_->GetGPUVirtualAddress());

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vertexView_);

	// インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&indexView_);

	// 描画コマンド
	cmdList->DrawInstanced(static_cast<UINT>(std::distance(particles_.begin(), particles_.end())), 1, 0, 0);
}

void ParticleEmitter2D::Finalize()
{
	particles_.clear();
}

void ParticleEmitter2D::AddParticle(std::unique_ptr<Particle> instance)
{
    particles_.push_back(std::move(instance));
}

void ParticleEmitter2D::CreateConstBuff()
{
	// 関数が成功したかどうかを判別する用変数
	HRESULT result;

	// デバイス取得
	ID3D12Device* device = DX12Cmd::GetInstance()->GetDevice();

#pragma region 定数バッファ生成
	// 定数バッファのヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};		// ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用

	// 定数バッファのリソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
#pragma endregion

#pragma region 定数バッファへのデータ転送
	result = constBuff_->Map(0, nullptr, (void**)&constMap_);
	assert(SUCCEEDED(result));
#pragma endregion
}

void ParticleEmitter2D::CreateVertexBuff()
{
	// デバイス取得
	ID3D12Device* device = DX12Cmd::GetInstance()->GetDevice();

	// 関数実行の成否を判別用の変数
	HRESULT result;

	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * MAX_VERTEX);

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};		// ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	result = device->CreateCommittedResource(
		&heapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBuff_));
	assert(SUCCEEDED(result));

	// 頂点バッファビューの作成
	vertexView_.BufferLocation = vertexBuff_->GetGPUVirtualAddress();// GPU仮想アドレス
	vertexView_.SizeInBytes = sizeVB;				// 頂点バッファのサイズ
	vertexView_.StrideInBytes = sizeof(Vertex);	// 頂点1つ分のデータサイズ
}

void ParticleEmitter2D::CreateIndexBuff()
{
	// デバイス取得
	ID3D12Device* device = DX12Cmd::GetInstance()->GetDevice();

	// 関数実行の成否を判別用の変数
	HRESULT result;

	// インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * 6);

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};		// ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// インデックスバッファの生成
	result = device->CreateCommittedResource(
		&heapProp,// ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,// リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff_)
	);

	// インデックスバッファビュー作成
	indexView_.BufferLocation = indexBuff_->GetGPUVirtualAddress();
	indexView_.Format = DXGI_FORMAT_R16_UINT;
	indexView_.SizeInBytes = sizeIB;

	// インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;
	result = indexBuff_->Map(0, nullptr, (void**)&indexMap);
	assert(SUCCEEDED(result));

	// インデックス情報を送信
	indexMap[0] = 0;
	indexMap[1] = 1;
	indexMap[2] = 2;
	indexMap[3] = 2;
	indexMap[4] = 1;
	indexMap[5] = 3;

	// マッピング解除
	indexBuff_->Unmap(0, nullptr);
}