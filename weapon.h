#pragma once
class Player;

#define d_r(_d) _d * (M_PI / 180)
#define r_d(_r) _r * (180 / M_PI)

#define INIT_COOLTIME_SWORD  120
#define INIT_COOLTIME_DAGGER  60
#define INIT_COOLTIME_GREATSWORD  210

#define INIT_ROTATION_SWORD  60.0f
#define INIT_ROTATION_DAGGER  60.0f
#define INIT_ROTATION_GREATSWORD  90.0f

#define INIT_DAMAGE_SWORD  7
#define INIT_DAMAGE_DAGGER  4
#define INIT_DAMAGE_GREATSWORD  25

#define AVOIDANCE_DAMAGE_RADIUS 100
#define MAX_THROW_DAGGER 64

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

struct Location
{
	float x;
	float y;
};

struct SwordSlash
{
	Location l;
	Vector v;
	bool flg;
	Location collsion1;
	Location collsion2;
};

struct ThrowDagger
{
	Location l;
	Vector v;
	bool flg;
	float relativeRot;
	float rot;
	Vector unit;
};


class weapon {
private:
	int weaponType;
	int weaponLevel;
	bool levelUpFlg;

	Location location;
	Vector playerVector;

	Vector weaponVec;
	Vector baseVec;
	Vector unitVec;

	float collisionX, collisionY;	//回転後の座標、当たり判定に使う
	Vector collisionVec;

	float rot;				//回転
	float relativeRot;		//プレイヤーのベクトルを中心とした回転
	float maxRot;			//最大どれくらい回転するか
	float weaponAngle;
	float rotSpeed;

	int coolTime;	//クールタイムを計算する変数
	int maxCoolTime;  //クールタイムの値
	int maxCoolTimeTmp;  //クールタイムの値
	bool isAttacking;	//攻撃中かどうか
	bool oldIsAttacking;	//攻撃中かどうか
	int damage;

	int sword_img;
	int dagger_img;
	int greatsword_img;

	//仮　プレイヤーのステータス
	float P_speed;
	int   P_cooltime;
	float P_limit;

	//飛ぶ斬撃
	SwordSlash swordSlash[10];
	int slash_img;
	int slashFlg;
	float slashRot;
	Location sl[100];

	//魔剣
	int hitCnt;
	int fpsCnt;
	float heelAmount;

	//投げナイフ
	ThrowDagger throwDagger[MAX_THROW_DAGGER];
	//回避中のダメージ
	bool avoidanceDamageFlg;

	float tmp, tmp1;
public:
	weapon();
	weapon(int type);
	~weapon();

	void Update(float cursorX, float cursorY, Location playerLocation, Player* player);
	void Draw() const;

	void SetWeaponType(int type);

	void LevelUpDebug(int num);
	void LevelState();

	bool WeaponCollision(Location enemyLocation, float radius);

	bool SpawnSwordSlash();
	void SwordSlashAnim();	//最終強化１の斬撃を飛ばす

	void SwordLevel8(Player* player);


	bool SpawnThrowDagger(int num);
	void ThrowDaggerAnim();

	//武器レベルをセット
	void SetWeaponLevel(int num) {
		weaponLevel = num;
		LevelState();
	}
	void SetCoolTime(float num, bool flg) {
		if (flg) {
			maxCoolTimeTmp = maxCoolTime;
			maxCoolTime = (int)maxCoolTime * num;
			coolTime = maxCoolTime;
		}
		else
		{
			maxCoolTime = maxCoolTimeTmp;
			LevelState();
		}
	}

	void SetHitCnt(bool flg) {
		if (flg) {
			hitCnt++;
		}
		else {
			hitCnt = 0;
		}
	}
	//武器レベルを取得
	int GetWeaponLevel() { return weaponLevel; }

	bool GetLevelUpFlg() { return levelUpFlg; }
	int GetDamage() { return damage; }
	int GetWeaponType() { return weaponType; }
	bool GetIsAttacking() { return isAttacking; }
	bool GetOldIsAttacking() { return oldIsAttacking; }
};

