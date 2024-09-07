#pragma once
#include "fMath.h"
#include <wrl.h>
#include <d3d12.h>
#include <string>

class ImGuiManager
{
private:
	// エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

#pragma region メンバ変数
private:
	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
#pragma endregion

#pragma region メンバ関数
public:
	// インスタンス取得
	static ImGuiManager* GetInstance();

	// 初期化処理
	void Initialize();

	// ImGui受付開始
	void Begin();

	// ImGui受付終了
	void End();

	// 画面への描画
	void Draw();

#pragma region Window
	/// <summary>
	/// ウィンドウの開始
	/// </summary>
	/// <param name="winName"> ウィンドウの名前 </param>
	void BeginWindow(const std::string& winName);
	/// <summary>
	/// ウィンドウの終了
	/// </summary>
	void EndWindow();
#pragma endregion
	
#pragma region Menu
	/// <summary>
	/// メニューバーの開始
	/// </summary>
	/// <returns> 作成できたか </returns>
	bool BeginMenuBar();
	/// <summary>
	/// メニューバーの終了
	/// </summary>
	void EndMenuBar();

	/// <summary>
	/// メニューの開始
	/// </summary>
	/// <param name="menuName"> メニューの名前 </param>
	/// <param name="enable"> 有効化(デフォルトではTRUE)(FALSEなら選択できなくなる) </param>
	/// <returns> メニューを開いているか </returns>
	bool BeginMenu(const std::string& menuName, bool enable = true);
	/// <summary>
	/// メニューの終了
	/// </summary>
	void EndMenu();

	/// <summary>
	/// メニュー項目の作成
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <returns> 選択されているか </returns>
	bool MenuItem(const std::string& label);
#pragma endregion

#pragma region Input
	/// <summary>
	/// 整数値の入力
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="v"> 入力される整数値の参照 </param>
	void InputInt(const std::string& label, int& v);
	/// <summary>
	/// 整数値を入力(上下ボタンあり)
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="v"> 入力される整数値の参照 </param>
	/// <param name="step"> 上下ボタンで増減させる時の増分値 </param>
	/// <param name="step_fast"> [Shift]キーを押しながら上下ボタンを押した時の増減値 </param>
	void InputInt(const std::string& label, int& v, int step = 1, int step_fast = 10);

	/// <summary>
	/// 浮動小数点数の入力
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="v"> 入力される浮動小数点数 </param>
	void InputFloat(const std::string& label, float& v);
	/// <summary>
	/// 浮動小数点数の入力(上下ボタンあり)
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="v"> 入力される浮動小数点数 </param>
	/// <param name="step"> 上下ボタンで増減させる時の増分値 </param>
	/// <param name="step_fast"> [Shift]キーを押しながら上下ボタンを押した時の増減値 </param>
	void InputFloat(const std::string& label, float& v, float step = 1.0f, float step_fast = 10.0f);

	/// <summary>
	/// Vector2の入力
	/// </summary>
	/// <param name="lavel"> 表示ラベル </param>
	/// <param name="v"> 入力されるVector2の参照 </param>
	void InputVector2(const std::string& label, Vector2& v);

	/// <summary>
	/// Vector3の入力
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="v"> 入力されるVector3の参照 </param>
	void InputVector3(const std::string& label, Vector3& v);

	/// <summary>
	/// チェックボックスの作成
	/// </summary>
	/// <param name="label"> 表示ラベル </param>
	/// <param name="flag"> BOOL型変数の参照 </param>
	/// <returns></returns>
	bool CheckBox(const std::string& label, bool& flag);
#pragma endregion

	/// <summary>
	/// テキストの表示
	/// </summary>
	/// <param name="fmt"> 表示するテキスト </param>
	/// <param name=""></param>
	void Text(const char* fmt, ...);

private:
	// コンストラクタ
	ImGuiManager();

	// デストラクタ
	~ImGuiManager();
#pragma endregion

#pragma region 特殊関数
	// 禁止
	ImGuiManager(const ImGuiManager&) = delete;				// コピーコンストラクタ禁止
	ImGuiManager& operator = (const ImGuiManager&) = delete;	// コピー代入演算子禁止
#pragma endregion
};

#pragma region Window
//	ウィンドウ名を指定してウィンドウを開始
//	BeginWindow("My Window");
//	
//	--ここにウィンドウ内の処理を書く--
//	
//	ウィンドウを正しく終了する
//	EndWindow();
#pragma endregion

#pragma region Menu
//	if (BeginMenuBar()) {
//		if (BeginMenu("File")) {
//			[action]にはそのメニューを開いている時の処理を書く
//			if (MenuItem("Open")) { action }
//			if (MenuItem("Save")) { action }
//			EndMenu();
//		}
//		EndMenuBar();
//	}
#pragma endregion