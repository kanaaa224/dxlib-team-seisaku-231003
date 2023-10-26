#include "main.h"

Credit::Credit()
{

}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	InputCtrl::Update();
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
	{
		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetFontSize(50);
	DrawString(300, 350, "Credit", 0x000000);
	DrawString(300, 500, "Xボタン：タイトルへ", 0x000000);
}
