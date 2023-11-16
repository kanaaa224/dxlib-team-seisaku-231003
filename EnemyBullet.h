#pragma once
#include "EnemyBase.h"
#include "Common.h"
#include <math.h>

class EnemyBullet :public EnemyBase
{
private:

	int lifeTimeCnt = 0;

public:
	EnemyBullet(Location spawnLocation);
	void Update(Player*player);
	void Draw() const;

	//get
	int GetDamage();

	int GetlifeTimeCnt();
};
