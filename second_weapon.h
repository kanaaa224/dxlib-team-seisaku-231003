#pragma once
#include "weapon.h"

#define SPEAR_MAX_MOVE 180.0f

enum second_weapon_type
{
	spear,
	frail,
	book,
};

class second_weapon
{
private:
	int weaponType;
	int weaponLevel;
	bool levelUpFlg;

	Location location;

	Vector weaponVec;
	Vector baseVec;
	Vector unitVec;

	float collisionX, collisionY;	//回転後の座標、当たり判定に使う
	Vector collisionVec;

	float rot;				//回転
	float relativeRot;		//プレイヤーのベクトルを中心とした回転
	float maxRot;			//最大どれくらい回転するか
	float weaponAngle;

	int coolTime;	//クールタイムを計算する変数
	int maxCoolTime;  //クールタイムの値
	bool isAttacking;	//攻撃中かどうか
	int damage;

	int sword_img;
	int dagger_img;
	int greatsword_img;


	float tmp, tmp1;


	float spear_move_cnt;
	Vector spear_move;

public:
	second_weapon();
	second_weapon(int type);
	~second_weapon();

	void Update(float cursorX, float cursorY, Location playerLocation);
	void Draw() const;

	void SetWeaponType(int type);

	void LevelUpDebug(int num);
	void LevelState();

	bool WeaponCollision(Location enemyLocation, float radius);

	//武器レベルをセット
	void SetWeaponLevel(int num) {
		weaponLevel = num;
		LevelState();
	}
	//武器レベルを取得
	int GetWeaponLevel() { return weaponLevel; }

	bool GetLevelUpFlg() { return levelUpFlg; }
	int GetDamage() { return damage; }
	int GetWeaponType() { return weaponType; }
};

