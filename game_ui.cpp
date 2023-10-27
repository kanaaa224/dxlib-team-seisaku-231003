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

	score  = 0;
	level  = 0;
	floor  = 0;
	hp     = 0;
	exp    = 0;
	enemy  = 0;
};

void GameUI::update(GameScene* gameScene) {
	frameCounter++;

	hud["opacity"] = 1.0f;

	//score = gameScene->getScore();

	// 仮
	//weapon["a"];
};

void GameUI::draw() const {
	drawHUD();
};

//void GameUI::drawBackground() const {
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
//	DrawBox(0, 0, SCREEN_WIDTH, 75, GetColor(0, 0, 0), TRUE);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//};

//void GameUI::drawScore() const {
//	std::string str = "SCORE : " + std::to_string(score);
//	//DrawStringToHandle(30, 20, str.c_str(), 0x000000, Resources::Get(FONT, FONTTYPE_EIGHTBIT, FONTSIZE_16), 0xffffff);
//};

void GameUI::drawHUD() const {
	auto it = hud.find("opacity");
	if (it != hud.end()) {
		double opacity = it->second;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * opacity));
	};

	// レベル
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawCircle((SCREEN_WIDTH - 60), 60, 40, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawCircle((SCREEN_WIDTH - 60), 60, 40, GetColor(242, 166, 68), false, 3);

	SetFontSize(50);
	ChangeFont("Bernard MT Condensed", DX_CHARSET_DEFAULT);

	DrawFormatString((SCREEN_WIDTH - 60) - GetDrawFormatStringWidth("2") / 2, 35, 0xffffff, "2");

	SetFontSize(20);

	DrawFormatString((SCREEN_WIDTH - 90) - GetDrawFormatStringWidth("Lv.") / 2, 70, 0xffffff, "Lv.");

	//ChangeFont("", DX_CHARSET_DEFAULT);

	// 経験値
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox((SCREEN_WIDTH - 400), 70, (SCREEN_WIDTH - 110), 90, GetColor(0, 0, 0), true);
	//DrawCircle((SCREEN_WIDTH - 400), 80, 10, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox((SCREEN_WIDTH - 400) + 5, 80 - 5, ((SCREEN_WIDTH - 400) + (290 * 0.8)) - 5, 90 - 5, GetColor(57, 165, 229), true);

	DrawFormatString((SCREEN_WIDTH - 395)/* - GetDrawFormatStringWidth("EXP:") / 2*/, 60, 0xffffff, "EXP:");

	ChangeFont("", DX_CHARSET_DEFAULT);


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