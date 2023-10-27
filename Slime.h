#pragma once
#include "EnemyBase.h"
#include "Player.h"

class Slime :public EnemyBase
{
private:

	float tmpVX;
	float tmpVY;

public:
	Slime();

	void Update(Player* player);
	void Draw();

	//移動処理
	void X();
	void Y();

	//現在のステージでの出現する数を返す
	int GetStageNum();
};

