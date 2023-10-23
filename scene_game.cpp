//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 0;
	frameCounter = 0;

	//////////////////////////////////////////////////

	score = 100;
	stock = 3;
	nowStage = 0;

	//////////////////////////////////////////////////

	/*player = new Player;

	Coordinates playerInitialLocation;
	playerInitialLocation.x = SCREEN_WIDTH / 2;
	playerInitialLocation.y = SCREEN_HEIGHT * 0.9;
	player->setLocation(playerInitialLocation);

	Box playerMoveLimit;
	playerMoveLimit.lr.x = SCREEN_WIDTH;
	playerMoveLimit.lr.y = SCREEN_HEIGHT;
	player->setMoveLimit(playerMoveLimit);*/

	//////////////////////////////////////////////////

	gameUI = new GameUI;

	//////////////////////////////////////////////////

	/*for (int i = 0; i < MAX_BULLET; i++) {
		bullet[i] = 0;
	};*/


	img_background = LoadGraph("./resources/images/background.png");
};

GameScene::~GameScene() {
	//delete player;
	delete gameUI;

	DeleteGraph(img_background);
};

Scene* GameScene::update() {
	//if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new TitleScene(false);

	frameCounter++;

	//player->update(this);

	gameUI->update(this);

	//////////////////////////////////////////////////

	// 弾の更新
	//for (int i = 0; i < MAX_BULLET; i++) {
	//	if (bullet[i] != nullptr) {
	//		// プレイヤーが自分以外の弾に当たったら
	//		if (player->checkCollision(bullet[i]) && player->type != bullet[i]->getShooter()) {
	//			player->hit(this);
	//		}
	//		// 敵がプレイヤーの弾に当たったら
	//		/*for (int j = 0; j < ENEMY_MAX; j++) {
	//			if (enemy[j] != nullptr) {
	//				if (enemy[j]->HitSphere(bullet[i]) && enemy[j]->name != bullet[i]->GetParent() && enemy[j]->GetFlg()) {
	//					enemy[j]->Hit(this);
	//					bullet[i]->SetFlg(false);
	//				}
	//			}
	//		}*/
	//		// 弾の更新処理
	//		if (!bullet[i]->update()) {
	//			bullet[i] = nullptr;
	//			delete bullet[i];
	//		}
	//	};
	//};

	//////////////////////////////////////////////////

	return this;
};

void GameScene::draw() const {
	DrawExtendGraph(0, 0, 1280, 720, img_background, TRUE); // 仮

	//DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x001478, true);

	//////////////////////////////////////////////////

	//player->draw();

	gameUI->draw();

	//////////////////////////////////////////////////

	// 弾の描画
	/*for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet[i] != nullptr) bullet[i]->draw();
	};*/
};

//void GameScene::spawnBullet(Collider* _collider, float _angle, int _speed, int _shooter) {
//	for (int i = 0; i < MAX_BULLET; i++) {
//		if (bullet[i] == nullptr) {
//			bullet[i] = new Bullet(_collider->getLocation(), _angle, _speed, _shooter);
//			break;
//		};
//	};
//};