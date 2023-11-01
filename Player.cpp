#include "main.h"
#include "Player.h"

float Player::MovingX;
float Player::MovingY;

Player::Player() {

	if (PlayerImg = LoadGraph("resources/images/yusya_red.png")) {}
	if (AimingImg = LoadGraph("resources/images/mark_maru.png")) {}
	if (KaihiImg = LoadGraph("resources/images/yusya_kaihi.png")) {}

	PlayerX = 640;
	PlayerY = 360;

	location.x = PlayerX;
	location.y = PlayerY;

	radius = 20;

	AimingX = 300.0;
	AimingY = 300.0;

	Provisional_LStickX = 0.0;
	Provisional_LStickY = 0.0;

	Provisional_RStickX = 0.0;
	Provisional_RStickY = 0.0;

	Provisional_Abtn = 0;

	Additional_Value = 10.0;
	Additional_Value2 = 2.0;
	Additional_Value3 = 0.0;

	MoveX = 0.0;
	MoveY = 0.0;
	MoveZ = 0.0;

	MovingX = 0.0;
	MovingY = 0.0;

	Player_HP = 100.0f;

	fps = 0;
	CoolTime_fps = 0;
	Second = 0;

	A_value = false;
	CoolTime = false;
	Avoidance_Flg = false;

	is_hit = false;

	camera_flg = false;
}

Player::~Player() {

	DeleteGraph(PlayerImg);
	DeleteGraph(AimingImg);
	DeleteGraph(KaihiImg);
}

void Player::update() {

	fps++;
	
	if (is_hit)
	{
		if (fps % 30 == 0)
		{
			is_hit = false;
		}
	}

	//左スティック
	Provisional_LStickX = InputCtrl::GetStickRatio(L).x;
	Provisional_LStickY = InputCtrl::GetStickRatio(L).y;

	//右スティック
	Provisional_RStickX = InputCtrl::GetStickRatio(R).x;
	Provisional_RStickY = InputCtrl::GetStickRatio(R).y;

	//Aボタン
	Provisional_Abtn = InputCtrl::GetButtonState(XINPUT_BUTTON_A);

	//回避フラグ ON
	if (Provisional_Abtn == PRESS && Provisional_LStickX > 0 || Provisional_Abtn == PRESS && Provisional_LStickX < 0 ||
		Provisional_Abtn == PRESS && Provisional_LStickY > 0 || Provisional_Abtn == PRESS && Provisional_LStickY < 0) 
	{
		A_value = true;
	}

	//回避の動作を実効　指定の加算値に到達するまで動く　その後クールダウンをはさむ
	if (A_value == true && CoolTime == false) {
		Avoidance_Flg = true;
		Player_Avoidance();
	}
	
	if (CoolTime == true) {
		Player_CoolTime();
	}

	

	//プレイヤーの移動　プレイヤーが回避をしていない間は動ける
	if ((A_value == false || CoolTime == true) /*&& camera_flg*/) {
		Player_Move();
	}

	Player_Camera();

	Player_Aim();


	if (fps > 59) {
		fps = 0;		
	}
}

void Player::draw()const {

	//左スティック
	DrawFormatString(0, 300, GetColor(255, 0, 0), "LStick:縦軸値 %0.1f", Provisional_LStickY);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "MoveY %0.1f", MoveY);

	//右スティック
	DrawFormatString(0, 340, GetColor(255, 0, 0), "RStick:縦軸値 %0.1f", Provisional_RStickY);
	DrawFormatString(0, 360, GetColor(255, 0, 0), "RStick:横軸値 %0.1f", Provisional_RStickX);

	//Aボタン
	DrawFormatString(0, 380, GetColor(255, 0, 0), "Abtn: %d", Provisional_Abtn);
	DrawFormatString(0, 400, GetColor(255, 0, 0), "加算値　回避　: %f", Additional_Value3);

	DrawFormatString(0, 420, GetColor(255, 0, 0), "A_value  %d", A_value);
	DrawFormatString(0, 440, GetColor(255, 0, 0), "CoolTime %d", CoolTime);
	DrawFormatString(0, 460, GetColor(255, 0, 0), "秒		%d", Second);

	//　中心線
	DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//照準の画像　描画
	DrawRotaGraph(AimingX - 25, AimingY - 25, 0.10f, 0.01, AimingImg, TRUE);

	//回避中の画像の切り替え
	if (A_value == true) {
		DrawRotaGraph(location.x, location.y, 0.10f, 0.01, KaihiImg, TRUE);
	}
	else {
		//プレイヤーの画像　描画
		if (is_hit)
		{
			SetDrawBright(125, 50, 50);
			DrawRotaGraph(location.x, location.y, 0.10f, 0.01, PlayerImg, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawRotaGraph(location.x, location.y, 0.10f, 0.01, PlayerImg, TRUE);
		}
	}

	//DrawRotaGraph(location.x, location.y, 0.10f, 0.01, PlayerImg, TRUE);
	DrawCircleAA(location.x, location.y, radius, 10, 0xffffff,FALSE);
}

void Player::Player_Move() {

	//移動　左スティック
	//横
	if (Provisional_LStickX > MOVE_RIGHT) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		MovingX = MovingX - MoveX;
	}
	else if (Provisional_LStickX < MOVE_LEFT) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		MovingX = MovingX - MoveX;
	}
	else if (Provisional_LStickX == 0) {
		MoveX = 0;
	}

	//縦
	if (Provisional_LStickY < MOVE_DOWN) {

		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		MovingY = MovingY - MoveY;

	}
	else if (Provisional_LStickY > MOVE_UP) {

		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		MovingY = MovingY - MoveY;
	}
	else if (Provisional_LStickY == 0) {
		MoveY = 0;
	}
}

