#pragma once
#include "EnemyBase.h"
#include "Common.h"
#define DEVILKING_MAX_HP 2000//魔王の最大体力
#define DEVILKING_ATTAK_DAMAGE 10//魔王のダメージ
#define BIG_BULLET_CREATE_TIME  SECOND_FRAME(3)
#define MAX_SHIELD 100//シールドの最大値
#define DOWN_TIME SECOND_FRAME(7)//ダウンタイム

class Devil_king:public EnemyBase
{
private:
	//シールド
	float shield;//魔王のシールド
	bool shieldFlg;//シールドが０になったらtrueを返す

	//大きい弾
	bool bigBulletCreateFlg = false;
	int bigBulletCreateCounter = 0;
	bool bigBulletHitFlg = false;

	//浮遊
	bool skyWalkFlg = true;//浮いているか
	float skyWalkVectorY = 0;
	int skyWalkCounter = 0;
	//影
	Location shadowLocation;

	//ダウン
	int downTimeCounter = 0;

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
	float GetShield() {
		return shield;
	}
	bool GetShieldFlg() const {
		return shieldFlg;
	}

	//Set関数
	void SetBigBulletCreateFlg(bool flg) {
		bigBulletCreateFlg = flg;
	}

	void SetBigBulletHitFlg(bool flg) {
		bigBulletHitFlg = flg;
	}
};

