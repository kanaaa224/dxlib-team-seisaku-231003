#pragma once
#include "sourceFiles/scene.h"
class End :public Scene
{
private:
	int g_WaitTime;
	int g_PosY;

public:
	End();
	~End();
	Scene* update()override;
	void draw()const override;

};

