#pragma once
#include "sourceFiles/scene.h"

class Title :public Scene
{
private:

	//‰æ‘œ‚Ì“Ç•Ï”
	int TitleImage;


	short PadStick;
	int cursor;
	int state,frameCounter;

	bool Ctrl;

public:
	Title();
	Scene* update() override;
	void draw() const override;

};