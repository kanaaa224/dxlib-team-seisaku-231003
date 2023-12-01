#pragma once
#include "EnemyBase.h"
#include "EnemyBullet.h"

class BigEnemyBullet :public EnemyBase
{
private:
	int lifeTimeCnt = 0;

public:
	BigEnemyBullet(Location spawnLocation, Player* player);
	~BigEnemyBullet();
	void Update(Player* player);
	void Draw() const;
};