//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameUI::GameUI() {
	if ((img["btnA"] = LoadGraph("resources/images/button_a.png")) == -1) throw;
	if ((img["btnB"] = LoadGraph("resources/images/button_b.png")) == -1) throw;
	if ((img["btnX"] = LoadGraph("resources/images/button_x.png")) == -1) throw;

	if ((img["weaponSword"]      = LoadGraph("resources/images/sword_longsword_brown.png"))      == -1) throw;
	if ((img["weaponDagger"]     = LoadGraph("resources/images/sword_shortsword_brown.png"))     == -1) throw;
	if ((img["weaponGreatSword"] = LoadGraph("resources/images/tsurugi_bronze_blue.png"))        == -1) throw;
	if ((img["weaponSpear"]      = LoadGraph("resources/images/spear.png"))                      == -1) throw;
	if ((img["weaponFrail"]      = LoadGraph("resources/images/Frailt_dottoy.png"))              == -1) throw;
	if ((img["weaponBook"]       = LoadGraph("resources/images/book_madousyo_necronomicon.png")) == -1) throw;

	//////////////////////////////////////////////////

	//if (AddFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;
	//MessageBox(NULL, "フォントのロードに失敗しました。resourcesフォルダーを確認してください。", "", MB_OK);

	//////////////////////////////////////////////////

	init();
};

GameUI::~GameUI() {
	DeleteGraph(img["btnA"]);
	DeleteGraph(img["btnB"]);
	DeleteGraph(img["btnX"]);

	DeleteGraph(img["weaponSword"]);
	DeleteGraph(img["weaponDagger"]);
	DeleteGraph(img["weaponGreatSword"]);
	DeleteGraph(img["weaponSpear"]);
	DeleteGraph(img["weaponFrail"]);
	DeleteGraph(img["weaponBook"]);

	//////////////////////////////////////////////////

	//RemoveFontResourceEx("resources/fonts/Anton-Regular.ttf", FR_PRIVATE, NULL);
};

void GameUI::init() {
	state        = 0;
	frameCounter = 1;

	notice["opacity"] = std::to_string(0.0);
	notice["state"]   = std::to_string(0);
	notice["frame"]   = std::to_string(0);
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
			for (int i = 0; i < 450; i++) {
				if (hud["opacity"] < 1.0f)       hud["opacity"]      += ((60.0f / FPSCtrl::Get()) * 0.0001f);
				if (hud["unvisibility"] >= 0.0f) hud["unvisibility"] -= ((60.0f / FPSCtrl::Get()) * 0.0001f);
			};

			if (frameCounter % ((int)FPSCtrl::Get() * 2) == 0) state = 2;
		}
		else if (state == 2) {
			hud["opacity"] = 1.0f;
			hud["unvisibility"] = 0.0f;
		};
	};

	if (std::stoi(notice["state"])) {
		notice["frame"] = std::to_string(std::stoi(notice["frame"]) + 1);

		if (std::stoi(notice["state"]) == 1) {
			if (std::stod(notice["opacity"]) < 1.0f) notice["opacity"] = std::to_string(std::stod(notice["opacity"]) + ((60.0f / FPSCtrl::Get()) * 0.1f));

			if (std::stoi(notice["frame"]) % ((int)FPSCtrl::Get() * 4) == 0) {
				notice["state"] = std::to_string(2);
			};
		}
		else if (std::stoi(notice["state"]) == 2) {
			if (std::stod(notice["opacity"]) > 0.0f) notice["opacity"] = std::to_string(std::stod(notice["opacity"]) - ((60.0f / FPSCtrl::Get()) * 0.1f));

			if (std::stoi(notice["frame"]) % ((int)FPSCtrl::Get() * 2) == 0) {
				notice["opacity"] = std::to_string(0.0);
				notice["state"]   = std::to_string(0);
				notice["frame"]   = std::to_string(0);
			};
		};
	};

	if (InputCtrl::GetKeyState(KEY_INPUT_G) == PRESS) init(); // 仮
	if (InputCtrl::GetKeyState(KEY_INPUT_N) == PRESS) notification("武器強化可能！", "Xボタンで確認", "btnX"); // 仮
	if (InputCtrl::GetKeyState(KEY_INPUT_S) == PRESS) state = 1; // スキップ
};

void GameUI::draw() const {
	if (state) {
		drawHUD();
	}
	else {
		drawBanner();
	};

	std::string notice_state = std::to_string(0);
	if (notice.find("state") != notice.end()) notice_state = notice.at("state");
	if (std::stoi(notice_state)) drawNotice();
};

