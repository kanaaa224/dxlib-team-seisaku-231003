#pragma once

#include "inputCtrl.h"
#include "scene.h"
#include "scene_result.h"

class GameClearScene : public Scene
{
private:
	// 画像用変数
	int img_gameclear;					// ゲームクリア（装飾）
	int img_button_a;					// Aボタン
	//int img_background;				// 背景

public:
	GameClearScene();
	~GameClearScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};
