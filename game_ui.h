//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

enum GameUIState {
	banner,          // バナー表示状態
	banner_playerUI, // バナーからプレイヤーUIへのフェードアニメーション中
	playerUI         // プレイヤーUI表示状態
};

class GameUI {
private:
	int state, frameCounter;

	int score, point, floor;

	std::map<std::string, int> exp;
	std::map<std::string, int> hp;
	std::map<std::string, int> enemy;
	std::map<std::string, std::string> enemyHP;
	std::map<std::string, std::map<std::string, int>> weapon;

	std::map<std::string, int> coolTime;

	std::map<std::string, double> hud;
	std::map<std::string, std::string> banner;
	std::map<std::string, std::string> notice;

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

	// 通知表示
	void drawNotice() const;

	//////////////////////////////////////////////////

	// ゲームスタート
	//void gameStart();

	// ゲームポーズ
	//void gamePause();

	// ゲームクリアアニメーション
	//void gameClear();

	// ゲームクリアアニメーション
	//void gameOver();

	// 通知表示
	void notification(std::string, std::string, std::string);

	//////////////////////////////////////////////////

	// プレイヤーのスコアを設定
	void setScore(int);

	// プレイヤーのレベルを設定
	//void setLevel(int);

	// ポイントを設定
	void setPoint(int);

	// 何階にいるか（ステージ）の設定
	void setFloor(int);

	// 経験値の現在値、最大値、割合（0-100）を設定
	void setEXP(int, int, int);

	// プレイヤーHPの現在値、最大値、割合（0-100）を設定
	void setHP(int, int, int);

	// プレイヤーのクールタイムを設定（現在値、最大値）
	void setCoolTime(int, int);

	// 所持している武器を設定（それぞれの武器の種類、レベル）
	void setWeapon(std::vector<int>, std::vector<int>);

	// 敵の今いる数、全ての数を設定
	void setEnemy(int, int);

	// 「drawEnemyHP()」で表示用の敵情報を設定（名前、体力）
	void setEnemyHP(std::string, int, int, int);

	// stateが「banner」の時に表示するテキストを設定
	void setBanner(std::string, std::string);

	//////////////////////////////////////////////////

	// stateを設定
	void setState(int);

	// stateを取得
	int getState();
};