#pragma once

// アニメーション
#define FPS_PERIOD 120					// 周期
#define AMPLITUDE 40					// 振幅

#include "scene.h"

// リザルトで使用予定
class weapon;								// 最初の武器
class second_weapon;						// 二つ目の武器
class Map;									// マップ

class GameOverScene : public Scene
{
private:
	// 画像用変数
	int img_gameover;					// ゲームオーバー（装飾）
	int img_ghost;						// ゴースト
	int img_button_a;					// Aボタン
	int img_background;				// 背景
	int img_logo_result;

	// 座標移動
	int ghost_x;
	int ghost_y;
	int count;

	// フェード演出
	int value;						// 不透明度

	int result_info[11];			// リザルト画面に渡す武器情報、マップ情報

public:
	GameOverScene(weapon* weapon1, second_weapon* weapon2, Map* map);
	~GameOverScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;
};