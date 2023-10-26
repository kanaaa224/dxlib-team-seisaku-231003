#pragma once

#include "DxLib.h"
#include "inputCtrl.h"
#include "scene.h"
#include "scene_result.h"

class GameOverScene : public Scene
{
private:
	// 画像用変数
	int img_gameover;
	int img_button_a;			// Aボタン
	//int img_background;

public:
	GameOverScene();
	~GameOverScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

