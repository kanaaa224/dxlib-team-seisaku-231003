#include "main.h"

Help::Help()
{
	HelpImage1 = LoadGraph("resources/images/Help1.png");
	HelpImage2 = LoadGraph("resources/images/Help2.png");
	Helpflg = 0;

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
	if (Helpflg < 1)
	{
		Helpflg=0;
	}
	else if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) && Helpflg > 1)
	{
		Helpflg ++;
	}

	return this;
}

void Help::draw()const
{
	if(Helpflg<1){
		DrawGraph(0, 0, HelpImage1, TRUE);
		SetFontSize(50);
		DrawString(1100, 670, "Aボタン:次へ", 0xff0000);
	}
	else
	{
		DrawGraph(0, 0, HelpImage2, TRUE);
		SetFontSize(50);
		DrawString(400, 670, "Aボタン：スタート", 0xff0000);
		DrawString(850, 670, "Bボタン：タイトル", 0xff0000);
	}
}
