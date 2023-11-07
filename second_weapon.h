#pragma once
#include "weapon.h"

#define INIT_COOLTIME_SPEAR  80
#define INIT_COOLTIME_FRAIL  120
#define INIT_COOLTIME_BOOK  60

#define INIT_ROTATION_SPEAR  60.0f
#define INIT_ROTATION_FRAIL  60.0f
#define INIT_ROTATION_BOOK  90.0f

#define INIT_DAMAGE_SPEAR 10
#define INIT_DAMAGE_FRAIL 10
#define INIT_DAMAGE_BOOK  5






#define SPEAR_MAX_MOVE 45.0f
#define MAX_BULLETS_NUM 100

enum second_weapon_type
{
	spear,
	frail,
	book,
};

struct Bullet
{
	Vector v;
	Location l;
	bool flg;
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

	int spear_img;
	int frail_img;
	int book_img;


	float tmp, tmp1;


	float spear_move_cnt;
	Vector spear_move;
	Location spearlocation;

	float frailRadius;
	Vector frailVec;
	Location frailLcation;
	Location frailLcationCursor;
	float frailLength;
	float frailLengthCursor;
	bool isFrailAttacking;

	Vector book_move;
	Bullet bullets[MAX_BULLETS_NUM];



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


	bool SpearAnim();

	void SpawnBookBullets();
	void MoveBookBullet();


	bool FrailAnim();

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