void GameUI::drawHUD() const {
	double opacity      = 0.0f;
	double unvisibility = 0.0f;

	if (hud.find("opacity")      != hud.end()) opacity      = hud.at("opacity");
	if (hud.find("unvisibility") != hud.end()) unvisibility = hud.at("unvisibility");

	//////////////////////////////////////////////////

	int rootLX = 0;
	int rootLY = 0;
	int rootRX = SCREEN_WIDTH;
	int rootRY = 0;

	if (state) {
		rootLX = rootLX - (SCREEN_WIDTH * unvisibility);
		rootRX = rootRX + (SCREEN_WIDTH * unvisibility);
	};

	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * opacity));


	//////////////////////////////////////////////////
	// ポイント
	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(rootRX - 60, rootRY + 60, 40, GetColor(0, 0, 0), true);
	if(opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int color = GetColor(255, 255, 255);
	if (point < 10) {
		color = GetColor(255, 214, 0);
	}
	else if (point < 20) {
		// 未完成
	};

	DrawCircle(rootRX - 60, rootRY + 60, 40, color, false, 3);

	SetFontSize(50);
	//ChangeFont("Bodoni MT Black Italic", DX_CHARSET_DEFAULT);
	std::string str = std::to_string(point);
	DrawFormatString(((rootRX - 60) - GetDrawFormatStringWidth(str.c_str()) / 2), rootRY + 35, 0xffffff, str.c_str());

	//SetFontSize(20);
	//ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);
	//DrawFormatString(((rootRX - 90) - GetDrawFormatStringWidth("Lv.") / 2), rootRY + 70, 0xffffff, "Lv.");


	//////////////////////////////////////////////////
	// 経験値
	//////////////////////////////////////////////////

	int current = 0;
	int max     = 0;
	int ratio   = 0;

	if (exp.find("current") != exp.end()) current = exp.at("current");
	if (exp.find("max")     != exp.end()) max     = exp.at("max");
	if (exp.find("ratio")   != exp.end()) ratio   = exp.at("ratio");

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

	if (hp.find("current") != hp.end()) current = hp.at("current");
	if (hp.find("max")     != hp.end()) max     = hp.at("max");
	if (hp.find("ratio")   != hp.end()) ratio   = hp.at("ratio");

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
	if (ratio <= 15)      color = GetColor(255, 0, 0);
	else if (ratio <= 30) color = GetColor(255, 140, 76);

	DrawBox(lx, ly, rx, ry, color, true);

	//SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT);
	str = "HP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString(rootLX + 45, rootLY + 30, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// スコア
	//////////////////////////////////////////////////

	/* SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(rootLX + 40, rootLY + 80, rootLX + 260, rootLY + 110, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//SetFontSize(16);
	//ChangeFont("");
	str = "SCORE: " + std::to_string(score);
	DrawFormatString(rootLX + 50, rootLY + 88, 0xffffff, str.c_str()); */


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

	if (enemy.find("current") != enemy.end()) current = enemy.at("current");
	if (enemy.find("max")     != enemy.end()) max     = enemy.at("max");

	SetFontSize(20);
	//ChangeFont("");
	str = "残りの敵: " + std::to_string(current) + "/" + std::to_string(max) + " 体";
	DrawFormatString(rootLX + 50, rootLY + (SCREEN_HEIGHT - 80), 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// 操作案内
	//////////////////////////////////////////////////

	int img_btnA = 0;
	int img_btnB = 0;
	int img_btnX = 0;

	if (img.find("btnA") != img.end()) img_btnA = img.at("btnA");
	if (img.find("btnB") != img.end()) img_btnB = img.at("btnB");
	if (img.find("btnX") != img.end()) img_btnX = img.at("btnX");

	lx = rootLX + 50;
	ly = rootLY + (SCREEN_HEIGHT - 200);
	rx = lx + 30;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnX, TRUE);

	SetFontSize(18);
	DrawFormatString(lx + 40, ly + 5 , 0xffffff, "レベルアップメニュー");

	/* ly -= 40;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnB, TRUE);

	DrawFormatString(lx + 40, ly + 5, 0xffffff, "武器持ち替え（仮）"); */

	ly -= 40;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnA, TRUE);

	DrawFormatString(lx + 40, ly + 5, 0xffffff, "回避");


	//////////////////////////////////////////////////
	// 武器
	//////////////////////////////////////////////////

	int img_weaponSword      = 0;
	int img_weaponDagger     = 0;
	int img_weaponGreatSword = 0;
	int img_weaponSpear      = 0;
	int img_weaponFrail      = 0;
	int img_weaponBook       = 0;

	if (img.find("weaponSword")      != img.end()) img_weaponSword      = img.at("weaponSword");
	if (img.find("weaponDagger")     != img.end()) img_weaponDagger     = img.at("weaponDagger");
	if (img.find("weaponGreatSword") != img.end()) img_weaponGreatSword = img.at("weaponGreatSword");
	if (img.find("weaponSpear")      != img.end()) img_weaponSpear      = img.at("weaponSpear");
	if (img.find("weaponFrail")      != img.end()) img_weaponFrail      = img.at("weaponFrail");
	if (img.find("weaponBook")       != img.end()) img_weaponBook       = img.at("weaponBook");

	int weaponA[3];
	int weaponB[3];

	if (weapon.find("A") != weapon.end()) {
		const std::map<std::string, int>& weaponStats = weapon.at("A");

		if (weaponStats.find("type")     != weaponStats.end()) weaponA[0] = weaponStats.at("type");
		if (weaponStats.find("level")    != weaponStats.end()) weaponA[1] = weaponStats.at("level");
		if (weaponStats.find("selected") != weaponStats.end()) weaponA[2] = weaponStats.at("selected");
	};
	if (weapon.find("B") != weapon.end()) {
		const std::map<std::string, int>& weaponStats = weapon.at("B");

		if (weaponStats.find("type")     != weaponStats.end()) weaponB[0] = weaponStats.at("type");
		if (weaponStats.find("level")    != weaponStats.end()) weaponB[1] = weaponStats.at("level");
		if (weaponStats.find("selected") != weaponStats.end()) weaponB[2] = weaponStats.at("selected");
	};

	int x = rootRX - 80;
	int y = rootRY + (SCREEN_HEIGHT - 80);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(x, y, 50, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (weaponB[0] != 99) {
		SetFontSize(16);
		str = "Lv. " + std::to_string(weaponB[1]);
		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y + 30, 0xffffff, str.c_str());

		if (weaponB[2]) DrawCircle(x, y, 55, GetColor(255, 255, 255), false, 3);

		switch (weaponB[0]) {
		case 0:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponSpear, TRUE);
			str = "槍";
			break;

		case 1:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponFrail, TRUE);
			str = "フレイル";
			break;

		case 2:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponBook, TRUE);
			str = "本";
			break;

		default:
			break;
		};

		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y - 40, 0xffffff, str.c_str());
	};

	x -= 120;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(x, y, 50, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (weaponA[0] != 99) {
		SetFontSize(16);
		str = "Lv. " + std::to_string(weaponA[1]);
		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y + 30, 0xffffff, str.c_str());

		if(weaponA[2]) DrawCircle(x, y, 55, GetColor(255, 255, 255), false, 3);

		switch (weaponA[0]) {
		case 0:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponSword, TRUE);
			str = "片手剣";
			break;

		case 1:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponDagger, TRUE);
			str = "短剣";
			break;

		case 2:
			DrawExtendGraph(x - 20, y - 20, (x - 20) + 50, (y - 20) + 50, img_weaponGreatSword, TRUE);
			str = "大剣";
			break;

		default:
			break;
		};

		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y - 40, 0xffffff, str.c_str());
	};


	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void GameUI::drawBanner() const {
	std::string title;
	std::string subTitle;

	if (banner.find("title")    != banner.end()) title    = banner.at("title");
	if (banner.find("subTitle") != banner.end()) subTitle = banner.at("subTitle");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int line = 5;
	DrawBox(0, (SCREEN_HEIGHT / 3),         SCREEN_WIDTH, (SCREEN_HEIGHT / 3) + line, GetColor(255, 255, 255), true);
	DrawBox(0, (SCREEN_HEIGHT / 3) * 2 - line, SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, GetColor(255, 255, 255), true);

	//ChangeFont("");

	SetFontSize(40);
	DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(title.c_str()) / 2, 320, 0xffffff, title.c_str());

	SetFontSize(24);
	DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(subTitle.c_str()) / 2, 370, 0xffffff, subTitle.c_str());
};

