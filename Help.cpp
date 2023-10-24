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
	/*if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new GameMain;
	}*/
	return this;
}

void Help::draw()const
{
	//DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	//SetFontSize(50);
	//DrawString(300, 350, "Help", 0x000000);
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		DrawGraph(0, 0, HelpImage2, TRUE);
	}
	else {
		DrawGraph(0, 0, HelpImage1, TRUE);
		SetFontSize(50);
		DrawString(1100, 630, "ŽŸ‚Ö", 0xff0000);
	}
}
