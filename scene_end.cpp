#include "main.h"

End::End()
{
	g_WaitTime = 0;
}

End::~End()
{

}

Scene* End::update()
{
	if (++g_WaitTime > 300)
	{
		return nullptr;
	}
	return this;
}

void End::draw()const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetFontSize(100);
	DrawString(100, 300, "Thank you", 0x000000);
}