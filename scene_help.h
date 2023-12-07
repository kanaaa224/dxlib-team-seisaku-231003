#pragma once
#include "main.h"
#include "scene.h"

class Help :  public Scene
{
private:
	int HelpImage1;
	int HelpImage2;
	int HelpImage3;

	int Help_Abtn_Count;

public:
	Help();
	~Help();
	Scene* update()override;
	void draw()const override;
};

