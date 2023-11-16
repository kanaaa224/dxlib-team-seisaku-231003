#include "main.h"
#include "DrawHelp.h"

Help::Help()
{
	HelpImage1 = LoadGraph("resources/images/Help1.png");

}

Help::~Help()
{

}

Scene*Help::update()
{
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new DrawHelp;
	}
	
	return this;
}

void Help::draw()const
{
	
		DrawGraph(0, 0, HelpImage1, TRUE);
		SetFontSize(40);
		DrawString(1000, 670, "Aƒ{ƒ^ƒ“:ŽŸ‚Ö", 0xff0000);
}
