#pragma once
#include "scene.h"
class DrawHelp : public Scene
{
private:
	int HelpImage2;

public:
	DrawHelp();
	Scene* update()override;
	void draw()const override;
};

