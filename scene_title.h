#pragma once

#include "scene.h"

class Title :public Scene
{
private:

	//‰æ‘œ‚Ì“Ç•Ï”
	int TitleImage;

	int g_MenuNumber;
	int cursor;
	int g_MenuY;
public:
	Title();
	Scene* update() override;
	void draw() const override;

};