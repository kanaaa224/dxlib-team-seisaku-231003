#pragma once

#include "scene.h"

class End :public Scene
{
private:
	int g_WaitTime;
	int g_PosY;
	int EndImage;

public:
	End();
	~End();
	Scene* update()override;
	void draw()const override;

};

