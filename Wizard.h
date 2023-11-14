#pragma once
#include "EnemyBase.h"
#include "Player.h"
#include "weapon.h"

class Wizard :public EnemyBase
{
private:

public:
	Wizard(int arrayNum, int WizardMaxNum);

	void Update(int arrayNum, Player* player, weapon* w, Stage stage);
	void Draw(int arrayNum);

	//移動処理
	void X();
	void Y();

	//スライムのダメージ取得
	float GetWizardDamage();
};

