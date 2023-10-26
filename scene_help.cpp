#include "main.h"

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
		return new GameScene;
	}
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
	{
		return new Title;
	}
	return this;
}

void Help::draw()const
{
	//DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	//SetFontSize(50);
	//DrawString(300, 350, "Help", 0x000000);
		DrawGraph(0, 0, HelpImage1, TRUE);
		SetFontSize(50);
		DrawString(400, 670, "Aボタン:スタート", 0xff0000);
		DrawString(850, 670, "Bボタン:タイトル", 0xff0000);
}
