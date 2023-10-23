#include "Help.h"
#include "DxLib.h"
#include "Title.h"

Help::Help()
{

}

Help::~Help()
{

}

Scene*Help::update()
{
	return this;
}

void Help::draw()const
{
	SetFontSize(50);
	DrawString(300, 350, "Help", 0x000000);
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
}
