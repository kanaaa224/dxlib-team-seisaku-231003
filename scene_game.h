//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "scene.h"
#include "Slime.h"
#include "Common.h"

class GameScene : public Scene {
private:
	int state, frameCounter;

	//Player* player;

	GameUI* gameUI;

	//////////////////////////////////////////////////

	int img_background; // 仮

	//敵//
	Slime* slime[MAX_SLIME_NUM];
	int tmpSlimeNum = 0;
	//////////

	int stage = 1;//ステージ

public:
	GameScene();

	~GameScene();

	virtual Scene* update() override;

	virtual void draw() const override;

	//////////////////////////////////////////////////

	int getState() {
		return state;
	};
};