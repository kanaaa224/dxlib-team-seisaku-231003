#pragma once
#include "SphereCollider.h"
#include "weapon.h"

class Stage;

class EnemyBase :public SphereCollider
{
private:

protected:
	int img;			//画像格納用変数
	float hp;			//敵のHP
	float damage;			//プレイヤーに与えるダメージ
	int respawnPosition;//リスポーンする場所
	int respawnTime;	//リスポーンまでの時間を格納する
	int respawnTimeCnt;	//リスポーンまでのカウント変数
	int alphaNum;		//透過率を制御する

	int weaponDamage;   //武器のダメージを格納する変数

	//FrameCnt変数
	int hitFrameCounter = 0;//武器と当たった時のダメージストップ用Cnt変数
	int redFrameCounter = 0;//画像を赤くする時間をCnt

	//Flg変数
	bool playerHitFlg;	//プレイヤーに当たったらTRUEを返す
	int hitFlg;			//何かに当たったら（全ての敵、プレイヤー、）
	bool respawnFlg;	//リスポーンしているか
	bool hitWeaponFlg;  //武器とあたったか
	bool hit1stFrameFlg = false;//武器と当たった最初のフレームか
public:
	EnemyBase();

	//プレイヤーまでの距離を求める
	float PlayerLoad_X(float location_x);//X座標上でのプレイヤーまでの距離
	float PlayerLoad_Y(float location_y);//Y座標上でのプレイヤーまでの距離
	//正規化
	float Normalization_X(float location_x, float location_y);//X座標上でのプレイヤーまでの距離を正規化
	float Normalization_Y(float location_x, float location_y);//Y座標上でのプレイヤーまでの距離を正規化

	float HitMoveCale_X(float myvx,float hitvx);
	float HitMoveCale_Y(float myvy,float hitvy);

	//Inc
	void hitFrameCntInc();

	//Get関数
	Location GetEnemyLocation();
	int GetHitFlg();
	float GetHP();
	bool GetHitWeaponFlg();
	bool GetHit1stFrameFlg();
	int GetHitFrameCnt();
	float GetDamage();
	Vector GetEnemyVector();

	//Set関数
	void SetRespawnPoint();//リスポーン位置を設定する
	int SetGetRand(int min, int max);
	void SetHitFlg(int hit);
	void SetWeaponDamage(int d);
	void SetHitHP(int d);//武器からのダメージを受けた時の処理
	void SetHitWeaponFlg();
	void SetHit1stFrameFlg(bool flg);
	void SetHitFrameCnt(int i);
	void SetPlayer_Location(Location PL);

	//動けるかどうか判定する
	bool IsMoveLimit(Stage stage);
};