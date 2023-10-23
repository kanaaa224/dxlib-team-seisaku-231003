//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "scene.h"

class GameScene : public Scene {
private:
	int state, frameCounter;

	int score, stock, nowStage;

	int img_background; // 仮

	//////////////////////////////////////////////////

	//Player* player;

	GameUI* gameUI;

public:
	GameScene();

	~GameScene();

	virtual Scene* update() override;

	virtual void draw() const override;

	//////////////////////////////////////////////////

	int getScore() {
		return score;
	};

	int getStock() {
		return stock;
	};

	int getNowStage() {
		return nowStage;
	};

	//////////////////////////////////////////////////

	void setStock(int Stock) {
		stock = Stock;
	};

	//////////////////////////////////////////////////

	//void spawnBullet(Collider* _collider, float _angle, int _speed, int _shooter);
};