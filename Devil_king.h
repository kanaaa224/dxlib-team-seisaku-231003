#pragma once
#include "EnemyBase.h"
#include "Common.h"
#define DEVILKING_MAX_HP 2000					//魔王の最大体力
#define DEVILKING_ATTAK_DAMAGE 10				//魔王のダメージ
#define BIG_BULLET_CREATE_TIME  SECOND_FRAME(1.5)//大きい弾の生成速度
#define MAX_SHIELD 100							//シールドの最大値
#define DOWN_TIME SECOND_FRAME(7)				//ダウンタイム

#define DARK_SHADOW_RADIUS_X  50				//濃い影の半径X
#define DARK_SHADOW_RADIUS_Y  15				//濃い影の半径Y
#define LIGHT_SHADOW_RADIUS_X 25				//薄い影の半径X
#define LIGHT_SHADOW_RADIUS_Y  7				//薄い影の半径Y

#define BOX_MAX_LENGTH_D 1280

class Devil_king:public EnemyBase
{
private:
	int debugCnt = 0;

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
	float shadowRadiusX = 25;
	float shadowRadiusY = 7;
	bool shadowRadiusChageFlg = false;

	//ダウン
	int downTimeCounter = 0;

	//・・・・・ビーム・・・・・//

	//薄い攻撃予測
	float boxX_a;
	float boxY_a;
	float boxX_d;
	float boxY_d;

	//濃い攻撃予測
	int lineSize;

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

	bool GetSkyWalkFlg() {
		return skyWalkFlg;
	}

	//Set関数
	void SetBigBulletCreateFlg(bool flg) {
		bigBulletCreateFlg = flg;
	}

	void SetBigBulletHitFlg(bool flg) {
		bigBulletHitFlg = flg;
	}
};

