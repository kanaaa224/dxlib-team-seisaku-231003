#pragma once
#include "EnemyBase.h"
#include "Common.h"
#define DEVILKING_MAX_HP 2000//魔王の最大体力
#define DEVILKING_ATTAK_DAMAGE 10//魔王のダメージ
#define BIG_BULLET_CREATE_TIME  SECOND_FRAME(3)

class Devil_king:public EnemyBase
{
private:
	float shield;//魔王のシールド
	bool shieldFlg;//現在、魔王がシールドを持っているかどうか

	bool bigBulletCreateFlg = false;
	int bigBulletCreateCounter = 0;

public:
	Devil_king();
	~Devil_king();
	void Update(Player* player);
	void Draw() const;

	//ビーム
	void BeamUpdate();
	void BeamDraw() const;

	//Get関数
	bool GetBigBulletCreateFlg() {
		return bigBulletCreateFlg;
	}
	float GetHP() {
		return hp;
	}

	//Set関数
	void SetBigBulletCreateFlg(bool flg) {
		bigBulletCreateFlg = flg;
	}
};

