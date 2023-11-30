#pragma once
#include "EnemyBase.h"
#include "Common.h"
#include <math.h>

class EnemyBullet :public EnemyBase
{
private:

	int lifeTimeCnt = 0;

	float angle;

public:
	EnemyBullet(Location spawnLocation , Player* player);
	~EnemyBullet();

	void Update(Player* player, Wizard* enemy);
	void Draw() const;

	//get
	int GetDamage();

	int GetlifeTimeCnt();
};
