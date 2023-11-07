#pragma once
#include "EnemyBase.h"
#include "Player.h"
#include "weapon.h"

class Stage;

class Slime :public EnemyBase
{
private:

	float tmpVX;
	float tmpVY;

	int EF_hitHp;

	bool is_area;

public:
	Slime(int arrayNum, int SlimeMaxNum);

	void Update(int arrayNum, Player* player, weapon* w, Stage stage);
	void Draw(int arrayNum);

	//移動処理
	void X();
	void Y();

	//現在のステージでの出現する数を返す
	int GetStageNum();

	//スライムのダメージ取得
	float GetSlimeDamage();
};

