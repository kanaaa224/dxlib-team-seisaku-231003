#include "main.h"
#include "DrawHelp.h"

Help::Help()
{
	//ƒwƒ‹ƒv‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	if (HelpImage1 = LoadGraph("resources/images/Help/Help_Img2.png")) {}
	if (HelpImage2 = LoadGraph("resources/images/Help/Help2.png")) {}

	Help_Abtn_Count = 0;

}

Help::~Help()
{

}

Scene*Help::update()
{
	//ƒwƒ‹ƒv2‰æ–Ê‚Ö‘JˆÚ
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		Help_Abtn_Count++;
		//return new DrawHelp;
	}
	
	return this;
}

void Help::draw()const
{
	if (Help_Abtn_Count > 0) {

		DrawGraph(0, 0, HelpImage2, TRUE);
	}
	else {

		//ƒwƒ‹ƒv‰æ‘œ‚Ì•\Ž¦
		DrawGraph(0, 0, HelpImage1, TRUE);
	}
}
