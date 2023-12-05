#pragma once
#include "EnemyBase.h"

class SmallEnemyBullet :public EnemyBase
{
private:
	int lifeTimeCnt = 0;
public:
	SmallEnemyBullet(Location spawnLocation);
	~SmallEnemyBullet();
	void Update(Player* player);
	void Draw() const;

	//Get関数
	int GetLifeTimeCnt();
};

