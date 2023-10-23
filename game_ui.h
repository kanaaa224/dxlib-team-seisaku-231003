//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

// ゲームユーザーインターフェースクラス（スコア、残機表示など）
class GameUI {
private:
	int score, level, floor, hp, exp, enemy, weapon;

public:
	GameUI() {
		//LoadGraph();

		init();
	};

	~GameUI() {
		//DeleteGraph();
	};

	//////////////////////////////////////////////////

	void init();

	void update(GameScene* gameScene);

	void draw() const;

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
};