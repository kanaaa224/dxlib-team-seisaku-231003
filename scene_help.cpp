#include "main.h"
#include "DrawHelp.h"

Help::Help()
{
	//ƒwƒ‹ƒv‰æ‘œ‚Ì“Ç‚İ‚İ
	HelpImage1 = LoadGraph("resources/images/Help/Help_Img2.png");
}

Help::~Help()
{

}

Scene*Help::update()
{
	//ƒwƒ‹ƒv2‰æ–Ê‚Ö‘JˆÚ
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new DrawHelp;
	}
	
	return this;
}

void Help::draw()const
{
	//ƒwƒ‹ƒv‰æ‘œ‚Ì•\¦
	DrawGraph(0, 0, HelpImage1, TRUE);
}
