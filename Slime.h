#pragma once
#include "EnemyBase.h"
#include "Player.h"
#include "weapon.h"

class Slime :public EnemyBase
{
private:

	float tmpVX;
	float tmpVY;

	int EF_hitHp;

public:
	Slime(int arrayNum);

	void Update(int arrayNum, Player* player ,weapon* w);
	void Draw(int arrayNum);

	//移動処理
	void X();
	void Y();

	//現在のステージでの出現する数を返す
	int GetStageNum();

	//スライムのダメージ取得
	int GetSlimeDamage();
};

