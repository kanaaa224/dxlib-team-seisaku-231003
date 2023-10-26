#pragma once

#include "scene.h"

class Credit : public Scene
{
private:

public:
	Credit();
	~Credit();
	Scene* update()override;
	void draw()const override;
};

