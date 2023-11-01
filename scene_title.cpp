#include "main.h"

//コンストラクタ
Title::Title()
{
	TitleImage = LoadGraph("resources/images/Title.png");
	/*g_MenuNumber = 0;
	interval = 0.7f;*/
	cursor = LoadGraph("resources/images/cursor.png");
	state = 0;
	Ctrl = false;
}

//更新
Scene*Title::update()
{
	InputCtrl::Update();
	InputCtrl::GetStickRatio(L).y;
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		if (state == 0) {
			return new GameMain;
		}
		if (state == 1) {
			return new Help;
		}
		if (state == 2) {
			return new Credit;
		}
		if (state == 3) {
			return new End;
		}
	}

	//十字キー下ボタンでカーソルを下に
	if (frameCounter++ % 40 == 0)state++;
	if ((state % 10) >= 8)state -= 8;


	if (((InputCtrl::GetStickState(L).y < 0.4f) && (InputCtrl::GetStickState(L).y > -0.4f))) Ctrl = true;
	if ((InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_UP) == PRESS) || ((InputCtrl::GetStickState(L).y >= 0.8f) && Ctrl)){
		if (state < 10) state += 40;
		else state -= 10;
			Ctrl = false;
	}
	else if((InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == PRESS) || (((InputCtrl::GetStickState(L).y <= -0.8f) && Ctrl))){
		if (state >= 40) state -= 40;
		else state += 10;
			Ctrl = false;
	}
	
	return this;
}

//描画
void Title::draw() const
{
	DrawGraph(0, 0, TitleImage, TRUE);
	SetFontSize(100);
	DrawString(400, 150, "タイトル名", 0x000000);
	SetFontSize(75);
	DrawString(550, 300, "Start", 0x000000);
	DrawString(550, 370, "Help", 0x000000);
	DrawString(550, 440, "Credit", 0x000000);
	DrawString(550, 510, "End", 0x000000);

	DrawGraph(470, 290 + state, cursor, TRUE);

}