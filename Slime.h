#pragma once
#include "EnemyBase.h"
#include "Player.h"

class Slime :public EnemyBase
{
private:

	float tmpVX;
	float tmpVY;

public:
	Slime(int arrayNum);

	void Update(int arrayNum, Player* player);
	void Draw();

	//移動処理
	void X();
	void Y();

	//現在のステージでの出現する数を返す
	int GetStageNum();

	//スライムのダメージ取得
	int GetSlimeDamage();

	//
	void SetHitVector(Vector v);
};

