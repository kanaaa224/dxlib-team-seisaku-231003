#pragma once
#include "EnemyBase.h"
#define BOX_MAX_WIDTH  50	//タックル攻撃予測の矩形の最大の幅
#define BOX_MAX_LENGTH 500	//タックル攻撃予測の矩形の長さ
#define TACKLE_SPEED   10	//タックルのスピード
#define ROAR_RADIU     250	//咆哮の半径

class Minotaur :public EnemyBase
{
private:
	int debugCnt;

	float pLength;//プレイヤーとの距離
	//----------タックル----------//
	int tackleCoolTimeCnt;		//タックルした後のクールタイムカウント変数
	int tackleCoolTime;			//タックルのクールタイム
	int tackleSpeed;			//タックルまでの速度
	int tacklePrepTimeCnt;		//タックル準備時間
	bool tackleFlg;				//現在がタックル状態かどうか
	bool doOneFlg;				//プレイヤーとの距離を一回だけとる
	bool coolTimeFlg;			//現在がタックルのクールタイム中か
	bool roarStartFlg;

	int nowTackleCnt;			//タックル中のカウント変数

	Location tackleTmpL;
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
	int roarCnt;//
	int roarRadius;
	bool roarFlg;//
	bool roarFinFlg;
	bool roarEffectFlg;
	bool roarEffectFinFlg;

public:
	Minotaur();
	void Update(Player* player);
	void Draw() const;

	//タックル
	void TackleUpdate();
	void TackleDraw() const;

	//
	float M_PLX(float location_X);
	float M_PLY(float location_Y);

	//咆哮
	void RoarUpdate();
	void RoarEffectUpdate();
	void RoarDraw() const;
	void RoarEffectDraw() const;
};

