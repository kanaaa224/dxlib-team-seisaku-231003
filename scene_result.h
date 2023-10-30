#pragma once

#include "inputCtrl.h"
#include "scene.h"
#include "scene_title.h"

class ResultScene : public Scene
{
private:
	// 画像用変数
	//int img_map;					// マップ
	//int img_branchPoint;			// 分岐点
	//int img_weapon1;				// 武器１
	//int img_weapon2;				// 武器２
	//int img_background;			// 背景
	int img_button_a;				// Aボタン

	// フェード演出
	int value;						// 不透明度

public:
	ResultScene();
	~ResultScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

