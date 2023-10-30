#pragma once
#include "SphereCollider.h"
#include "weapon.h"

class EnemyBase :public SphereCollider
{
private:

protected:
	int img;			//画像格納用変数
	float hp;			//敵のHP
	int damage;			//プレイヤーに与えるダメージ
	int damageStopCnt;	//ダメージストップ用のカウント変数
	int respawnPosition;//リスポーンする場所
	int respawnTime;	//リスポーンまでの時間を格納する
	int respawnTimeCnt;	//リスポーンまでのカウント変数
	int alphaNum;		//透過率を制御する

	int weaponDamage;   //武器のダメージを格納する変数

	//Flg変数
	bool playerHitFlg;	//プレイヤーに当たったらTRUEを返す
	int hitFlg;			//何かに当たったら（全ての敵、プレイヤー、）
	bool respawnFlg;	//リスポーンしているか
	bool hitWeaponFlg;  //武器とあたったか
public:
	EnemyBase();

	//プレイヤーまでの距離を求める
	float PlayerLoad_X(float location_x);//X座標上でのプレイヤーまでの距離
	float PlayerLoad_Y(float location_y);//Y座標上でのプレイヤーまでの距離
	//正規化
	float Normalization_X(float location_x, float location_y);//X座標上でのプレイヤーまでの距離を正規化
	float Normalization_Y(float location_x, float location_y);//Y座標上でのプレイヤーまでの距離を正規化

	//Get関数
	Location GetEnemyLocation();
	int GetHitFlg();
	float GetHP();

	//Set関数
	void SetRespawnPoint();//リスポーン位置を設定する
	int SetGetRand(int min, int max);
	void SetHitFlg(int hit);
	void SetHitWeapon(weapon* w);
	void SetWeaponDamage(weapon* w);

};