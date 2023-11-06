//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameUI::GameUI() {
	if ((img["btnA"] = LoadGraph("resources/images/button_a.png")) == -1) throw;
	if ((img["btnX"] = LoadGraph("resources/images/button_x.png")) == -1) throw;

	//////////////////////////////////////////////////

	//if (AddFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;
	//MessageBox(NULL, "フォントのロードに失敗しました。resourcesフォルダーを確認してください。", "", MB_OK);

	//////////////////////////////////////////////////

	init();
};

GameUI::~GameUI() {
	DeleteGraph(img["btnA"]);

	//////////////////////////////////////////////////

	//RemoveFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL);
};

void GameUI::init() {
	state = 0;
	frameCounter = 1;
};

void GameUI::update(GameScene* gameScene) {
	if ((int)FPSCtrl::Get()) {
		frameCounter++;

		if (state == 0) {
			hud["opacity"] = 0.0f;
			hud["unvisibility"] = 1.0f;

			if (frameCounter % ((int)FPSCtrl::Get() * 3) == 0) state = 1;
		}
		else if (state == 1) {
			if (hud["opacity"] < 1.0f) hud["opacity"] += 0.04f;
			if (hud["unvisibility"] >= 0.0f) hud["unvisibility"] -= 0.05f;

			if (frameCounter % ((int)FPSCtrl::Get() * 2) == 0) state = 2;
		};
	};

	// 仮
	if (InputCtrl::GetKeyState(KEY_INPUT_G) == PRESS) init();
	//score = gameScene->getScore();
};

void GameUI::draw() const {
	if (state) {
		drawHUD();
	}
	else {
		drawBanner();
	};
};

void GameUI::drawHUD() const {
	double opacity      = 0.0f;
	double unvisibility = 0.0f;

	auto msd = hud.find("opacity");
	if (msd != hud.end()) opacity = msd->second;

	msd = hud.find("unvisibility");
	if (msd != hud.end()) unvisibility = msd->second;

	//////////////////////////////////////////////////

	int rootLX = 0,
		rootLY = 0,
		rootRX = SCREEN_WIDTH,
		rootRY = 0;

	if (state) {
		rootLX = rootLX - (SCREEN_WIDTH * unvisibility);
		rootRX = rootRX + (SCREEN_WIDTH * unvisibility);
	};

	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * opacity));


	//////////////////////////////////////////////////
	// レベル
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(rootRX - 60, rootRY + 60, 40, GetColor(0, 0, 0), true);
	if(opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int color = GetColor(255, 255, 255);
	if (level < 10) {
		color = GetColor(255, 214, 0);
	}
	else if (level < 20) {
		// 未完成
	};

	DrawCircle(rootRX - 60, rootRY + 60, 40, color, false, 3);

	SetFontSize(50);
	//ChangeFont("Bodoni MT Black Italic", DX_CHARSET_DEFAULT);

	std::string str = std::to_string(level);
	DrawFormatString(((rootRX - 60) - GetDrawFormatStringWidth(str.c_str()) / 2), rootRY + 35, 0xffffff, str.c_str());

	SetFontSize(20);
	//ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);

	DrawFormatString(((rootRX - 90) - GetDrawFormatStringWidth("Lv.") / 2), rootRY + 70, 0xffffff, "Lv.");


	//////////////////////////////////////////////////
	// 経験値
	//////////////////////////////////////////////////

	int current = 0, max = 0, ratio = 0;

	auto it = exp.find("current");
	if (it != exp.end()) current = it->second;

	it = exp.find("max");
	if (it != exp.end()) max = it->second;

	it = exp.find("ratio");
	if (it != exp.end()) ratio = it->second;

	int lx = rootRX - 400;
	int ly = rootRY + 70;
	int rx = rootRX - 110;
	int ry = rootRY + 90;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(lx, ly, rx, ry, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	DrawBox(lx, ly, rx, ry, GetColor(57, 165, 229), true);

	SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT); // Algerian

	str = "EXP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString((rootRX - 395)/* - GetDrawFormatStringWidth(str.c_str()) / 2*/, rootRY + 60, 0xffffff, str.c_str());

	
	//////////////////////////////////////////////////
	// HP
	//////////////////////////////////////////////////

	current = 0;
	max     = 0;
	ratio   = 0;

	it = hp.find("current");
	if (it != hp.end()) current = it->second;

	it = hp.find("max");
	if (it != hp.end()) max = it->second;

	it = hp.find("ratio");
	if (it != hp.end()) ratio = it->second;

	lx = rootLX + 40;
	ly = rootLY + 40;
	rx = rootLX + 460;
	ry = rootLY + 70;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(lx, ly, rx, ry, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	color = GetColor(128, 207, 27);
	if(ratio <= 15) color = GetColor(255, 0, 0);
	else if (ratio <= 30) color = GetColor(255, 140, 76);

	DrawBox(lx, ly, rx, ry, color, true);

	//SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT);

	str = "HP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString(rootLX + 45, rootLY + 30, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// スコア
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(rootLX + 40, rootLY + 80, rootLX + 260, rootLY + 110, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//SetFontSize(16);
	//ChangeFont("");

	str = "SCORE: " + std::to_string(score);
	DrawFormatString(rootLX + 50, rootLY + 88, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// フロア
	//////////////////////////////////////////////////

	SetFontSize(38);
	//ChangeFont("Century Gothic Bold Italic", DX_CHARSET_DEFAULT);
	
	if(floor < 0) str = "B" + std::to_string(abs(floor)) + "F";
	else str = std::to_string(floor) + "F";
	DrawFormatString(rootLX + 50, rootLY + (SCREEN_HEIGHT - 120), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// 残りの敵
	//////////////////////////////////////////////////

	current = 0;
	max     = 0;

	it = enemy.find("current");
	if (it != enemy.end()) current = it->second;

	it = enemy.find("max");
	if (it != enemy.end()) max = it->second;

	SetFontSize(20);
	//ChangeFont("");

	str = "残りの敵: " + std::to_string(current) + "/" + std::to_string(max) + " 体";
	DrawFormatString(rootLX + 50, rootLY + (SCREEN_HEIGHT - 80), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// 操作案内
	//////////////////////////////////////////////////

	SetFontSize(18);

	int img_btnA = 0, img_btnX = 0;

	it = img.find("btnA");
	if (it != img.end()) img_btnA = it->second;

	it = img.find("btnX");
	if (it != img.end()) img_btnX = it->second;

	lx = rootLX + 50;
	ly = rootLY + (SCREEN_HEIGHT - 200);
	rx = lx + 30;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnX, TRUE);

	DrawFormatString(lx + 40, ly + 5 , 0xffffff, "レベルアップメニュー");

	ly = rootLY + (SCREEN_HEIGHT - 240);
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnA, TRUE);

	DrawFormatString(lx + 40, ly + 5, 0xffffff, "回避");


	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void GameUI::drawBanner() const {
	std::string title, subTitle;

	auto it = banner.find("title");
	if (it != banner.end()) title = it->second;

	it = banner.find("subTitle");
	if (it != banner.end()) subTitle = it->second;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ChangeFont("");

	SetFontSize(40);
	DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(title.c_str()) / 2, 320, 0xffffff, title.c_str());

	SetFontSize(24);
	DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(subTitle.c_str()) / 2, 370, 0xffffff, subTitle.c_str());
};