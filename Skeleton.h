#pragma once
#include "EnemyBase.h"
#include "Player.h"
#include "weapon.h"

class Stage;

class Skeleton :public EnemyBase
{
private:

	bool is_area;

public:
	Skeleton(int arrayNum,int SkeletonMaxNum);

	void Update(int arrayNum, Player* player, weapon* w, Stage stage);
	void Draw(int arrayNum);

	//移動処理
	void X();
	void Y();

	//現在のステージでの出現する
	int GetStageNum();

	//スケルトンのダメージ取得
	float GetSkeletonDamage();
};

