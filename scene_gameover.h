#pragma once

#define _USE_MATH_DEFINES				// <math.h>

// アニメーション
#define FPS_PERIOD 120					// 周期
#define AMPLITUDE 40					// 振幅

#include <math.h>
#include "DxLib.h"
#include "inputCtrl.h"
#include "scene.h"
#include "scene_result.h"

class GameOverScene : public Scene
{
private:
	int ghost_x;
	int ghost_y;
	float count;

	// 画像用変数
	int img_gameover;
	int img_ghost;
	int img_button_a;
	//int img_background;

public:
	GameOverScene();
	~GameOverScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

