#pragma once

// アニメーション
#define FPS_PERIOD 120					// 周期
#define AMPLITUDE 40					// 振幅

#include "scene.h"

// リザルトで使用予定
class weapon;								// 最初の武器
class second_weapon;						// 二つ目の武器

class GameOverScene : public Scene
{
private:
	// リザルトで使用予定
	int num1;
	int num2;

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
	GameOverScene(weapon* weapon1, second_weapon* weapon2);
	~GameOverScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

