#include "main.h"

// 開始
int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
	//SetOutApplicationLogValidFlag(FALSE);          // DxLib の Log.txt 自動生成をしない
	SetMainWindowText(APP_NAME);                   // ウィンドウタイトルを設定
	SetMainWindowClassName(APP_NAME);              // 他の DxLib と競合しないようにウィンドウクラスを設定
	ChangeWindowMode(TRUE);                        // ウインドウモードで起動
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ
	if (DxLib_Init() == -1) return -1;             // DxLib の初期化処理
	SetDrawScreen(DX_SCREEN_BACK);                 // 描画先画面を裏にする（ダブルバッファリング）

	// シーンマネージャーオブジェクトを作成し、シーンを割り当て
	SceneManager* sceneMng = new SceneManager((Scene*) new GameScene());

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

		// 仮
		SetFontSize(16);
		DrawFormatString(10, 10, 0xffffff, "FPS: %0.0f", FPSCtrl::Get());
		
		ScreenFlip();
    };

	DxLib_End();
	return 0;
};