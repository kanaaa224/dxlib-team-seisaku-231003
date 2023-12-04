#pragma once
#include "EnemyBase.h"

class SmallEnemyBullet :public EnemyBase
{
private:

public:
	SmallEnemyBullet(Location spawnLocation);
	~SmallEnemyBullet();
	void Update();
	void Draw() const;
};

