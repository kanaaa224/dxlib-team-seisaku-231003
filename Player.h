#pragma once
#include"SphereCollider.h"

#define MOVE_RIGHT 0.1
#define MOVE_LEFT -0.1
#define MOVE_UP 0.1
#define MOVE_DOWN -0.1


class Player :public SphereCollider
{
private:
	//画像用変数
	int PlayerImg;
	int AimingImg;
	int KaihiImg;

	//PlayerLocation
	int PlayerX;
	int PlayerY;

	//照準
	float AimingX;
	float AimingY;

	//左スティック
	float Provisional_LStickX;
	float Provisional_LStickY;

	//右スティック
	float Provisional_RStickX;
	float Provisional_RStickY;

	// Aボタン
	int Provisional_Abtn;
	bool A_value;
	bool CoolTime;
	bool Avoidance_Flg;

	//　加算値
	float Additional_Value;
	float Additional_Value2;
	float Additional_Value3;

	float Avoidance;

	//移動量
	float MoveX;
	float MoveY;
	float MoveZ;

	//プレイヤーの体力
	float Player_HP;

	int fps;
	int CoolTime_fps;
	int Second;

public:

	static float MovingX;
	static float MovingY;

	Player();
	~Player();

	void update();

	//描画処理
	void draw() const;

	void Player_Move();
	void Player_Aim();
	void Player_Avoidance();
	void Player_CoolTime();

	//照準の関数 X Y を戻り値で返す
	int Player_AimingX();
	int Player_AimingY();

	//プレイヤーの移動量 X Y を返す
	float Player_MoveX();
	float Player_MoveY();

	//プレイヤーの座標を返す X Y
	static float Player_MovingX();
	static float Player_MovingY();

	// プレイヤーの体力を返す
	float GetPlayer_HP();
	int GetPlayer_Avoidance();

	// プレイヤーの体力を引く
	void SetPlayer_HP(float value);
};