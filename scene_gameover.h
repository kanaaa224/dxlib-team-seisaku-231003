#pragma once

#include "DxLib.h"
#include "inputCtrl.h"
#include "scene.h"
#include "scene_result.h"

class GameOverScene : public Scene
{
private:
	// ‰æ‘œ—p•Ï”
	int img_gameover;
	int img_ghost;
	int img_button_a;
	//int img_background;

public:
	GameOverScene();
	~GameOverScene();

	// XV
	Scene* update() override;

	// •`‰æ
	void draw() const override;

};

