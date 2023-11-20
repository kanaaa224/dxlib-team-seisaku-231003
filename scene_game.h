//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#pragma once

#include "scene.h"

enum GameSceneMode {
	map,          // マップ
	blacksmith,   // 鍛冶屋
	rest,         // 休憩
	main,         // 戦闘
	weaponSelect, // 武器選択
	weaponLevelup // 武器強化
};

enum GameSceneState {
	pause,
	play,
	end
};

class GameScene : public Scene {
private:
	int mode, state, frameCounter;

	//////////////////////////////////////////////////

	Player* player;

	bool swordHitFlg; //魔剣の連続ヒットカウント用
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
	//弾
	EnemyBullet* enemyBullet[MAX_BULLET_NUM];
	int tmpBulletNum = 0;
	//ミノタウロス
	Minotaur* minotaur;

	GameUI* gameUI;

	//////////////////////////////////////////////////

	Map* map;

	Weapon_Selection* weaponSelect;
	bool weapon_selected;

	WeaponLevelUp* weaponLevelup;
	bool restor_cursor_position; // レベルアップ画面のカーソル位置を元に戻すか

	Blacksmith* blacksmith;

	//////////////////////////////////////////////////

	int hp;    // プレイヤー体力
	int exp;   // 経験値
	int level; // レベル
	int point; // ポイント（武器強化に使用）

	int currentStage; // 現在のステージ

public:
	GameScene();

	~GameScene();

	virtual Scene* update() override;

	virtual void draw() const override;

	//////////////////////////////////////////////////

	// 初期化
	void init();

	// 敵の数
	int getEnemiesNum(int);

	// 累計経験値取得
	int getEXP();

	// レベル取得
	int getLevel();

	//////////////////////////////////////////////////

	void HitCheck();

	//プレイヤーと敵の当たり判定
	bool HitEnemy(EnemyBase* enemy);

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
	void EnemyBulletUpdate(Location location);
	void EnemyBulletDraw() const;
	//ミノタウロス
	void MinotaurUpdate();
	void MinotaurDraw() const;
};