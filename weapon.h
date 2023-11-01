#pragma once
#define INIT_COOLTIME_SWORD  150
#define INIT_COOLTIME_DAGGER  60
#define INIT_COOLTIME_GREATSWORD  300

#define INIT_ROTATION_SWORD  60.0f
#define INIT_ROTATION_DAGGER  60.0f
#define INIT_ROTATION_GREATSWORD  90.0f

#define INIT_DAMAGE_SWORD  7
#define INIT_DAMAGE_DAGGER  4
#define INIT_DAMAGE_GREATSWORD  25

struct Vector
{
	float x;
	float y;
	float length;
};

enum weapontype
{
	sword,
	dagger,
	greatSword,
	none = 99
};

struct Location;

class weapon {
private:
	int weaponType;
	int weaponLevel;
	bool levelUpFlg;


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
public:
	weapon();
	weapon(int type);
	~weapon();

	void Update(float cursorX, float cursorY);
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

