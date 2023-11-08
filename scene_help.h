#pragma once

#include "main.h"

class Help :  public Scene
{
private:
	int HelpImage1;
	int HelpImage2;
	int Helpflg;


public:
	Help();
	~Help();
	Scene* update()override;
	void draw()const override;
};

