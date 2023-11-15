#pragma once
#include "SphereCollider.h"

class Bullet:public SphereCollider
{
private:
	int img;
	float damage;
	float speed;
public:
	Bullet(Location spawnLocation);
	void Update();
	void Draw();

	Vector CaleVector(Location location);
	//get
	int GetDamage();
};
