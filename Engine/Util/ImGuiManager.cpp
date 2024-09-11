#include "ImGuiManager.h"
#include "WinAPI.h"
#include "DX12Cmd.h"
#include "Texture.h"

#include <imgui_impl_win32.h>
#include <imgui_impl_DX12.h>

#include <cassert>

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager inst;
	return &inst;
}

void ImGuiManager::Initialize()
{
	// インスタンス取得
	WinAPI* winAPI = WinAPI::GetInstance();
	DX12Cmd* dx12 = DX12Cmd::GetInstance();

	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	// デスクリプタヒープ生成
	HRESULT result;
	result = dx12->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	// ImGuiのコンテキストを生成
	ImGui::CreateContext();

	// ImGuiのスタイルを設定
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(winAPI->GetHWND());

	ImGui_ImplDX12_Init(dx12->GetDevice(), static_cast<uint32_t>(dx12->GetBackBufferNum()), DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		srvHeap_.Get(), srvHeap_->GetCPUDescriptorHandleForHeapStart(), srvHeap_->GetGPUDescriptorHandleForHeapStart());

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 18.0f, &config, io.Fonts->GetGlyphRangesJapanese());
}

void ImGuiManager::Begin()
{
	// ImGuiフレーム開始
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	// 描画前準備
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DX12Cmd::GetInstance()->GetCmdList();

	// デスクリプタヒープの配列をセットするコマンド
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get()};
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// 描画コマンドを発行
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);
}

void ImGuiManager::BeginWindow(const std::string& winName)
{
	ImGui::Begin(winName.c_str());
}

void ImGuiManager::EndWindow()
{
	ImGui::End();
}

bool ImGuiManager::BeginMenuBar()
{
	return ImGui::BeginMenuBar();
}

void ImGuiManager::EndMenuBar()
{
	ImGui::EndMenuBar();
}

bool ImGuiManager::BeginMenu(const std::string& menuName, bool enable)
{
	return ImGui::BeginMenu(menuName.c_str(), enable);
}

void ImGuiManager::EndMenu()
{
	ImGui::EndMenu();
}

bool ImGuiManager::MenuItem(const std::string& label)
{
	return ImGui::MenuItem(label.c_str());
}

void ImGuiManager::InputInt(const std::string& label, int& v)
{
	ImGui::InputInt(label.c_str(), &v);
}

void ImGuiManager::InputInt(const std::string& label, int& v, int step, int step_fast)
{
	ImGui::InputInt(label.c_str(), &v, step, step_fast);
}

void ImGuiManager::InputFloat(const std::string& label, float& v)
{
	ImGui::InputFloat(label.c_str(), &v);
}

void ImGuiManager::InputFloat(const std::string& label, float& v, float step, float step_fast)
{
	ImGui::InputFloat(label.c_str(), &v, step, step_fast);
}

void ImGuiManager::InputVector2(const std::string& label, Vector2& v)
{
	float value[2] = { v.x, v.y };
	ImGui::InputFloat2(label.c_str(), value);
	v = { value[0], value[1] };
}

void ImGuiManager::InputVector3(const std::string& label, Vector3& v)
{
	float value[3] = { v.x, v.y, v.z };
	ImGui::InputFloat3(label.c_str(), value);
	v = { value[0], value[1], value[2] };
}

bool ImGuiManager::CheckBox(const std::string& label, bool& flag)
{
	return ImGui::Checkbox(label.c_str(), &flag);
}

bool ImGuiManager::BeginTabBar(const std::string& tab_id)
{
	return ImGui::BeginTabBar(tab_id.c_str());
}

void ImGuiManager::EndTabBar()
{
	ImGui::EndTabBar();
}

bool ImGuiManager::BeginTabItem(const std::string& label)
{
	return ImGui::BeginTabItem(label.c_str());
}

void ImGuiManager::EndTabItem()
{
	ImGui::EndTabItem();
}

bool ImGuiManager::Button(const std::string& label)
{
	return ImGui::Button(label.c_str());
}

bool ImGuiManager::Button(const std::string& label, const Vector2& size)
{
	return ImGui::Button(label.c_str(), {size.x, size.y});
}

bool ImGuiManager::BeginCombo(const std::string& label, const std::string& previewValue)
{
	return ImGui::BeginCombo(label.c_str(), previewValue.c_str());
}

bool ImGuiManager::Selectable(const std::string& label, bool selected)
{
	return ImGui::Selectable(label.c_str(), selected);
}

void ImGuiManager::SetItemDefaultFocus()
{
	ImGui::SetItemDefaultFocus();
}

void ImGuiManager::EndCombo()
{
	ImGui::EndCombo();
}

void ImGuiManager::Text(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextV(fmt, args);
	va_end(args);
}

ImGuiManager::ImGuiManager() {}

ImGuiManager::~ImGuiManager()
{
	// 後始末
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	srvHeap_.Reset();
}
