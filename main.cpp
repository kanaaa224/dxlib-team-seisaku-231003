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
	SetAlwaysRunFlag(TRUE);							//常にアクティブ状態にする

	SoundManager::CreateSoundManager();

	SceneManager* sceneMng = new SceneManager((Scene*) new Title());

	FPSCtrl::SetLimitRate(SCREEN_FPS);
	FPSCtrl::SetUpdateInterval(1000);

	// ゲームループ＆シーンの更新
	while ((ProcessMessage() == 0) && (sceneMng->update() != nullptr)) {
		ClearDrawScreen();

		if ((GetMainWindowHandle() == GetForegroundWindow()))
		{
			InputCtrl::Update();
		}

		FPSCtrl::Limit();
		FPSCtrl::Update();

		sceneMng->draw();

		//////////////////////////////////////////////////
		// 仮
		SetFontSize(16);
		DrawFormatString(10, 10, 0xffffff, "FPS: %0.0f", FPSCtrl::Get());

		if (InputCtrl::GetButtonState(XINPUT_BUTTON_BACK)) break; // 強制終了
		//////////////////////////////////////////////////
		
		ScreenFlip();
    };

	SoundManager::DeleteSoundManager();

	DxLib_End();
	return 0;
};