//////////////////////////////////////////////////
// ゲームUI
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameUI::GameUI() {
	//LoadGraph();

	init();
};

GameUI::~GameUI() {
	//DeleteGraph();
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

	//score = gameScene->getScore();

	// 仮
	//weapon["a"];
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