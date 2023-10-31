#include "Help.h"
#include "DxLib.h"
#include "Title.h"
#include "sourceFiles/inputCtrl.h"
#include "GameMain.h"

Help::Help()
{
	HelpImage1 = LoadGraph("resources/images/Help1.png");
	HelpImage2 = LoadGraph("resources/images/Help2.png");
}

Help::~Help()
{

}

Scene*Help::update()
{
	InputCtrl::Update();
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new GameMain;
	}
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
	{
		return new Title;
	}
	return this;
}

void Help::draw()const
{
		DrawGraph(0, 0, HelpImage1, TRUE);
		SetFontSize(50);
		DrawString(1100, 670, "Aボタン:次へ", 0xff0000);

		if (InputCtrl::GetButtonState(XINPUT_BUTTON_X))
		{
			DrawGraph(0, 0, HelpImage2, TRUE);
			SetFontSize(50);
			DrawString(400, 670, "Aボタン：スタート", 0xff0000);
			DrawString(850, 670, "Bボタン：タイトル", 0xff0000);
		}
}
