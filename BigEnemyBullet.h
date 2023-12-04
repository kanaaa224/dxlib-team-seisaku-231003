#pragma once
#include "EnemyBase.h"
#include "Common.h"

#define LIFETIME 6

class BigEnemyBullet :public EnemyBase
{
private:
	int lifeTimeCnt = 0;
	bool redDrawFlg = false;
	int redDrawCounter = 0;
public:
	BigEnemyBullet(Location spawnLocation, Player* player);
	~BigEnemyBullet();
	void Update(Player* player);
	void Draw() const;

	void RedFlashing();

	//Get関数
	int GetlifeTimeCnt() {
		return lifeTimeCnt;
	}
};