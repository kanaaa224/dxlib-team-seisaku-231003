//////////////////////////////////////////////////
// デバッグ シーン
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

DebugScene::DebugScene() {
	state = 0;
};

DebugScene::~DebugScene() {};

Scene* DebugScene::update() {
	//if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new TitleScene(false);

	     if (InputCtrl::GetKeyState(KEY_INPUT_0) == PRESS) FPSCtrl::SetLimitRate(10);
	else if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) FPSCtrl::SetLimitRate(30);
	else if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) FPSCtrl::SetLimitRate(60);
	else if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) FPSCtrl::SetLimitRate(120);
	else if (InputCtrl::GetKeyState(KEY_INPUT_4) == PRESS) FPSCtrl::SetLimitRate(240);

	//     if (InputCtrl::GetKeyState(KEY_INPUT_UP)   == PRESS) state++;
	//else if (InputCtrl::GetKeyState(KEY_INPUT_DOWN) == PRESS) state--;
		 
		 if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) == PRESS)   return new GameScene();
		 if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS) return new GameScene();

		 if (InputCtrl::GetKeyState(KEY_INPUT_L) == PRESS) return new LoadScene();

	return this;
};

void DebugScene::draw() const {
	SetFontSize(16);

	int x = 20,
		y = 50;

	//////////////////////////////////////////////////

	DrawFormatString(x, y, 0xffffff, "FPSCtrlクラス の動作テスト");

	x += 20;

	y += 30;
	DrawFormatString(x, y, 0xffffff, "FPSを変更 -> 0キー:10 / 1キー:30 / 2キー:60 / 3キー:120 / 4キー:240");

	y += 30;
	DrawFormatString(x, y, 0xffffff, "FPS: %.1f", FPSCtrl::Get());

	x -= 20;

	//////////////////////////////////////////////////

	y += 50;
	DrawFormatString(x, y, 0xffffff, "InputCtrlクラス の動作テスト");

	x += 20;

	y += 30;
	DrawFormatString(x, y, 0xffffff, "Spaceキー の状態:");

	x += 20;

	y += 15;
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS) {
		DrawFormatString(x, y, 0xffffff, "押されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "押されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESSED) {
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == RELEASE) {
		DrawFormatString(x, y, 0xffffff, "離されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "離されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	x -= 20;

	//////////////////////////////////////////////////
	
	y += 30;
	DrawFormatString(x, y, 0xffffff, "マウス の状態:");

	x += 20;

	y += 15;
	if (InputCtrl::GetMouseState(L) == PRESS) {
		DrawFormatString(x, y, 0xffffff, "押されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "押されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetMouseState(L) == PRESSED) {
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetMouseState(L) == RELEASE) {
		DrawFormatString(x, y, 0xffffff, "離されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "離されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 30;
	DrawFormatString(x, y, 0xffffff, "カーソル位置: X %d - Y %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);

	x -= 20;

	//////////////////////////////////////////////////

	y += 30;
	DrawFormatString(x, y, 0xffffff, "コントローラー Aボタン の状態:");

	x += 20;
	y += 15;
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		DrawFormatString(x, y, 0xffffff, "押されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "押されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESSED) {
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "まだ押されています");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	y += 15;
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == RELEASE) {
		DrawFormatString(x, y, 0xffffff, "離されました");
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawFormatString(x, y, 0xffffff, "離されました");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	x -= 20;

	y += 30;
	DrawFormatString(x, y, 0xffffff, "コントローラー L Stick の傾き割合: X %.5f - Y %.5f", InputCtrl::GetStickRatio(L).x, InputCtrl::GetStickRatio(L).y);

	y += 30;
	DrawFormatString(x, y, 0xffffff, "コントローラー L Stick の傾き: X %.1f - Y %.1f", InputCtrl::GetStickState(L).x, InputCtrl::GetStickState(L).y);

	x -= 20;

	//////////////////////////////////////////////////

	y += 50;
	DrawFormatString(x, y, 0xffffff, "Enterキー/Bボタン で仮のゲームメインシーンへ");

	y += 50;
	DrawFormatString(x, y, 0xffffff, "Lキー でロード画面付きで仮のゲームメインシーンへ");

	//y += 50;
	//if(InputCtrl::GetStickRatio(L).x) DrawFormatString(x, y, 0xffffff, "aaaaaaa");
};