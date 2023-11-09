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
	std::map<std::string, std::string> enemyHP;
	std::map<std::string, std::map<std::string, int>> weapon;

	std::map<std::string, double> hud;
	std::map<std::string, std::string> banner;

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

	// HP表示
	void drawHP() const;

	// ポーズ画面
	void drawPause() const;

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

	// プレイヤーのスコアを設定
	void setScore(int);

	// プレイヤーのレベルを設定
	void setLevel(int);

	// 何階にいるか（ステージ）の設定
	void setFloor(int);

	// 経験値の現在値、最大値、割合（0-100）を設定
	void setEXP(int, int, int);

	// プレイヤーHPの現在値、最大値、割合（0-100）を設定
	void setHP(int, int, int);

	// 所持している武器を設定（それぞれの武器の種類、レベル）
	void setWeapon(std::vector<int>, std::vector<int>);

	// 敵の今いる数、全ての数を設定
	void setEnemy(int, int);

	// 「drawEnemyHP」で表示用の敵情報を設定（名前、体力）
	void setEnemyHP(std::string, int, int, int);

	// stateが「banner」の時に表示するテキストを設定
	void setBanner(std::string, std::string);

	// stateを設定
	void setState(int);

	//////////////////////////////////////////////////

	// stateを取得
	int getState();
};