#include "DrawHelp.h"
#include "DxLib.h"
#include "main.h"

DrawHelp::DrawHelp()
{
	HelpImage2 = LoadGraph("resources/images/Help2.png");
}

Scene* DrawHelp::update()
{
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new GameScene;
	}
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
	{
		return new Title;
	}
	// 文字の表示(点滅)
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press [SPACE] Key  --", 0xFF0000);
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
	return this;
}

void DrawHelp::draw() const
{
	DrawGraph(0, 0, HelpImage2, TRUE);
	SetFontSize(40);
	DrawString(520, 670, "Aボタン：スタート", 0xff0000);
	DrawString(900, 670, "Bボタン：タイトル", 0xff0000);
}
