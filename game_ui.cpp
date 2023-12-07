//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameUI::GameUI() {
	if ((img["btnA"] = LoadGraph("resources/images/button_a.png")) == -1) throw;
	if ((img["btnB"] = LoadGraph("resources/images/button_b.png")) == -1) throw;
	if ((img["btnX"] = LoadGraph("resources/images/button_x.png")) == -1) throw;

	if ((img["weaponSword"]      = LoadGraph("resources/images/武器/片手剣50・50.png"))   == -1) throw;
	if ((img["weaponDagger"]     = LoadGraph("resources/images/武器/短剣50・50.png"))     == -1) throw;
	if ((img["weaponGreatSword"] = LoadGraph("resources/images/武器/大剣50・50.png"))     == -1) throw;
	if ((img["weaponSpear"]      = LoadGraph("resources/images/武器/槍50・50.png"))       == -1) throw;
	if ((img["weaponFrail"]      = LoadGraph("resources/images/武器/フレイル50・50.png")) == -1) throw;
	if ((img["weaponBook"]       = LoadGraph("resources/images/武器/本50・50.png"))       == -1) throw;

	if ((img["whiteCircle50"]    = LoadGraph("resources/images/shiromaru_50.png")) == -1) throw;
	if ((img["blackCircle50"]    = LoadGraph("resources/images/kuromaru_50.png"))  == -1) throw;
	if ((img["whiteCircle80"]    = LoadGraph("resources/images/shiromaru_80.png")) == -1) throw;
	if ((img["blackCircle80"]    = LoadGraph("resources/images/kuromaru_80.png"))  == -1) throw;

	if ((img["coolTimeWhite"]    = LoadGraph("resources/images/Cool_Time_white.png")) == -1) throw;
	if ((img["coolTimeGreen"]    = LoadGraph("resources/images/Cool_Time_green.png")) == -1) throw;

	//////////////////////////////////////////////////

	//if (AddFontResourceEx("resources/fonts/PressStart2P-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;
	//MessageBox(NULL, "フォントのロードに失敗しました。resourcesフォルダーを確認してください。", "", MB_OK);

	//////////////////////////////////////////////////

	coolTime["current"] = 0.0f;
	coolTime["max"]     = 0.0f;

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

	DeleteGraph(img["whiteCircle50"]);
	DeleteGraph(img["blackCircle50"]);
	DeleteGraph(img["whiteCircle80"]);
	DeleteGraph(img["blackCircle80"]);

	DeleteGraph(img["coolTimeWhite"]);
	DeleteGraph(img["coolTimeGreen"]);

	//////////////////////////////////////////////////

	//RemoveFontResourceEx("resources/fonts/APressStart2P-Regular.ttf", FR_PRIVATE, NULL);
};

void GameUI::init() {
	state        = 0;
	frameCounter = 1;

	notice["opacity"] = std::to_string(0.0);
	notice["state"]   = std::to_string(0);
	notice["frame"]   = std::to_string(0);

	enemyHP["currentRatio"] = std::to_string(0);
	enemyHP["ratio"]        = std::to_string(0);

	shieldHP["currentRatio"] = std::to_string(0);
	shieldHP["ratio"]        = std::to_string(0);
};

