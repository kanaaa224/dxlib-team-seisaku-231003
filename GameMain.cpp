#include "GameMain.h"
#include "DxLib.h"
#include "sourceFiles/inputCtrl.h"
#include "Title.h"

GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

Scene* GameMain::update()
{
	return this;
}

void GameMain::draw() const
{
	DrawBox(0, 0, 1280, 720, 0xffffff,TRUE);
	SetFontSize(200);
	DrawString(200, 260, "GameMain", 0x000000);
}