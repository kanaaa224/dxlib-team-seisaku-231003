#pragma once
#include "EnemyBase.h"
#define BOX_MAX_WIDTH  50  //タックル攻撃予測の矩形の最大の幅
#define BOX_MAX_LENGTH 500 //タックル攻撃予測の矩形の長さ
#define TACKLE_SPEED 5	//タックルのスピード

class Minotaur :public EnemyBase
{
private:
	float pLength;//プレイヤーとの距離
	//----------タックル----------//
	int tackleCoolTimeCnt;//タックルした後のクールタイムカウント変数
	int tackleCoolTime;//タックルのクールタイム
	int tackleSpeed;//タックルまでの速度
	int tacklePrepTimeCnt;//タックル準備時間
	bool tackleFlg;//現在がタックル状態かどうか
	bool doOneFlg;//プレイヤーとの距離を一回だけとる
	bool coolTimeFlg;//現在がタックルのクールタイム中か

	int tackleCnt;//現在が何回目のタックルか？

	//薄い赤色の矩形
	float boxX_a;
	float boxY_a;
	float boxX_d;//ボックスの倍率
	float boxY_d;
	float drawBoxY_a;

	//濃い赤色の矩形
	int lineSize;
	int lineSizeChageCnt;

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

