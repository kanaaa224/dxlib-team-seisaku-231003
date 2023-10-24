#pragma once
#include"DxLib.h"
#include"scene.h"

#define DATA_MAX 21

class Map : public Scene
{
private:
	int Mapdata[DATA_MAX];
	int randnum[DATA_MAX];
public:
	Map();
	~Map();
	virtual Scene* update() override;

	virtual void draw() const override;
};

