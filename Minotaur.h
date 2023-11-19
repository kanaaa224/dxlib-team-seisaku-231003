#pragma once
#include "EnemyBase.h"

class Minotaur :public EnemyBase
{
private:
	int tackleCoolTimeCnt;//タックルした後のクールタイム
	int tacklePrepTimeCnt;//タックル準備時間
	bool tackleFlg;//

public:
	Minotaur();
	void Update();
	void Draw() const;

	void Tackle();//タックル時の移動量を計算
	void Roar();//咆哮
};

