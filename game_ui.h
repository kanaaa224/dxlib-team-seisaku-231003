//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

class GameUI {
private:
	int state, frameCounter;

	int score, level, floor, hp, exp, enemy;
	std::map<std::string, int> weapon;

	std::map<std::string, double> hud;

public:
	GameUI();

	~GameUI();

	void update(GameScene* gameScene);

	void draw() const;

	//////////////////////////////////////////////////

	// 初期化
	void init();

	//////////////////////////////////////////////////

	// ヘッドアップディスプレイ
	void drawHUD() const;

	//////////////////////////////////////////////////

	// ゲームスタート
	//void gameStart();

	// ゲームポーズ
	//void gamePause();

	// ゲームクリアアニメーション
	//void gameClear();

	// ゲームクリアアニメーション
	//void gameOver();
};