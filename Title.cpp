#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "sourceFiles/inputCtrl.h"
#include "Help.h"
#include "Credit.h"
#include "End.h"

//コンストラクタ
Title::Title()
{
	TitleImage = LoadGraph("resources/images/Title.png");
	g_MenuNumber = 0;
	interval = 0;
	cursor = LoadGraph("resources/images/cursor.png");
}

//デストラクタ
Title::~Title()
{

}

//更新
Scene*Title::update()
{
	InputCtrl::Update();
	InputCtrl::GetStickRatio(L).y;
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		if (g_MenuNumber == 0) {
			return new GameMain;
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

	//十字キー下ボタンでカーソルを下に移動
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == PRESS || InputCtrl::GetStickRatio(L).y>STICK_MAX && interval>=30)
	{
		if (++g_MenuNumber > 3)g_MenuNumber = 0;
	}
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_UP) == PRESS || InputCtrl::GetStickRatio(L).y<-STICK_MAX && interval>=30)
	{
		if (--g_MenuNumber < 0)g_MenuNumber = 3;
	}
	g_MenuY = g_MenuNumber * 65;

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

	DrawGraph(470, 290 + g_MenuY, cursor, TRUE);

}