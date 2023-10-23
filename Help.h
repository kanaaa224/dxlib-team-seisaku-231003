#pragma once
#include "sourceFiles/scene.h"

class Help :  public Scene
{
private:

public:
	Help();
	~Help();
	Scene* update()override;
	void draw()const override;
};

