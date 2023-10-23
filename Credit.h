#pragma once
#include "sourceFiles/scene.h"
class Credit : public Scene
{
private:

public:
	Credit();
	~Credit();
	Scene* update()override;
	void draw()const override;
};