void Player::Player_Aim() {

	//照準　右スティック
	//横
	if (Provisional_RStickX > MOVE_RIGHT) {

		AimingX = AimingX + Additional_Value * Provisional_RStickX;
	}
	else if (Provisional_RStickX < MOVE_LEFT) {

		AimingX = AimingX + Additional_Value * Provisional_RStickX;
	}

	//縦
	if (Provisional_RStickY > MOVE_UP) {

		AimingY = AimingY - Additional_Value * Provisional_RStickY;
	}
	else if (Provisional_RStickY < MOVE_DOWN) {

		AimingY = AimingY - Additional_Value * Provisional_RStickY;
	}
}

void Player::Player_Avoidance() {

	//回避　Aボタン 縦軸　下
	if (Provisional_LStickY < MOVE_DOWN) {
		Additional_Value3 = Additional_Value3 + 1.5f;
		//MoveY = -1 * Additional_Value3 * Provisional_LStickY;
		MoveY = Additional_Value3;
		MovingY = MovingY - MoveY;
		if (Additional_Value3 > 13.0f) {
			Additional_Value3 = 0.0f;
			CoolTime = true;
		}

	}
	//縦軸　上
	else if (Provisional_LStickY > MOVE_UP) {
		Additional_Value3 = Additional_Value3 + -1.5f;
		//MoveY = -1 * Additional_Value3 * Provisional_LStickY;
		MoveY = Additional_Value3;
		MovingY = MovingY + MoveY;
		if (Additional_Value3 < -13.0f) {
			Additional_Value3 = 0.0f;
			CoolTime = true;
		}
	}
	
	//回避　Aボタン　横軸
	if (Provisional_LStickX > MOVE_RIGHT) {
		Additional_Value3 = Additional_Value3 + 1.5f;
		MoveX = Additional_Value3;
		MovingX = MovingX + MoveX;
		if (Additional_Value3 > 13.0f) {
			Additional_Value3 = 0.0f;
			CoolTime = true;
		}
	}
	else if (Provisional_LStickX < MOVE_LEFT) {
		Additional_Value3 = Additional_Value3 + -1.5f;
		MoveX = Additional_Value3;
		MovingX = MovingX - MoveX;
		if (Additional_Value3 < -13.0f) {
			Additional_Value3 = 0.0f;
			CoolTime = true;
		}
	}
}

void Player::Player_CoolTime() {
	
	CoolTime_fps++;

	if (CoolTime_fps > 59) {
		CoolTime_fps = 0;
		Second++;
		if (Second > 3) {
			A_value = false;
			CoolTime = false;
			Avoidance_Flg = false;
			Additional_Value3 = 0.0f;
			Second = 0;
		}
	}
}

void Player::Player_Camera()
{
	//左
	if (lefttop.x > -50) {
		MoveX = 0;
		location.x += Additional_Value2 * Provisional_LStickX;
		camera_flg = true;
	}
	if (location.x > 640 && lefttop.x > -50) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		location.x = 640;
		camera_flg = false;
	}
	//上
	if (lefttop.y > -50) {
		MoveY = 0;
		location.y += -1 * Additional_Value2 * Provisional_LStickY;
		camera_flg = true;
	}
	if (location.y > 360 && lefttop.y > -50) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		location.y = 360;
		camera_flg = false;
	}
	//右
	if (rightbottom.x < 50) {
		MoveX = 0;
		location.x += Additional_Value2 * Provisional_LStickX;
		camera_flg = true;
	}
	if (location.x < 640 && rightbottom.x < 50) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		location.x = 640;
		camera_flg = false;
	}
	//下
	if (rightbottom.y < 50) {
		MoveY = 0;
		location.y += -1 * Additional_Value2 * Provisional_LStickY;
		camera_flg = true;
	}
	if (location.y < 360 && rightbottom.y < 50) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		location.y = 360;
		camera_flg = false;
	}

	//移動制限
	if (location.x < 25) {
		location.x = 25;
	}
	if (location.x > 1255) {
		location.x = 1255;
	}
	if (location.y < 25) {
		location.y = 25;
	}
	if (location.y > 695) {
		location.y = 695;
	}

	if (AimingX < 50) {
		AimingX = 50;
	}
	if (AimingX > 1280) {
		AimingX = 1280;
	}
	if (AimingY < 50) {
		AimingY = 50;
	}
	if (AimingY > 720) {
		AimingY = 720;
	}
}

int Player::Player_AimingX() {

	return AimingX;
}

int Player::Player_AimingY() {

	return AimingY;
}

float Player::Player_MoveX() {

	return MoveX;
}

float Player::Player_MoveY() {

	return MoveY;
}

float Player::Player_MovingX() {

	return MovingX;
}

float Player::Player_MovingY() {

	return MovingY;
}

float Player::GetPlayer_HP() {

	return Player_HP;
}

int Player::GetPlayer_Avoidance() {
	
	return Avoidance_Flg;
}

void Player::SetPlayer_HP(float value) {

	Player_HP = Player_HP - value;
}

Location Player::Player_Location()
{
	return location;
}
