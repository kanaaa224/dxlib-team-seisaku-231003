#pragma once

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



class weapon {
private:
	int weaponType;



	Vector weaponVec;
	Vector baseVec;

	float collisionX, collisionY;	//回転後の座標、当たり判定に使う

	float rot;				//回転
	float relativeRot;		//プレイヤーのベクトルを中心とした回転
	float maxRot;			//最大どれくらい回転するか

	int coolTime;	//クールタイム
	bool isAttacking;	//攻撃中かどうか

public:
	weapon();
	weapon(int type);
	~weapon();

	void Update();
	void Draw() const;

	void SetWeaponType(int type);
};

