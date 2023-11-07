#pragma once
#include"SphereCollider.h"
#include "Stage.h"

#define MOVE_RIGHT 0.2
#define MOVE_LEFT -0.2
#define MOVE_UP 0.2
#define MOVE_DOWN -0.2

#define Speed 1.5f
#define Upper_Limit 13.0f
#define Initial_Value 0.0f

#define MAX_HP 100.f

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

	//カメラ用
	StageArray lefttop;
	StageArray rightbottom;
	bool camera_flg_top_bottom;
	bool camera_flg_left_right;

	bool is_hit;			//攻撃を受けたかどうか

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
	void Player_Camera();

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
	bool GetPlayer_Avoidance();

	// プレイヤーの体力を引く
	void SetPlayer_HP(float value);

	//is_hitを取得する
	bool GetIsHit()
	{
		return is_hit;
	}

	//is_hitを設定する
	void SetIsHit(const bool flg)
	{
		is_hit = flg;
	}


	Location Player_Location();

	//ステージの左上と右下を取得
	void SetLeftTop(StageArray sa) {
		lefttop = sa;
	}
	void SetRightBottom(StageArray sa) {
		rightbottom = sa;
	}
};