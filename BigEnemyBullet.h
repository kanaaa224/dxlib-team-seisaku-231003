#pragma once
#include "EnemyBase.h"
#include "Common.h"

#define LIFETIME 3.2

class BigEnemyBullet :public EnemyBase
{
private:
	int lifeTimeCnt = 0;
	bool redDrawFlg = false;
	int redDrawCounter = 0;

	bool doOnesFlg = false;
	//武器との当たり判定
	bool hitWeapon = false;
public:
	BigEnemyBullet(Location spawnLocation, Player* player);
	~BigEnemyBullet();
	void Update(Player* player);
	void Draw() const;

	//爆発１秒前の赤い色の点滅表示
	void RedFlashing();

	//Get関数
	int GetlifeTimeCnt() {
		return lifeTimeCnt;
	}

	//Set関数
	void SetHitWeapon(bool flg) {
		hitWeapon = flg;
	}
};