//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

enum GameUIState {
	banner,
	playerUI
};

class GameUI {
private:
	int state, frameCounter;

	int score, level, floor;

	std::map<std::string, int> exp;
	std::map<std::string, int> hp;
	std::map<std::string, int> enemy;

	std::map<std::string, std::map<std::string, int>> weapon;

	std::map<std::string, double> hud;

	std::map<std::string, std::string> banner;

	std::map<std::string, std::string> enemyHP;

	//std::map<std::string, double> pauseMenu;

	std::map<std::string, int> img;

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

	// バナー表示
	void drawBanner() const;

	// 敵の体力
	void drawEnemyHP() const;

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
		if (Ratio >= 0 && Ratio <= 100) exp["ratio"] = Ratio;
	};

	void setHP(int Current, int Max, int Ratio) {
		hp["current"] = Current;
		hp["max"]     = Max;
		if (Ratio >= 0 && Ratio <= 100) hp["ratio"] = Ratio;
	};

	void setEnemy(int Current, int Max) {
		enemy["current"] = Current;
		enemy["max"]     = Max;
	};

	void setWeapon(std::vector<int> WeaponA, std::vector<int> WeaponB) {
		weapon["A"]["type"]     = WeaponA[0];
		weapon["A"]["level"]    = WeaponA[1];
		weapon["A"]["selected"] = WeaponA[2];

		weapon["B"]["type"]     = WeaponB[0];
		weapon["B"]["level"]    = WeaponB[1];
		weapon["B"]["selected"] = WeaponB[2];
	};

	void setEnemyHP(std::string Name, int Current, int Max, int Ratio) {
		enemyHP["name"]    = Name;
		enemyHP["current"] = Current;
		enemyHP["max"]     = Max;
		if (Ratio >= 0 && Ratio <= 100) enemyHP["ratio"] = Ratio;
	};

	void setBanner(std::string Title, std::string SubTitle) {
		banner["title"]    = Title;
		banner["subTitle"] = SubTitle;
	};

	void setState(int State) {
		state = State;
	};

	//////////////////////////////////////////////////

	int getState() {
		return state;
	};
};