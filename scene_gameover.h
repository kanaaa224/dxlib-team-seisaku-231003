#pragma once

#define _USE_MATH_DEFINES				// <math.h>

// アニメーション
#define FPS_PERIOD 120					// 周期
#define AMPLITUDE 40					// 振幅

#include <math.h>
#include "inputCtrl.h"
#include "scene.h"
#include "scene_result.h"

class GameOverScene : public Scene
{
private:
	// 画像用変数
	int img_gameover;					// ゲームオーバー（装飾）
	int img_ghost;						// ゴースト
	int img_button_a;					// Aボタン
	//int img_background;				// 背景

	// 座標移動
	int ghost_x;
	int ghost_y;
	int count;

	// フェード演出
	int value;							// 不透明度

public:
	GameOverScene();
	~GameOverScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

