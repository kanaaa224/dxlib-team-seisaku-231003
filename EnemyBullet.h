#pragma once
#include "SphereCollider.h"
#include "Common.h"
#include <math.h>

class EnemyBullet :public SphereCollider
{
private:
	int img;
	float damage;
	float speed;

	int lifeTimeCnt = 0;

	Location spwLocation;
public:
	EnemyBullet(Location spawnLocation);
	void Update();
	void Draw();

	Vector CaleVector(Location location);
	//get
	int GetDamage();

	int GetlifeTimeCnt();
};
