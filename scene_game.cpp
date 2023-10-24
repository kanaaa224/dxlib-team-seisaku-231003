//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 0;
	frameCounter = 0;

	/*player = new Player;*/

	gameUI = new GameUI;

	//////////////////////////////////////////////////

	img_background = LoadGraph("./resources/images/background.png"); // 仮
};

GameScene::~GameScene() {
	//delete player;

	delete gameUI;

	//////////////////////////////////////////////////

	DeleteGraph(img_background); // 仮
};

Scene* GameScene::update() {
	frameCounter++;

	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene(); // 仮

	//player->update(this);

	gameUI->update(this);

	return this;
};

void GameScene::draw() const {
	DrawExtendGraph(0, 0, 1280, 720, img_background, TRUE); // 仮

	//player->draw();

	gameUI->draw();
};