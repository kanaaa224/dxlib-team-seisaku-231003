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
	if ((int)FPSCtrl::Get()) {
		frameCounter++;

		if (InputCtrl::GetKeyState(KEY_INPUT_G) == PRESS) {
			init();
			frameCounter = 1;
		};

		if (state == 0) {
			hud["opacity"] = 0.0f;
			hud["visibility"] = 1.0f;

			if (frameCounter % ((int)FPSCtrl::Get() * 3) == 0) state = 1;
		}
		else if (state == 1) {
			if (hud["opacity"] < 1.0f) hud["opacity"] += 0.04f;
			if (hud["visibility"] >= 0.0f) hud["visibility"] -= 0.05f;

			if (frameCounter % ((int)FPSCtrl::Get() * 2) == 0) state = 2;
		};
	};

	//score = gameScene->getScore();
};

void GameUI::draw() const {
	drawHUD();

	if (state == 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(0, (SCREEN_HEIGHT / 4), SCREEN_WIDTH, (SCREEN_HEIGHT / 4) * 3, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//ChangeFont("");

		SetFontSize(40);
		DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth("MISSION（仮）") / 2, 300, 0xffffff, "MISSION（仮）");

		SetFontSize(24);
		DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth("すべてのモンスターを倒してください") / 2, 350, 0xffffff, "すべてのモンスターを倒してください");
	};
};

void GameUI::drawHUD() const {
	double hud_opacity = 0.0f;

	auto msd = hud.find("opacity");
	if (msd != hud.end()) hud_opacity = msd->second;

	double hud_visibility = 0.0f;

	msd = hud.find("visibility");
	if (msd != hud.end()) hud_visibility = msd->second;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * hud_opacity));


	//////////////////////////////////////////////////
	// レベル
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * hud_opacity);
	DrawCircle((SCREEN_WIDTH - 60) + (SCREEN_WIDTH * hud_visibility), 60, 40, GetColor(0, 0, 0), true);
	if(hud_opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int color = 0xffffff;

	if (level < 10) {
		color = GetColor(242, 166, 68);
	}
	else if (level < 20) {
		//
	};

	DrawCircle((SCREEN_WIDTH - 60) + (SCREEN_WIDTH * hud_visibility), 60, 40, color, false, 3);

	SetFontSize(50);
	//ChangeFont("Bodoni MT Black Italic", DX_CHARSET_DEFAULT);

	std::string str = std::to_string(level);
	DrawFormatString(((SCREEN_WIDTH - 60) - GetDrawFormatStringWidth(str.c_str()) / 2) + (SCREEN_WIDTH * hud_visibility), 35, 0xffffff, str.c_str());

	SetFontSize(20);
	//ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);

	DrawFormatString(((SCREEN_WIDTH - 90) - GetDrawFormatStringWidth("Lv.") / 2) + (SCREEN_WIDTH * hud_visibility), 70, 0xffffff, "Lv.");


	//////////////////////////////////////////////////
	// 経験値
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * hud_opacity);
	DrawBox((SCREEN_WIDTH - 400) + (SCREEN_WIDTH * hud_visibility), 70, (SCREEN_WIDTH - 110) + (SCREEN_WIDTH * hud_visibility), 90, GetColor(0, 0, 0), true);
	if (hud_opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int current = 0, max = 0, ratio = 0;

	auto it = exp.find("current");
	if (it != exp.end()) current = it->second;

	it = exp.find("max");
	if (it != exp.end()) max = it->second;

	it = exp.find("ratio");
	if (it != exp.end()) ratio = it->second;

	int lx = (SCREEN_WIDTH - 400 + 5) + (SCREEN_WIDTH * hud_visibility);
	int ly = 80 - 5;
	int rx = ((lx - 5) + static_cast<int>(290 * (ratio / 100.0f)) - 5) + (SCREEN_WIDTH * hud_visibility);
	int ry = 90 - 5;

	if (!ratio) rx = lx;

	DrawBox(lx, ly, rx, ry, GetColor(57, 165, 229), true);

	SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT); // Algerian

	str = "EXP: " + std::to_string(current) + "/" + std::to_string(max);

	DrawFormatString((SCREEN_WIDTH - 395)/* - GetDrawFormatStringWidth(str.c_str()) / 2*/ + (SCREEN_WIDTH * hud_visibility), 60, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// HP
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * hud_opacity);
	DrawBox(40 - (SCREEN_WIDTH * hud_visibility), 40, 460 - (SCREEN_WIDTH * hud_visibility), 70, GetColor(0, 0, 0), true);
	if (hud_opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	current = 0, max = 0, ratio = 0;

	it = hp.find("current");
	if (it != hp.end()) current = it->second;

	it = hp.find("max");
	if (it != hp.end()) max = it->second;

	it = hp.find("ratio");
	if (it != hp.end()) ratio = it->second;

	lx = (40 + 5) - (SCREEN_WIDTH * hud_visibility);
	ly = 40 + 5;
	rx = ((lx - 5) + static_cast<int>(420 * (ratio / 100.0f)) - 5) - (SCREEN_WIDTH * hud_visibility);
	ry = 70 - 5;

	if (!ratio) rx = lx;

	color = GetColor(128, 207, 27);
	if(ratio <= 10) color = GetColor(255, 0, 0);

	DrawBox(lx, ly, rx, ry, color, true);

	//SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT);

	str = "HP: " + std::to_string(current) + "/" + std::to_string(max);

	DrawFormatString(45 - (SCREEN_WIDTH * hud_visibility), 30, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// スコア
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * hud_opacity);
	DrawBox(40 - (SCREEN_WIDTH * hud_visibility), 80, 260 - (SCREEN_WIDTH * hud_visibility), 110, GetColor(0, 0, 0), true);
	if (hud_opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//SetFontSize(16);
	//ChangeFont("");

	str = "SCORE: " + std::to_string(score);

	DrawFormatString(50 - (SCREEN_WIDTH * hud_visibility), 88, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// フロア
	//////////////////////////////////////////////////

	SetFontSize(38);
	//ChangeFont("Century Gothic Bold Italic", DX_CHARSET_DEFAULT);
	
	if(floor < 0) str = "B" + std::to_string(abs(floor)) + "F";
	else str = std::to_string(floor) + "F";

	DrawFormatString(50 - (SCREEN_WIDTH * hud_visibility), (SCREEN_HEIGHT - 120), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// 残りの敵
	//////////////////////////////////////////////////

	current = 0, max = 0;

	it = enemy.find("current");
	if (it != enemy.end()) current = it->second;

	it = enemy.find("max");
	if (it != enemy.end()) max = it->second;

	SetFontSize(20);
	//ChangeFont("");

	str = "残りの敵: " + std::to_string(current) + "/" + std::to_string(max) + " 体";

	DrawFormatString(50 - (SCREEN_WIDTH * hud_visibility), (SCREEN_HEIGHT - 80), 0xffffff, str.c_str());




















	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawFormatString(20, 20, 0xffffff, "%f %f", hud_opacity, hud_visibility);


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