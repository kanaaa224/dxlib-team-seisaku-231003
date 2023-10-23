#pragma once
#include "sourceFiles/scene.h"
class End :public Scene
{
private:

public:
	End();
	~End();
	Scene* update()override;
	void draw()const override;

};

