//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

class GameUI {
private:
	int state, frameCounter;

	int score, level, floor;

	std::map<std::string, int> exp;
	std::map<std::string, int> hp;
	std::map<std::string, int> enemy;

	//std::vector<std::string, int> weapon;

	std::map<std::string, double> hud;

	std::map<std::string, double> pauseMenu;

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

	//////////////////////////////////////////////////

	void setScore(int Score) {
		score = Score;
	};

	void setLevel(int Level) {
		level = Level;
	};

	void setFloor(int Floor) {
		floor = Floor;
	};

	void setEXP(int Current, int Max, int Ratio) {
		exp["current"] = Current;
		exp["max"]     = Max;
		exp["ratio"]   = Ratio;
	};

	void setHP(int Current, int Max, int Ratio) {
		hp["current"] = Current;
		hp["max"]     = Max;
		hp["ratio"]   = Ratio;
	};

	void setEnemy(int Current, int Max) {
		enemy["current"] = Current;
		enemy["max"]     = Max;
	};
};