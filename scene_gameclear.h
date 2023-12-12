#pragma once

#include "scene.h"

// リザルトで使用予定
class weapon;								// 最初の武器
class second_weapon;						// 二つ目の武器
class Map;									// マップ

class GameClearScene : public Scene
{
private:
	// 画像用変数
	int img_gameclear;					// ゲームクリア（装飾）
	int img_crown;						// 王冠
	int img_grail;						// 聖杯
	int img_player;						// プレイヤー
	int img_button_a;					// Aボタン
	int img_background;					// 背景
	int img_logo_result;

	// フェード演出
	int value;						// 不透明度

	int result_info[11];			// リザルト画面に渡す武器情報、マップ情報

public:
	GameClearScene(weapon* weapon1, second_weapon* weapon2, Map* map);
	~GameClearScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};
