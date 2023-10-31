//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameUI::GameUI() {
	//LoadGraph();

	//////////////////////////////////////////////////

	//if (AddFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;
	//MessageBox(NULL, "フォントのロードに失敗しました。resourcesフォルダーを確認してください。", "", MB_OK);

	//////////////////////////////////////////////////

	init();
};

GameUI::~GameUI() {
	//DeleteGraph();

	//////////////////////////////////////////////////

	//RemoveFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL);
};

void GameUI::init() {
	state = 0;
	frameCounter = 0;
};

void GameUI::update(GameScene* gameScene) {
	frameCounter++;

	hud["opacity"] = 0.5f;

	setScore(432);
	setLevel(7);
	setFloor(-2);
	setHP(900, 1000, 90);
	setEXP(1500, 2000, 75);
	setEnemy(234, 2384);

	//score = gameScene->getScore();
};

void GameUI::draw() const {
	drawHUD();
};

void GameUI::drawHUD() const {
	/*double opacity = 0.0f;

	auto it = hud.find("opacity");
	if (it != hud.end()) opacity = it->second;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * opacity));*/


	//////////////////////////////////////////////////
	// レベル
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawCircle((SCREEN_WIDTH - 60), 60, 40, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int color = 0xffffff;

	if (level < 10) {
		color = GetColor(242, 166, 68);
	}
	else if (level < 20) {
		//
	};

	DrawCircle((SCREEN_WIDTH - 60), 60, 40, color, false, 3);
	
	SetFontSize(50);
	ChangeFont("Bodoni MT Black Italic", DX_CHARSET_DEFAULT);

	std::string str = std::to_string(level);
	DrawFormatString((SCREEN_WIDTH - 60) - GetDrawFormatStringWidth(str.c_str()) / 2, 35, 0xffffff, str.c_str());

	SetFontSize(20);
	ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);

	DrawFormatString((SCREEN_WIDTH - 90) - GetDrawFormatStringWidth("Lv.") / 2, 70, 0xffffff, "Lv.");


	//////////////////////////////////////////////////
	// 経験値
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox((SCREEN_WIDTH - 400), 70, (SCREEN_WIDTH - 110), 90, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int current = 0, max = 0, ratio = 0;

	auto it = exp.find("current");
	if (it != exp.end()) current = it->second;

	it = exp.find("max");
	if (it != exp.end()) max = it->second;

	it = exp.find("ratio");
	if (it != exp.end()) ratio = it->second;

	int lx = SCREEN_WIDTH - 400 + 5;
	int ly = 80 - 5;
	int rx = lx + static_cast<int>(290 * (ratio / 100.0f)) - 5;
	int ry = 90 - 5;

	if (!ratio) rx = lx;

	DrawBox(lx, ly, rx, ry, GetColor(57, 165, 229), true);

	SetFontSize(16);
	ChangeFont("Algerian", DX_CHARSET_DEFAULT);

	str = "EXP: " + std::to_string(current) + "/" + std::to_string(max);

	DrawFormatString((SCREEN_WIDTH - 395)/* - GetDrawFormatStringWidth(str.c_str()) / 2*/, 60, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// HP
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(40, 40, 460, 70, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	current = 0, max = 0, ratio = 0;

	it = hp.find("current");
	if (it != hp.end()) current = it->second;

	it = hp.find("max");
	if (it != hp.end()) max = it->second;

	it = hp.find("ratio");
	if (it != hp.end()) ratio = it->second;

	lx = 40 + 5;
	ly = 40 + 5;
	rx = lx + static_cast<int>(420 * (ratio / 100.0f)) - 5;
	ry = 70 - 5;

	if (!ratio) rx = lx;

	color = GetColor(128, 207, 27);
	if(ratio <= 10) color = GetColor(255, 0, 0);

	DrawBox(lx, ly, rx, ry, color, true);

	SetFontSize(16);
	ChangeFont("Algerian", DX_CHARSET_DEFAULT);

	str = "HP: " + std::to_string(current) + "/" + std::to_string(max);

	DrawFormatString(45, 30, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// スコア
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(40, 80, 260, 110, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(16);
	ChangeFont("Algerian", DX_CHARSET_DEFAULT);

	if (floor < 0) str = "B" + std::to_string(abs(floor)) + "F";
	else str = std::to_string(floor) + "F";

	DrawFormatString(50, (SCREEN_HEIGHT - 120), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// フロア
	//////////////////////////////////////////////////

	SetFontSize(38);
	ChangeFont("Century Gothic Bold Italic", DX_CHARSET_DEFAULT);
	
	if(floor < 0) str = "B" + std::to_string(abs(floor)) + "F";
	else str = std::to_string(floor) + "F";

	DrawFormatString(50, (SCREEN_HEIGHT - 120), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// 残りの敵
	//////////////////////////////////////////////////

	current = 0, max = 0;

	it = enemy.find("current");
	if (it != enemy.end()) current = it->second;

	it = enemy.find("max");
	if (it != enemy.end()) max = it->second;

	SetFontSize(24);
	ChangeFont("", DX_CHARSET_DEFAULT);

	str = "残りの敵: " + std::to_string(current) + "/" + std::to_string(max) + " 体";

	DrawFormatString(50, (SCREEN_HEIGHT - 80), 0xffffff, str.c_str());



















	ChangeFont("", DX_CHARSET_DEFAULT);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


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