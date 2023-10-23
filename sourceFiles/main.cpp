#include "main.h"
#include "../GameMain.h"

// 開始
int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
	SetOutApplicationLogValidFlag(FALSE);          // DxLib の Log.txt 自動生成をしない
	SetMainWindowText(APP_NAME);                   // ウィンドウタイトルを設定
	SetMainWindowClassName(APP_NAME);              // 他のDxLibと競合しないようにウィンドウクラスを設定
	ChangeWindowMode(TRUE);                        // ウインドウモードで起動
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ
	if (DxLib_Init() == -1) return -1;             // DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);                 // 描画先画面を裏にする（ダブルバッファリング）

	// シーンマネージャーオブジェクトを作成し、シーンを割り当て
	SceneManager* sceneMng = new SceneManager((Scene*) new Title());

	// FPSコントローラーを設定
	FPSCtrl::SetLimitRate(SCREEN_FPS);
	FPSCtrl::SetUpdateInterval(1000);

	// ゲームループし、シーンマネジャーでシーンの更新
	while ((ProcessMessage() == 0) && (sceneMng->update() != nullptr)) {
		ClearDrawScreen();

		// コントローラーとキーボード入力の更新
		InputCtrl::Update();

		// FPSコントローラーで固定
		FPSCtrl::Limit();
		FPSCtrl::Update();

		// シーンマネジャーでシーンの描画開始
		sceneMng->draw();

		// デバッグ - Dキーで切り替え
		/*if (InputCtrl::GetKeyState(KEY_INPUT_D) == PRESSED && InputCtrl::GetKeyState(KEY_INPUT_M) == PRESS) {
			if (Main::debugMode == 0)      Main::debugMode = 1;
			else if (Main::debugMode == 1) Main::debugMode = 2;
			else if (Main::debugMode == 2) Main::debugMode = 0;
		};

		// デバッグ - FPS 表示
		if (Main::debugMode) {
			SetFontSize(16);
			DrawFormatString(10, 10, 0xffffff, "FPS : %0.0f / %d", FPSCtrl::Get(), Main::fps);
		};*/
		
		ScreenFlip();
    };

	DxLib_End();
	return 0;
};