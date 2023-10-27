#pragma once

#include "inputCtrl.h"
#include "scene.h"
#include "scene_title.h"

class ResultScene : public Scene
{
private:
	// 画像用変数
	//int img_map;
	//int img_branchPoint;
	//int img_weapon1;
	//int img_weapon2;
	//int img_background;
	int img_button_a;

	// フェード演出
	int value;

public:
	ResultScene();
	~ResultScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

