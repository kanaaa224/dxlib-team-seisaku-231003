#pragma once

#include "scene.h"

class Credit : public Scene
{
private:
	int CreditImage;

public:
	Credit();
	~Credit();
	Scene* update()override;
	void draw()const override;
};

