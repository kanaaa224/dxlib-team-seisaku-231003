#pragma once
#include"SphereCollider.h"
#include "Stage.h"

#define MOVE_RIGHT 0.2
#define MOVE_LEFT -0.2
#define MOVE_UP 0.2
#define MOVE_DOWN -0.2

#define Speed 1.5f
#define Upper_Limit 20.0f
#define Initial_Value 0.0f

#define MAX_HP 100.f

class Player :public SphereCollider
{
private:
	//画像用変数
	int PlayerArrayImg[3];
	int PlayerImg;
	int AimingImg;
	int KaihiImg;
	int TurnFlg;
	int P_Cnt;
	bool MovingFlg;

	//PlayerLocation
	int PlayerX;
	int PlayerY;

	//残像用前回の座標格納用変数
	float Previous_AfterImage_locationX;
	float Previous_AfterImage_locationY;

	//照準
	float AimingX;
	float AimingY;
	float X = 0.0;
	float Y = 0.0;

	//仮 円運動
	float Angle;
	float rd;
	
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
	Vector Additional_Value3;
	float Avoidance;

	//移動量
	float MoveX;
	float MoveY;
	float MoveZ;

	//プレイヤーの体力
	float Player_HP;
	float MaxPlayer_hp;

	int fps;
	int CoolTime_fps;
	int Second;
	int p_CoolTimeCounter;
	int Animation_fps;

	//カメラ用
	StageArray lefttop;
	StageArray rightbottom;
	bool camera_flg_top_bottom;
	bool camera_flg_left_right;

	//SE用
	int SE_playermove;
	int SE_playeravoidance;

	bool is_hit;			//攻撃を受けたかどうか
	int PlayerTestImg;

	//回避
	Vector relativeCursorLocation;
	Vector unitRelativeCursorLocation;
	bool firstAvoidanceFlg = false;
	int AvoidanceCnt = 0;
	Location avoidanceLocation[64];//回避残像
	int afterimageNum;

public:

	static float MovingX;
	static float MovingY;
	static float Additional_Value2;
	static float Aiming_RadiusX;
	static float Aiming_RadiusY;
	static float   Cool_Limit;
	static float Upper_speed;

	//ヒットクールダウン
	static int Hit_cooltime;

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
	void Player_Move_Animation();

	//照準の関数 X Y を戻り値で返す
	int Player_AimingX();
	int Player_AimingY();

	//プレイヤーのヒットクールタイム
	static int Player_invincible(int value);

	//照準の半径を返す
	static void SetPlayer_RadiusX(float value);
	static void SetPlayer_RadiusY(float value);
	float GetPlayer_RadiusX();
	float GetPlayer_RadiusY();

	//回避の移動スピード
	static void SetPlayer_Upperlimit(float value);
	float GetPlayer_Upperlimit();

	//回避のクールダウン時間
	static void SetAvoidance_limit(int value);
	float GetAvoidance_limit();

	//プレイヤーの移動速度
	static void SetPlayer_Speed(float value);
	float GetPlayer_Speed();

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
	
	//プレイヤーのHPをセット
	void SetPlayerHP(float value);


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

	int GetCoolTimeCounter() {
		return p_CoolTimeCounter;
	}

	//プレイヤーの体力の上限値
	float GetMaxPlayer_hp() {
		return MaxPlayer_hp;
	}
};