#pragma once
#include "EnemyBase.h"
#include "Common.h"
#define DEVILKING_MAX_HP 2000					//魔王の最大体力
#define DEVILKING_ATTAK_DAMAGE 1				//魔王のダメージ
#define BIG_BULLET_CREATE_TIME  SECOND_FRAME(1.5)//大きい弾の生成速度
#define MAX_SHIELD 100							//シールドの最大値
#define DOWN_TIME SECOND_FRAME(7)				//ダウンタイム

#define DARK_SHADOW_RADIUS_X  50				//濃い影の半径X
#define DARK_SHADOW_RADIUS_Y  15				//濃い影の半径Y
#define LIGHT_SHADOW_RADIUS_X 25				//薄い影の半径X
#define LIGHT_SHADOW_RADIUS_Y  7				//薄い影の半径Y

#define BOX_MAX_LENGTH_D 1280

#define TELEPORTATION_RADIUS 150

#define BEAM_MAX_WIDTH 300//ビームの幅
#define BEAM_POSITION_CROSS	   0//ビームが十字方向
#define BEAM_POSITION_DIAGONAL 1//ビームが斜め方向

#define BEAM_CAN_TIEM SECOND_FRAME(2)//ビームのクールタイム

#define BEAM_SIZE 3000//ビームの縦

#define DEVILKING_BEAM_SPACE 60//ビームと魔王との隙間
#define BEAM_DAMAGE 1
#define NOW_BEAM_TIME SECOND_FRAME(7)//ビームの照射時間

//ビームの配列//
//十字
#define RIGHT 0//右
#define LEFT  1//左
#define LOWER 2//下
#define UPPER 3//上
//斜め
#define UPPER_RIGHT 0//右上
#define UPPER_LEFT  1//左上
#define LOWER_RIGHT 2//右下
#define LOWER_LEFT  3//左下

class Devil_king:public EnemyBase
{
private:
	int debugCnt = 0;

	bool InitFlg = false;
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

	//瞬間移動
	bool teleportationFlg = false;

	//・・・・・ビーム・・・・・//
	int beamChargeImg[4];	//チャージ画像
	int beamShootImg[4];	//発射画像

	int beamPosition = 0;//十字か斜めか
	Location beamLocation[4];
	int lineSize = 0;
	bool beamPossibleFlg = false;//発射準備してもいいか
	int beamPossibleCounter = 0;
	bool beamShootFlg = false;//ビームが発射されているか
	bool beamShootFinFlg = false;
	bool nowBeamFlg = false;//ビーム中か？
	int nowBeamCounter = 0;

	bool hitBeamPlayer[8];	//プレイヤーがビームにヒット時の判定用



public:
	Devil_king();
	~Devil_king();
	void Update(Player* player);
	void Draw() const;

	//瞬間移動
	void Teleportation();

	//ビーム
	void BeamUpdate(Player* player);
	void BeamDraw() const;
	//ビームの当たり判定
	void BeamCollision(Player* player);
	//十字
	void BeamCollisionRight(Player* player);
	void BeamCollisionLeft(Player* player);
	void BeamCollisionLower(Player* player);
	void BeamCollisionUpper(Player* player);
	//斜め
	void BeamCollisionUpperRight(Player* player);
	void BeamCollisionUpperLeft(Player* player);
	void BeamCollisionLowerRight(Player* player);
	void BeamCollisionLowerLeft(Player* player);



	//・・・・・Get関数・・・・・//
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

	bool GetHitBeamPlayerFlg(int arrayNum) {
		return hitBeamPlayer[arrayNum];
	}

	//・・・・・Set関数・・・・・//
	void SetBigBulletCreateFlg(bool flg) {
		bigBulletCreateFlg = flg;
	}

	void SetBigBulletHitFlg(bool flg) {
		bigBulletHitFlg = flg;
	}
};

