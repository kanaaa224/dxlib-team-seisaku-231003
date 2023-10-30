#pragma once

#define MOVE_RIGHT 0.1
#define MOVE_LEFT -0.1
#define MOVE_UP 0.1
#define MOVE_DOWN -0.1


class Player
{
private:
	//画像用変数
	int PlayerImg;
	int AimingImg;

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
	int Player_HP;

public:

	static float MovingX;
	static float MovingY;

	Player();
	~Player();

	void update();

	//描画処理
	void draw() const;

	int Player_AimingX();
	int Player_AimingY();

	float Player_MoveX();
	float Player_MoveY();

	static float Player_MovingX();
	static float Player_MovingY();

	int GetPlayer_HP();
	void SetPlayer_HP(int value);
};