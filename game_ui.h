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

public:
	GameUI() {
		//LoadGraph();

		init();
	};

	~GameUI() {
		//DeleteGraph();
	};

	//////////////////////////////////////////////////

	void update(GameScene* gameScene);

	void draw() const;

	//////////////////////////////////////////////////

	// 初期化
	void init();

	//////////////////////////////////////////////////
	
	// 現在のスコア を描画
	/* void drawScore() const;

	// 現在のレベル を描画
	void drawLevel() const;

	// 現在のフロア を描画
	void drawFloor() const;

	// 体力ゲージ を描画
	void drawHP() const;

	// 経験値ゲージ を描画
	void drawEXP() const;

	// 残りの敵 を描画
	void drawEnemy() const;

	// 所持している武器 を描画
	void drawWeapon() const; */

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