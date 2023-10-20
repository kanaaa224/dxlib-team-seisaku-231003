#pragma once
#include "sourceFiles/scene.h"

class Title :public Scene
{
private:

public:
	Title();
	~Title();
	virtual Scene* Update() = 0;
	virtual void draw() const = 0;

};