void GameUI::update() {
	if ((int)FPSCtrl::Get()) {
		frameCounter++;

		if (state == 0) {
			hud["opacity"]      = 0.0f;
			hud["unvisibility"] = 1.0f;

			if (frameCounter % ((int)FPSCtrl::Get() * 3) == 0) state = 1;
		}
		else if (state == 1) {
			for (int i = 0; i < 450; i++) {
				if (hud["opacity"] < 1.0f)      hud["opacity"]      += ((60.0f / FPSCtrl::Get()) * 0.0001f);
				if (hud["unvisibility"] > 0.0f) hud["unvisibility"] -= ((60.0f / FPSCtrl::Get()) * 0.0001f);
			};

			if (frameCounter % ((int)FPSCtrl::Get() * 2) == 0) state = 2;
		}
		else if (state == 2) {
			hud["opacity"]      = 1.0f;
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
				notice["frame"]   = std::to_string(1);
			};
		};
	};

	if (hp["currentRatio"] > hp["ratio"]) hp["ratio"]++;
	if (hp["currentRatio"] < hp["ratio"]) hp["ratio"]--;

	if (exp["currentRatio"] > exp["ratio"]) exp["ratio"]++;
	if (exp["currentRatio"] < exp["ratio"]) exp["ratio"]--;
	if (exp["currentRatio"] == 0) exp["ratio"] = 0;

	if (std::stoi(enemyHP["currentRatio"])) {
		if (std::stoi(enemyHP["currentRatio"]) > std::stoi(enemyHP["ratio"])) enemyHP["ratio"] = std::to_string(std::stoi(enemyHP["ratio"]) + 1);
		if (std::stoi(enemyHP["currentRatio"]) < std::stoi(enemyHP["ratio"])) enemyHP["ratio"] = std::to_string(std::stoi(enemyHP["ratio"]) - 1);
	};

	if (std::stoi(shieldHP["currentRatio"])) {
		if (std::stoi(shieldHP["currentRatio"]) > std::stoi(shieldHP["ratio"])) shieldHP["ratio"] = std::to_string(std::stoi(shieldHP["ratio"]) + 1);
		if (std::stoi(shieldHP["currentRatio"]) < std::stoi(shieldHP["ratio"])) shieldHP["ratio"] = std::to_string(std::stoi(shieldHP["ratio"]) - 1);
	};

	if (InputCtrl::GetKeyState(KEY_INPUT_G) == PRESS) init();
	//if (InputCtrl::GetKeyState(KEY_INPUT_N) == PRESS) notification("武器強化可能！", "Xボタンで確認", "btnX");
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
	DrawCircle(rootRX - 60, rootRY + 60, 40, 0x000000, true);
	if(opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int color = GetColor(0, 0, 0);
	//if (point < 10) {
	//	color = GetColor(255, 214, 0);
	//}
	//else if (point < 20) {
	//	// 未完成
	//};

	DrawCircle(rootRX - 60, rootRY + 60, 40, color, false, 5);

	SetFontSize(40);
	//ChangeFont("Bodoni MT Black Italic", DX_CHARSET_DEFAULT);
	std::string str = std::to_string(point);
	DrawFormatString(((rootRX - 60) - GetDrawFormatStringWidth(str.c_str()) / 2), rootRY + 34, 0xffffff, str.c_str());

	SetFontSize(14);
	//ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);
	DrawFormatString(((rootRX - 58) - GetDrawFormatStringWidth("LEVELUP") / 2), rootRY + 72, 0xffffff, "LEVELUP");
	DrawFormatString(((rootRX - 58) - GetDrawFormatStringWidth("POINT") / 2), rootRY + 84, 0xffffff, "POINT");


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
	DrawBox(lx, ly, rx, ry, 0x000000, true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	DrawBox(lx, ly, rx, ry, GetColor(0, 180, 255), true);

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
	DrawBox(lx, ly, rx, ry, 0x000000, true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	color = GetColor(67, 255, 32);
	if (ratio <= 15)      color = GetColor(255, 0, 0);
	else if (ratio <= 30) color = GetColor(255, 90, 0);

	DrawBox(lx, ly, rx, ry, color, true);

	//SetFontSize(16);
	//ChangeFont("Bahnschrift Light", DX_CHARSET_DEFAULT);
	str = "HP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString(rootLX + 45, rootLY + 30, 0xffffff, str.c_str());


	//////////////////////////////////////////////////
	// CoolTime
	//////////////////////////////////////////////////

	/* int img_blackCircle50 = 0;

	if (img.find("blackCircle50") != img.end()) img_blackCircle50 = img.at("blackCircle50");

	current = 0;
	max     = 0;

	if (coolTime.find("current") != coolTime.end()) current = coolTime.at("current");
	if (coolTime.find("max")     != coolTime.end()) max     = coolTime.at("max");

	int x = rootLX + 80;
	int y = rootLY + 120;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(x, y, 28, 0x000000, true);
	DrawCircleGauge(x, y, ((float)current / (float)max) * 100, img_blackCircle50);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(14);
	str = "回避";
	DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y - 7, 0xffffff, str.c_str()); */


	//////////////////////////////////////////////////
	// スコア
	//////////////////////////////////////////////////

	/* SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(rootLX + 40, rootLY + 80, rootLX + 260, rootLY + 110, 0x000000, true);
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

	SetFontSize(16);
	DrawFormatString(lx + 40, ly + 7 , 0xffffff, "レベルアップメニュー");

	/* ly -= 40;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnB, TRUE);

	DrawFormatString(lx + 40, ly + 5, 0xffffff, "武器持ち替え（仮）"); */

	ly -= 40;
	ry = ly + 30;

	DrawExtendGraph(lx, ly, rx, ry, img_btnA, TRUE);

	DrawFormatString(lx + 40, ly + 7, 0xffffff, "回避");


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
	DrawCircle(x, y, 50, 0x000000, true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (weaponB[0] != 99) {
		//SetFontSize(16);
		str = "Lv. " + std::to_string(weaponB[1]);
		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y + 30, 0xffffff, str.c_str());

		if (weaponB[2]) DrawCircle(x, y, 55, 0xffffff, false, 3);

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
			str = "魔導書";
			break;

		default:
			break;
		};

		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y - 40, 0xffffff, str.c_str());
	};

	x -= 120;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawCircle(x, y, 50, 0x000000, true);
	if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (weaponA[0] != 99) {
		//SetFontSize(16);
		str = "Lv. " + std::to_string(weaponA[1]);
		DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y + 30, 0xffffff, str.c_str());

		if(weaponA[2]) DrawCircle(x, y, 55, 0xffffff, false, 3);

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
	// CoolTime
	//////////////////////////////////////////////////

	int img_blackCircle80 = 0, img_coolTimeWhite = 0, img_coolTimeGreen = 0;

	if (img.find("blackCircle80") != img.end()) img_blackCircle80 = img.at("blackCircle80");
	if (img.find("coolTimeWhite") != img.end()) img_coolTimeWhite = img.at("coolTimeWhite");
	if (img.find("coolTimeGreen") != img.end()) img_coolTimeGreen = img.at("coolTimeGreen");

	current = 0;
	max     = 0;

	if (coolTime.find("current") != coolTime.end()) current = coolTime.at("current");
	if (coolTime.find("max")     != coolTime.end()) max     = coolTime.at("max");

	x -= 120;

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	//DrawCircle(x, y, 50, 0xffffff, true);
	//if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//SetFontSize(16);
	//str = "回避（仮）";
	if (current) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	//DrawFormatString((x - GetDrawFormatStringWidth(str.c_str()) / 2), y - 8, 0x000000, str.c_str());
	//DrawBox(x - 35, y - 35, x + 35, y + 35, 0xffffff, false);
	//DrawCircle(x, y, 50, 0xffffff, false, 2);
	if (current) DrawExtendGraph(x - 34, y - 34, (x - 34) + 70, (y - 34) + 70, img_coolTimeWhite, TRUE);
	else         DrawExtendGraph(x - 34, y - 34, (x - 34) + 70, (y - 34) + 70, img_coolTimeGreen, TRUE);
	if (current) DrawCircleGauge(x, y, ((float)current / (float)max) * 100, img_blackCircle80);
	if (current) if (opacity >= 1.0f) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//////////////////////////////////////////////////

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void GameUI::drawBanner() const {
	std::string title;
	std::string subTitle;
	std::string mode;

	if (banner.find("title")    != banner.end()) title    = banner.at("title");
	if (banner.find("subTitle") != banner.end()) subTitle = banner.at("subTitle");
	if (banner.find("mode")     != banner.end()) mode     = banner.at("mode");

	int lx = 0;
	int ly = (SCREEN_HEIGHT / 3);
	int rx = SCREEN_WIDTH;
	int ry = ly * 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(lx, ly, rx, ry, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (!std::stoi(mode)) {
		int line = 5;
		DrawBox(lx, ly, rx, ly + line, 0xffffff, true);
		DrawBox(lx, ry - line, rx, ry, 0xffffff, true);
	};

	//ChangeFont("");

	SetFontSize(40);
	DrawFormatString((rx / 2) - GetDrawFormatStringWidth(title.c_str()) / 2, 320, 0xffffff, title.c_str());

	SetFontSize(24);
	DrawFormatString((rx / 2) - GetDrawFormatStringWidth(subTitle.c_str()) / 2, 370, 0xffffff, subTitle.c_str());

	if (std::stoi(mode)) {
		int x = lx;
		int y = ly;

		while (x < SCREEN_WIDTH) {
			y = ly;
			DrawTriangle(x + 40, y, x, y + 40, x + 80, y, 0xffffff, true);
			DrawTriangle(x + 80, y, x, y + 40, x + 40, y + 40, 0xffffff, true);

			y = ry - 40;
			DrawTriangle(x + 40, y, x, y + 40, x + 80, y, 0xffffff, true);
			DrawTriangle(x + 80, y, x, y + 40, x + 40, y + 40, 0xffffff, true);

			x += 80;
		};
	};
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
	DrawBox(lx, ly, rx, ry, 0x000000, true);
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

void GameUI::drawShieldHP() const {
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

	if (shieldHP.find("name")    != shieldHP.end()) name    = shieldHP.at("name");
	if (shieldHP.find("current") != shieldHP.end()) current = shieldHP.at("current");
	if (shieldHP.find("max")     != shieldHP.end()) max     = shieldHP.at("max");
	if (shieldHP.find("ratio")   != shieldHP.end()) ratio   = shieldHP.at("ratio");

	int lx = (SCREEN_WIDTH / 2) - 200;
	int ly = 120;
	int rx = (SCREEN_WIDTH / 2) + 200;
	int ry = 140;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * opacity);
	DrawBox(lx, ly, rx, ry, 0x000000, true);
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

	DrawBox(lx, ly, rx, ry, GetColor(0, 110, 255), true);


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
	DrawBox(lx, ly, rx, ry, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lx = lx + 5;
	ly = ly + 5;
	rx = rx - 5;
	ry = ry - 5;

	rx = lx + static_cast<int>((rx - lx) * (ratio / 100.0f));

	int color = GetColor(67, 255, 32);
	if (ratio <= 15)      color = GetColor(255, 0, 0);
	else if (ratio <= 30) color = GetColor(255, 90, 0);

	DrawBox(lx, ly, rx, ry, color, true);

	std::string str = "HP: " + std::to_string(current) + "/" + std::to_string(max);
	DrawFormatString(45, 30, 0xffffff, str.c_str());
};

void GameUI::drawPause() const {
	SetFontSize(16);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, true);
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
	DrawBox(lx, ly, rx, ry, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * std::stod(opacity));
	SetFontSize(18);
	DrawFormatString(lx + 10, ly + 10, 0xffffff, title.c_str());

	SetFontSize(14);
	DrawFormatString(lx + 15, ly + 35, 0xffffff, message.c_str());

	DrawExtendGraph(rx - (ry - ly) + 2, ly + 10, rx - 10, ry - 10, img_btn, TRUE);
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
	if (Ratio >= 0 && Ratio <= 100) exp["currentRatio"] = Ratio;
};

void GameUI::setHP(int Current, int Max, int Ratio) {
	hp["current"] = Current;
	hp["max"]     = Max;
	if (Ratio >= 0 && Ratio <= 100) hp["currentRatio"] = Ratio;
};

void GameUI::setCoolTime(int Current, int Max) {
	coolTime["current"] = Current;
	coolTime["max"]     = Max;
};

void GameUI::setWeapon(std::vector<int> WeaponA, std::vector<int> WeaponB) {
	weapon["A"]["type"]        = WeaponA[0];
	weapon["A"]["level"]       = WeaponA[1];
	weapon["A"]["selected"]    = WeaponA[2];
	weapon["A"]["coolTime"]    = WeaponA[3];
	weapon["A"]["coolTimeMax"] = WeaponA[4];

	weapon["B"]["type"]        = WeaponB[0];
	weapon["B"]["level"]       = WeaponB[1];
	weapon["B"]["selected"]    = WeaponB[2];
	weapon["B"]["coolTime"]    = WeaponB[3];
	weapon["B"]["coolTimeMax"] = WeaponB[4];
};

void GameUI::setEnemy(int Current, int Max) {
	enemy["current"] = Current;
	enemy["max"]     = Max;
};

void GameUI::setEnemyHP(std::string Name, int Current, int Max, int Ratio) {
	enemyHP["name"]    = Name;
	enemyHP["current"] = std::to_string(Current);
	enemyHP["max"]     = std::to_string(Max);
	if (Ratio >= 0 && Ratio <= 100) enemyHP["currentRatio"] = std::to_string(Ratio);
};

void GameUI::setShieldHP(std::string Name, int Current, int Max, int Ratio) {
	shieldHP["name"]    = Name;
	shieldHP["current"] = std::to_string(Current);
	shieldHP["max"]     = std::to_string(Max);
	if (Ratio >= 0 && Ratio <= 100) shieldHP["currentRatio"] = std::to_string(Ratio);
};

void GameUI::setBanner(std::string Title, std::string SubTitle, int Mode) {
	banner["title"]    = Title;
	banner["subTitle"] = SubTitle;
	banner["mode"]     = std::to_string(Mode);
};

void GameUI::setState(int State) {
	state = State;
};

int GameUI::getState() {
	return state;
};