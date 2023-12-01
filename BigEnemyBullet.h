#pragma once
#include "EnemyBase.h"
#include "Common.h"

class BigEnemyBullet :public EnemyBase
{
private:
	int lifeTimeCnt = 0;
	bool redDrawFlg = false;
	int redDrawInterval = 200;
	int redDrawCounter = 0;
public:
	BigEnemyBullet(Location spawnLocation, Player* player);
	~BigEnemyBullet();
	void Update(Player* player);
	void Draw() const;

	//Get関数
	int GetlifeTimeCnt() {
		return lifeTimeCnt;
	}
};