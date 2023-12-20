#pragma once
class Player;

#define d_r(_d) _d * (M_PI / 180)
#define r_d(_r) _r * (180 / M_PI)

#define INIT_COOLTIME_SWORD  60
#define INIT_COOLTIME_DAGGER  30
#define INIT_COOLTIME_GREATSWORD  90

#define INIT_ROTATION_SWORD  60.0f
#define INIT_ROTATION_DAGGER  60.0f
#define INIT_ROTATION_GREATSWORD  90.0f

#define INIT_DAMAGE_SWORD  10
#define INIT_DAMAGE_DAGGER  6
#define INIT_DAMAGE_GREATSWORD  20

#define AVOIDANCE_DAMAGE_RADIUS 100
#define MAX_THROW_DAGGER 64

#define MAX_DUST 64

#define ATTACKBUF 2.0f

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

struct Dust
{
	Location l;
	Vector v;
	bool flg;
	float radius;
	int endcnt;
	int startcnt;
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

	int fps;

	int coolTime;	//クールタイムを計算する変数
	int maxCoolTime;  //クールタイムの値
	int maxCoolTimeTmp;  //クールタイムの値
	bool isAttacking;	//攻撃中かどうか
	bool oldIsAttacking;	//攻撃中かどうか
	int damage;

	int sword_img;
	int dagger_img;
	int greatsword_img;
	int attackbuf_img;
	int tornado_img;
	int arrow_img;

	int daggerslash_img;

	int sword_level7_img;
	int sword_level8_img;
	int dagger_level7_img;
	int dagger_level8_img;
	int greatsword_level7_img;
	int greatsword_level8_img;


	//int sword_sound;
	//int dagger_sound;
	//int greatSword_sound;

	bool soundFlg;

	float attackbuf;

	//仮　プレイヤーのステータス
	float P_speed;
	float   P_cooltime;
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

	//dust
	Dust dust[MAX_DUST];
	int dustcnt;
	float dustDamage;


	//総合ダメージ
	int totalDamage;

	float tmp, tmp1;
public:
	weapon();
	weapon(int type);
	~weapon();

	void Update(float cursorX, float cursorY, Location playerLocation, Player* player);
	void Draw() const;

	void SetWeaponType(int type);

	void LevelState();

	bool WeaponCollision(Location enemyLocation, float radius);

	bool SpawnSwordSlash();
	void SwordSlashAnim();	//最終強化１の斬撃を飛ばす

	void SwordLevel8(Player* player);
	void SwordLevel8Heel(Player* player);


	bool SpawnThrowDagger(int num);
	void ThrowDaggerAnim();

	bool SpawnDust();
	void DustAnim();
	bool DustCollision(Location enemyLocation, float radius);

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
			if (hitCnt > 0) {
				hitCnt--;
			}
		}
	}

	void SetAttackBuf(bool f) {
		if (f) {
			if (attackbuf == ATTACKBUF || attackbuf == 1.0f) {
				if (attackbuf == 1.0f) {
					attackbuf = 1.5f;
				}
				else {
					attackbuf = attackbuf * 1.5f;
				}
			}
			
		}
		else {
			if (attackbuf >= ATTACKBUF) {
				attackbuf = ATTACKBUF;
			}
			else {
				attackbuf = 1.0f;
			}
		}
	}

	void SetAvoidanceDamageFlg(bool f) {
		avoidanceDamageFlg = f;
	}
	//武器レベルを取得
	int GetWeaponLevel() { return weaponLevel; }

	bool GetLevelUpFlg() { return levelUpFlg; }
	int GetCoolTime() { return coolTime; }
	int GetMaxCoolTime() { return maxCoolTime; }
	int GetDamage() { return damage; }
	int GetWeaponType() { return weaponType; }
	bool GetIsAttacking() { return isAttacking; }
	bool GetOldIsAttacking() { return oldIsAttacking; }
	float GetDustDamage() { return dustDamage; }
	float GetAttackBuf() { return attackbuf; }

	int GetAttackBufImg() { return attackbuf_img; }
	int GetArrowImg() { return arrow_img; }

	void InitWeapon();

	//武器のレベルが上がる際、プレイヤーのステータスも上がるため
	//その数値を返す関数
	float GetP_Speed() { return P_speed; }
	float GetP_AvoidanceCooltime() { return P_cooltime; }
	float GetP_Upperlimitlimit() { return P_limit;}

	float GetMaxRot() { return maxRot; }

	int GetTotalDamage() { return totalDamage; }
	void AddTotalDamage();
	void AddTotalDamageDust();

};

