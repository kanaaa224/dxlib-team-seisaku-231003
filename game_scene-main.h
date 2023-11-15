//////////////////////////////////////////////////
// 戦闘シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "Player.h"

#include "weapon.h"
#include "second_weapon.h"

#include "Stage.h"

#include "Slime.h"
#include "Skeleton.h"
#include "Wizard.h"
#include "Common.h"

class GameScene_Main {
private:
	int state, frameCounter;

	GameData gameData;

	Player* player;

	Stage* stage;

	weapon* weaponA;
	second_weapon* weaponB;
	bool bookFlg;

	// 敵 スライム
	Slime* slime[MAX_SLIME_NUM];
	int tmpSlimeNum = 0;

	// 敵 スケルトン
	Skeleton* skeleton[MAX_SKELETON_NUM];
	int tmpSkeletonNum = 0;

	// 敵 魔法使い
	Wizard* wizard[MAX_WIZARD_NUM];
	int tmpWizardNum = 0;

public:
	GameScene_Main();

	~GameScene_Main();

	void update(GameScene* gameScene);

	void draw() const;

	//////////////////////////////////////////////////

	// 初期化
	void init();

	//////////////////////////////////////////////////

	void EnemyInc();

	// スライム
	void SlimeUpdate();
	void SlimeDraw() const;

	// スケルトン
	void SkeletonUpdate();
	void SkeletonDraw() const;

	// 魔法使い
	void WizardUpdate();
	void WizardDraw() const;

	// 弾
	void BulletUpdate();
	void BulletDraw() const;

	//////////////////////////////////////////////////

	// プレイヤーと敵の当たり判定
	void HitEnemy(EnemyBase* enemy);

	void HitCheck();
};