#include "main.h"

Credit::Credit()
{
	CreditImage = LoadGraph("resources/images/background.png");
	g_WaitTime = 0;
}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	if (++g_WaitTime < 1500)g_PosY = 600 - g_WaitTime;
	if (++g_WaitTime > 900) {
		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	DrawExtendGraph(0, 0,1280,720, CreditImage, TRUE);
	SetFontSize(40);
	DrawString(100, 350+g_PosY, "pngtree", 0x000000);
}
