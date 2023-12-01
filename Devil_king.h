#pragma once
#include "EnemyBase.h"
#include "Common.h"
#define DEVILKING_MAX_HP 2000//魔王の最大体力
#define DEVILKING_ATTAK_DAMAGE 10//魔王のダメージ

class Devil_king:public EnemyBase
{
private:
	float shield;//魔王のシールド
public:
	Devil_king();
	~Devil_king();
	void Update(Player* player);
	void Draw() const;
};

