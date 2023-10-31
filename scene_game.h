//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#pragma once

#include "scene.h"
#include "Stage.h"
#include "weapon.h"
#include "Player.h"
#include "Slime.h"
#include "Common.h"
#include"scene_weapon.h"
#include "scene_gameclear.h"
#include "scene_levelup.h"

class GameScene : public Scene {
private:
	int state, frameCounter;

	Player* player;
	Stage* backimg;
	weapon* Weapon;
	GameUI* gameUI;

	//////////////////////////////////////////////////

	int img_background; // 仮

	//敵//
	Slime* slime[MAX_SLIME_NUM];
	int tmpSlimeNum = 0;

	//シーン
	Weapon_Selection* weapon_selection;
	WeaponLevelUp* weapon_level_up;

	//////////

	int stage = 1;//ステージ

	bool is_weapon_selct;

	bool open_level_up;

	
	bool is_hit;	//仮で当たったか
public:
	GameScene();

	~GameScene();

	virtual Scene* update() override;

	virtual void draw() const override;

	//////////////////////////////////////////////////

	int getState() {
		return state;
	};

	void HitCheck();
};