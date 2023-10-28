#pragma once
#include "SphereCollider.h"

class EnemyBase :public SphereCollider
{
private:

protected:
	int img;			//画像格納用変数
	int hp;				//敵のHP
	int damage;			//プレイヤーに与えるダメージ
	int damageStopCnt;	//ダメージストップ用のカウント変数
	int respawnPosition;//リスポーンする場所
	int respawnTime;	//リスポーンまでの時間を格納する
	int respawnTimeCnt;	//リスポーンまでのカウント変数

	//Flg変数
	bool playerHitFlg;	//プレイヤーに当たったらTRUEを返す
	int hitFlg;			//何かに当たったら（全ての敵、プレイヤー、）
	bool respawnFlg;	//リスポーンしているか
public:
	EnemyBase();

	//プレイヤーまでの距離を求める
	float PlayerLoad_X(float location_x);//X座標上でのプレイヤーまでの距離
	float PlayerLoad_Y(float location_y);//Y座標上でのプレイヤーまでの距離
	//正規化
	float Normalization_X(float location_x, float location_y);//X座標上でのプレイヤーまでの距離を正規化
	float Normalization_Y(float location_x, float location_y);//Y座標上でのプレイヤーまでの距離を正規化

	//リスポーン位置を設定する
	void SetRespawnPoint();

	int SetGetRand(int min, int max);

	Location GetEnemyLocation();

	int GetHitFlg();
	void SetHitFlg(int hit);

};