#pragma once
#include "EnemyBase.h"
#include "Player.h"
#include "weapon.h"

class Stage;

class Slime :public EnemyBase
{
private:

public:
	Slime(int arrayNum, int SlimeMaxNum);

	void Update(int arrayNum, Player* player, weapon* w, Stage stage);
	void Draw(int arrayNum) const;

	//移動処理
	void X();
	void Y();

	//スライムのダメージ取得
	float GetSlimeDamage();
};

