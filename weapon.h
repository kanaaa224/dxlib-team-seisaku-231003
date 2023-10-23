#pragma once

struct Vector
{
	float x;
	float y;
	float length;
};


class weapon {
private:
	Vector weaponVec;
	Vector baseVec;

	float collisionX, collisionY;

	float rot;				//回転
	float relativeRot;		//プレイヤーのベクトルを中心とした回転

public:
	weapon();
	~weapon();

	void Update();
	void Draw() const;
};

