#include "Credit.h"
#include "DxLib.h"
#include "Title.h"
#include "sourceFiles/inputCtrl.h"

Credit::Credit()
{

}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	InputCtrl::Update();
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
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
}
