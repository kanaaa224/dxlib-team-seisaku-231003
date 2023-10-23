//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "scene.h"
#include "Stage.h"

class GameScene : public Scene {
private:
	int state, frameCounter;

	//Player* player;

	Stage* stage;
	GameUI* gameUI;

	//////////////////////////////////////////////////

	int img_background; // 仮

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