//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#pragma once

#include "scene.h"

enum GameSceneMode {
	main,          // 戦闘
	map,           // マップ
	weaponSelect,  // 武器選択
	weaponLevelup, // 武器強化
	blacksmith,    // 鍛冶屋
	rest           // 休憩
};

enum GameSceneState {
	pause, // ポーズは mode がどの状態でも発動
	play
};

class GameScene : public Scene {
private:
	int state, frameCounter;

	//////////////////////////////////////////////////

	Player* player;

	weapon* weaponA;
	second_weapon* weaponB;
	bool bookFlg = false;

	Stage* stage;

	//敵//
	//スライム
	Slime* slime[MAX_SLIME_NUM];
	int tmpSlimeNum = 0;
	//スケルトン
	Skeleton* skeleton[MAX_SKELETON_NUM];
	int tmpSkeletonNum = 0;
	//魔法使い
	Wizard* wizard[MAX_WIZARD_NUM];
	int tmpWizardNum = 0;

	GameUI* gameUI;

	//////////////////////////////////////////////////

	Map* map;
	Weapon_Selection* weaponSelect;
	WeaponLevelUp* weaponLevelup;
	Blacksmith* blacksmith;

	//////////////////////////////////////////////////

	int mode;

	int exp, level; // 仮

	int nowStage = 1;//ステージ
	//bool hitFlg = false;
	//int hitFrameCounter = 0;

	bool is_weapon_select;
	bool weapon_selected;

	bool open_level_up;				// レベルアップ画面が開いているか
	bool restor_cursor_position;	// レベルアップ画面のカーソル位置を元に戻すか

	bool open_blacksmith;			// 鍛冶テスト用

public:
	GameScene();

	~GameScene();

	virtual Scene* update() override;

	virtual void draw() const override;

	//////////////////////////////////////////////////

	void HitCheck();

	//プレイヤーと敵の当たり判定
	void HitEnemy(EnemyBase* enemy);

	//////////////////////////////////////////////////

	//敵
	void EnemyInc();
	//スライム
	void SlimeUpdate();
	void SlimeDraw() const;
	//スケルトン
	void SkeletonUpdate();
	void SkeletonDraw() const;
	//魔法使い
	void WizardUpdate();
	void WizardDraw() const;
	//弾
	void BulletUpdate();
	void BulletDraw() const;
};