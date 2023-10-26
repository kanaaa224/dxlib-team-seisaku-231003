#pragma once

#include "DxLib.h"
#include "inputCtrl.h"
#include "scene.h"

class ResultScene : public Scene
{
private:

	// ‰æ‘œ—p•Ï”
	//int img_map;
	//int img_branchPoint;
	//int img_weapon1;
	//int img_weapon2;
	//int img_background;
	int img_button_a;

public:
	ResultScene();
	~ResultScene();

	// XV
	Scene* update() override;

	// •`‰æ
	void draw() const override;

};

