#pragma once
#include "EnemyBase.h"

class Minotaur :public EnemyBase
{
private:
	//----------タックル----------//
	int tackleCoolTimeCnt;//タックルした後のクールタイム
	int tacklePrepTimeCnt;//タックル準備時間
	bool tackleFlg;//現在がタックル状態かどうか

	//薄い赤色の矩形
	float boxX_a;
	float boxY_a;

	//濃い赤色の矩形
	int lineSize;

	//----------咆哮----------//

public:
	Minotaur();
	void Update(Player* player);
	void Draw() const;

	//タックル
	void TackleUpdate();
	void TackleDraw() const;

	//咆哮
	void RoarUpdate();
	void RoarDraw() const;
};

