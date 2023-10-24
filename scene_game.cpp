//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 0;
	frameCounter = 0;

	player = new Player;
	backimg = new Stage;
	Weapon = new weapon;
	gameUI = new GameUI;

	//////////////////////////////////////////////////

	//img_background = LoadGraph("./resources/images/background.png"); // 仮
};

GameScene::~GameScene() {

	delete player;
	delete backimg;
	delete Weapon;
	delete gameUI;

	//////////////////////////////////////////////////

	//DeleteGraph(img_background); // 仮
};

Scene* GameScene::update() {
	frameCounter++;

	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene(); // 仮

	//敵//
	if (tmpSlimeNum < SLIME_1_STAGE_NUM) {
		slime[tmpSlimeNum] = new Slime;
		tmpSlimeNum++;
	}

	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update();
			}
		}
	}

	if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
		Weapon->SetWeaponType(sword);
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
		Weapon->SetWeaponType(dagger);
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
		Weapon->SetWeaponType(greatSword);
	}
	////////////

	player->update();
	Weapon->Update();
	//stage->update(this);
	gameUI->update(this);

	return this;
};

void GameScene::draw() const {
	//DrawExtendGraph(0, 0, 1280, 720, img_background, TRUE); // 仮

	

	//backimg->draw();
	Weapon->Draw();
	player->draw();

	//敵//
	if (stage == 1) {
		for (int i = 0; i < MAX_SLIME_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Draw();
			}
		}
	}
	////////////
	//gameUI->draw();
};