void GameUI::drawEnemyHP() const {
	double opacity      = 0.0f;
	double unvisibility = 0.0f;

	if (hud.find("opacity")      != hud.end()) opacity      = hud.at("opacity");
	if (hud.find("unvisibility") != hud.end()) unvisibility = hud.at("unvisibility");

	//////////////////////////////////////////////////

	SetFontSize(16);

	std::string name;
	std::string current;
	std::string max;
	std::string ratio = "0";

	if (enemyHP.find("name")    != enemyHP.end()) name    = enemyHP.at("name");
	if (enemyHP.find("current") != enemyHP.end()) current = enemyHP.at("current");
	if (enemyHP.find("max")     != enemyHP.end()) max     = enemyHP.at("max");
	if (enemyHP.find("ratio")   != enemyHP.end()) ratio   = enemyHP.at("ratio");

	int lx = (SCREEN_WIDTH / 2) - 200;
	int ly = 120;
	int rx = (SCREEN_WIDTH / 2) + 200;
	int ry = 140;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(lx, ly, rx, ry, GetColor(0, 0, 0), true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int x = lx + ((rx - lx) / 2);
	int y = ly - 20;

	std::string str = name + ": " + current + "/" + max;
	DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y, 0xffffff, str.c_str());

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (std::stoi(ratio) / 100.0f));

	DrawBox(lx, ly, rx, ry, GetColor(255, 0, 0), true);


	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void GameUI::drawHP() const {
	SetFontSize(16);

	int current = 0;
	int max     = 0;
	int ratio   = 0;

	if (hp.find("current") != hp.end()) current = hp.at("current");
	if (hp.find("max")     != hp.end()) max     = hp.at("max");
	if (hp.find("ratio")   != hp.end()) ratio   = hp.at("ratio");

	int lx = 40;
	int ly = 40;
	int rx = 460;
	int ry = 70;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(lx, ly, rx, ry, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	int color = GetColor(128, 207, 27);
	if (ratio <= 15)      color = GetColor(255, 0, 0);
	else if (ratio <= 30) color = GetColor(255, 140, 76);

	DrawBox(lx, ly, rx, ry, color, true);

	std::string str = "HP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString(45, 30, 0xffffff, str.c_str());
};

void GameUI::drawPause() const {
	SetFontSize(16);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	std::string str = "PAUSE（仮）";
	DrawFormatString((SCREEN_WIDTH / 2) - (GetDrawFormatStringWidth(str.c_str()) / 2), SCREEN_HEIGHT / 2, 0xffffff, str.c_str());
};

void GameUI::drawNotice() const {
	std::string title;
	std::string message;
	std::string button;
	std::string opacity = std::to_string(0);

	if (notice.find("title")   != notice.end()) title   = notice.at("title");
	if (notice.find("message") != notice.end()) message = notice.at("message");
	if (notice.find("button")  != notice.end()) button  = notice.at("button");
	if (notice.find("opacity") != notice.end()) opacity = notice.at("opacity");

	int img_btn = 0;

	if (img.find(button) != img.end()) img_btn = img.at(button);

	int lx = (SCREEN_WIDTH / 2) - 150;
	int ly = SCREEN_HEIGHT - 100 + (100 - (100 * std::stod(opacity)));
	int rx = lx + 300;
	int ry = ly + 60;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180 * std::stod(opacity));
	DrawBox(lx, ly, rx, ry, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * std::stod(opacity));

	SetFontSize(18);
	DrawFormatString(lx + 10, ly + 10, 0xffffff, title.c_str());

	SetFontSize(14);
	DrawFormatString(lx + 15, ly + 35, 0xffffff, message.c_str());

	DrawExtendGraph(rx - (ry - ly), ly + 10, rx - 10, ry - 10, img_btn, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void GameUI::notification(std::string Title, std::string Message, std::string Button) {
	if (!std::stoi(notice["state"])) {
		notice["title"]   = Title;
		notice["message"] = Message;
		notice["button"]  = Button;

		notice["state"] = std::to_string(1);
	};
};

void GameUI::setScore(int Score) {
	score = Score;
};

void GameUI::setPoint(int Point) {
	point = Point;
};

void GameUI::setFloor(int Floor) {
	floor = Floor;
};

void GameUI::setEXP(int Current, int Max, int Ratio) {
	exp["current"] = Current;
	exp["max"]     = Max;
	if (Ratio >= 0 && Ratio <= 100) exp["ratio"] = Ratio;
};

void GameUI::setHP(int Current, int Max, int Ratio) {
	hp["current"] = Current;
	hp["max"]     = Max;
	if (Ratio >= 0 && Ratio <= 100) hp["ratio"] = Ratio;
};

void GameUI::setWeapon(std::vector<int> WeaponA, std::vector<int> WeaponB) {
	weapon["A"]["type"]     = WeaponA[0];
	weapon["A"]["level"]    = WeaponA[1];
	weapon["A"]["selected"] = WeaponA[2];

	weapon["B"]["type"]     = WeaponB[0];
	weapon["B"]["level"]    = WeaponB[1];
	weapon["B"]["selected"] = WeaponB[2];
};

void GameUI::setEnemy(int Current, int Max) {
	enemy["current"] = Current;
	enemy["max"]     = Max;
};

void GameUI::setEnemyHP(std::string Name, int Current, int Max, int Ratio) {
	enemyHP["name"]    = Name;
	enemyHP["current"] = std::to_string(Current);
	enemyHP["max"]     = std::to_string(Max);
	if (Ratio >= 0 && Ratio <= 100) enemyHP["ratio"] = std::to_string(Ratio);
};

void GameUI::setBanner(std::string Title, std::string SubTitle) {
	banner["title"]    = Title;
	banner["subTitle"] = SubTitle;
};

void GameUI::setState(int State) {
	state = State;
};

int GameUI::getState() {
	return state;
};