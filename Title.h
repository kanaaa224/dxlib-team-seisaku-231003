#pragma once
#include "sourceFiles/scene.h"

class Title :public Scene
{
private:

	//‰æ‘œ‚Ì“Ç•Ï”
	int TitleImage;
	int EnemyImage0;
	int EnemyImage1;
	int EnemyImage2;
	int EnemyImage3;
	int EnemyImage4;

	int g_MenuNumber;
	int g_MenuY;
	int interval;
	short PadStick;
	int cursor;

	float interval;

public:
	Title();
	Scene* update() override;
	void draw() const override;

};