#pragma once
#include "sourceFiles/scene.h"
class GameMain : public Scene
{
private:

public:
	GameMain();
	~GameMain();
	Scene* update() override;
	void draw() const override;
};

