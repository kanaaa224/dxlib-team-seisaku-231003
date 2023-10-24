#include "End.h"
#include "DxLib.h"

End::End()
{

}

End::~End()
{

}

Scene* End::update()
{
	return this;
}

void End::draw()const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetFontSize(100);
	DrawString(100, 300, "Thank you", 0x000000);
}