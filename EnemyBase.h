#pragma once
#include "SphereCollider.h"
#include "weapon.h"
#include "Player.h"

class Stage;

class EnemyBase :public SphereCollider
{
private:

protected:

	float hitLX = 0;//当たった相手のX座標
	float hitLY = 0;//当たった相手のY座標
	float hitVX = 0;//当たった相手のXベクトル
	float hitVY = 0;//当たった相手のYベクトル

	int img;			//画像格納用変数
	float hp;			//敵のHP
	float damage;		//プレイヤーに与えるダメージ
	float speed;		//移動速度
	int exp;			//倒された時のEXPの値(使うか未定)
	int respawnPosition;//リスポーンする場所
	int respawnTime;	//リスポーンまでの時間を格納する
	int respawnTimeCnt;	//リスポーンまでのカウント変数
	int alphaNum;		//透過率を制御する

	int weaponDamage;   //武器のダメージを格納する変数

	float previousFrameValue;	//1フレーム前のプレイヤーとの距離
	float currentFrameValue;	//現在のフレームでのプレイヤーとの距離

	int imgArray[2];//画像格納用変数
	int imgAngle;	//画像左右を格納用

	//FrameCnt変数
	int hitFrameCounter = 0;//武器と当たった時のダメージストップ用Cnt変数
	int redFrameCounter = 0;//画像を赤くする時間をCnt
	int imgFrameCounter = 0;//画像切り替え用変数

	//Flg変数
	bool playerHitFlg;			//プレイヤーに当たったらTRUEを返す
	int hitFlg;					//何かに当たったら（全ての敵、プレイヤー、）
	bool respawnFlg;			//リスポーンしているか
	bool hitWeaponFlg;			//武器とあたったか
	bool hit1stFrameFlg = false;//武器と当たった最初のフレームか
	bool redDrawFlg = false;	//ダメージを受けた時の赤く表示する
	bool stopFlg = false;		//立ち止まっているか

	bool flg = false;
public:
	EnemyBase();

	//プレイヤーまでの距離を求める
	float PlayerLoad_X(float location_x);//X座標上でのプレイヤーまでの距離
	float PlayerLoad_Y(float location_y);//Y座標上でのプレイヤーまでの距離
	//プレイヤーまでの直線距離
	float PlayerLoad(Location location, bool absFlg);
	//正規化
	float Normalization_X(float location_x, float location_y);//X座標上でのプレイヤーまでの距離を正規化
	float Normalization_Y(float location_x, float location_y);//Y座標上でのプレイヤーまでの距離を正規化

	float HitMoveCale_X(float mylx,float hitlx);
	float HitMoveCale_Y(float myly,float hitly);

	//プレイヤーとの距離を遠ざかっているのか近づいているのか同じなのかを返してくれる
	int checkPlayerProximity(float pLocation_x, float pLocation_y, float eLocation_x, float eLocation_y);

	//敵同士の距離
	int checkHitEnemyProximity(Location location, float hlx, float hly);

	//画像左右
	int CheckImgAngle();

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

	float GetLX();
	float GetLY();
	float GetVX();
	float GetVY();

	//Set関数
	void SetRespawnPoint(Player* player ,int WaveNum/*１ウェーブでリスポーンする数*/,int arrayNum);//リスポーン位置を設定する
	int SetGetRand(int min, int max);//最小値と最大値の間のランダムな数字を返す
	void SetHitFlg(int hit);//変数HitFlgに値をセットする
	void SetWeaponDamage(int d);//武器からのダメージをセットする
	void SetHitHP(int d);//武器からのダメージを受けた時の処理
	void SetHitWeaponFlg();//武器との当たり判定用フラグ変数をセットする
	void SetHit1stFrameFlg(bool flg);
	void SetHitFrameCnt(int i);
	void SetPlayer_Location(Location PL);
	int SetRespawnTime(int array, int MAX_ENEMY_STAGE_NUM, int WaveNum);

	void SetHitLocation_X(float lx);
	void SetHitLocation_Y(float ly);
	void SetHitVector_X(float vx);
	void SetHitVector_Y(float vy);

	//動けるかどうか判定する
	bool IsMoveLimit(Stage stage);
};