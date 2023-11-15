#include "main.h"

Credit::Credit()
{
	CreditImage = LoadGraph("resources/images/credit.png");
}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS && InputCtrl::GetKeyState(KEY_INPUT_A)==PRESS)
	{
		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	DrawExtendGraph(0, 0,1280,720, CreditImage, TRUE);
	SetFontSize(30);
	DrawString(100, 350, "pngtree", 0x000000);
}
