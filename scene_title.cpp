#include "main.h"

//コンストラクタ
Title::Title()
{
	TitleImage = LoadGraph("resources/images/Title.png");
	g_MenuNumber = 0;
	/*interval = 0.7f; */
	cursor = LoadGraph("resources/images/cursor.png");
	//state = 10;
	Ctrl = false;
}

//更新
Scene*Title::update()
{
	//スティックの制限
	if (frameCounter++ % 40 == 0);
	if ((g_MenuNumber % 10) >= 8)g_MenuNumber -= 8;

	//タイトルカーソルの移動量
	if (((InputCtrl::GetStickState(L).y < 0.5f) && (InputCtrl::GetStickRatio(L).y > -0.5f))) Ctrl = true;
	if ((InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_UP) == PRESS) || ((InputCtrl::GetStickRatio(L).y >= 1.0f) && Ctrl)){
		if (g_MenuNumber < 10) g_MenuNumber += 200;
		else g_MenuNumber -= 50;
			Ctrl = false;
	}
	else if((InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == PRESS) || (((InputCtrl::GetStickRatio(L).y <= -1.0f) && Ctrl))){
		if (g_MenuNumber >= 200) g_MenuNumber -= 200;
		else g_MenuNumber += 50;
			Ctrl = false;
	}
	//Aボタンでメニュー決定・画面遷移
	else if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		if (g_MenuNumber == 0) {
			return new GameScene;
		}
		if (g_MenuNumber == 1) {
			return new Help;
		}
		if (g_MenuNumber == 2) {
			return new Credit;
		}
		if (g_MenuNumber == 3) {
			return new End;
		}
	}
	
	return this;
}

//描画
void Title::draw() const
{
	//タイトル背景の描画
	DrawGraph(0, 0, TitleImage, TRUE);
	//タイトル名の表示
	SetFontSize(100);
	DrawString(400, 150, "タイトル名", 0x000000);
	//タイトルメニューの表示
	SetFontSize(55);
	DrawString(550, 320, "Start", 0x000000);
	DrawString(550, 370, "Help", 0x000000);
	DrawString(550, 420, "Credit", 0x000000);
	DrawString(550, 470, "End", 0x000000);

	//タイトルカーソルの描画
	DrawGraph(470, 290 + g_MenuNumber, cursor, TRUE);

}