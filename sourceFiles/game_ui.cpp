//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

void GameUI::init() {
	score    = 0;
	stock    = 0;
	timeLeft = 0;
	nowStage = 0;
	mode     = 0;
};

void GameUI::update(GameScene* gameScene) {
	score = gameScene->getScore();
	stock = gameScene->getStock();
	nowStage = gameScene->getNowStage();

	//timeLeft = _timeLeft;
	//mode     = _mode;
};

void GameUI::draw() const {
	/* drawScore();
	drawLevel();
	drawFloor();
	drawHP();
	drawEXP();
	drawEnemy();
	drawWeapon(); */
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