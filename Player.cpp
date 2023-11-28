#include "main.h"
#include "Player.h"

float Player::MovingX;
float Player::MovingY;
float Player::Additional_Value2;
float Player::Aiming_RadiusX;
float Player::Aiming_RadiusY;
float Player::Cool_Limit;
int   Player::Hit_cooltime;
float Player::Upper_speed;

Player::Player() {

	//画像
	if(PlayerTestImg = LoadGraph("resources/images/raiyatest.png")) {}
	if (PlayerImg = LoadGraph("resources/images/knightplayer_test.png")) {}
	if (AimingImg = LoadGraph("resources/images/mark_maru.png")) {}
	if (KaihiImg = LoadGraph("resources/images/yusya_kaihi.png")) {}

	//SE
	if (SE_playermove = LoadSoundMem("resources/sounds/se_player_move.wav")) {};
	if (SE_playeravoidance = LoadSoundMem("resources/sounds/se_player_avoidance.wav")) {};

	PlayerX = 640;
	PlayerY = 360;

	location.x = PlayerX;
	location.y = PlayerY;

	//当たり判定のもの
	radius = 20;

	AimingX = 300.0;
	AimingY = 300.0;
	Aiming_RadiusX = 200.0;
	Aiming_RadiusY = 200.0;

	Angle = 0.0;
	rd = 0.0;

	Provisional_LStickX = 0.0;
	Provisional_LStickY = 0.0;

	Provisional_RStickX = 0.0;
	Provisional_RStickY = 0.0;

	Provisional_Abtn = 0;

	Additional_Value = 10.0;
	Additional_Value2 = 2.0;
	Additional_Value3 = { 0.0f,0.0f };

	MoveX = 0.0;
	MoveY = 0.0;
	MoveZ = 0.0;

	MovingX = 0.0;
	MovingY = 0.0;

	Player_HP = MAX_HP;

	fps = 0;
	CoolTime_fps = 0;
	Second = 0;

	A_value = false;
	CoolTime = false;
	Avoidance_Flg = false;
	Cool_Limit = 2;

	is_hit = false;

	camera_flg_top_bottom = false;
	camera_flg_left_right = false;

	Hit_cooltime = 30;
	Upper_speed = 1.5f;

	firstAvoidanceFlg = false;
	AvoidanceCnt = 0;
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
		// 0.5秒の間、無敵
		if (fps % Hit_cooltime == 0)
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

	Angle = atan2(Provisional_RStickX, Provisional_RStickY);

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
		Avoidance_Flg = false;
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
	//DrawFormatString(0, 300, GetColor(255, 0, 0), "RStick:縦軸値 %0.1f", AimingY);
	//DrawFormatString(0, 320, GetColor(255, 0, 0), "AimingY %0.1f", AimingY);
	//DrawFormatString(0, 320, GetColor(255, 0, 0), "RStick:横軸値 %0.1f", AimingX);

	//右スティック
	//DrawFormatString(0, 360, GetColor(255, 0, 0), "PlayerX:縦軸値 %0.1f", location.x);
	//DrawFormatString(0, 380, GetColor(255, 0, 0), "PlayerY:横軸値 %0.1f", location.y);

	//Aボタン
	/*DrawFormatString(0, 380, GetColor(255, 0, 0), "Abtn: %d", Provisional_Abtn);
	DrawFormatString(0, 400, GetColor(255, 0, 0), "加算値　回避　: %f", Additional_Value3);*/

	/*DrawFormatString(0, 420, GetColor(255, 0, 0), "A_value  %d", A_value);
	DrawFormatString(0, 440, GetColor(255, 0, 0), "CoolTime %d", CoolTime);
	DrawFormatString(0, 460, GetColor(255, 0, 0), "秒		%d", Second);*/

	//　中心線
	//DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	//DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//照準の画像　描画　中心座標
	//DrawRotaGraph(AimingX - 25, AimingY - 25, 0.10f, 0.01, AimingImg, TRUE);
	DrawRotaGraph(X, Y, 0.10f, 0.01, AimingImg, TRUE);

	//回避中の画像の切り替え
	if (Avoidance_Flg == true && CoolTime == true) {
		DrawRotaGraph(location.x, location.y, 0.10f, 0.01, KaihiImg, TRUE);
	}
	else {
		//プレイヤーの画像　描画
		if (is_hit)
		{
			SetDrawBright(125, 50, 50);
			DrawRotaGraph(location.x, location.y, 0.15f, 0.01, PlayerImg, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawRotaGraph(location.x, location.y, 0.15f, 0.01, PlayerImg, TRUE);
			DrawRotaGraph(location.x + 70, location.y, 0.15f, 0.01, PlayerTestImg, TRUE);
		}
	}

	//DrawRotaGraph(location.x, location.y, 0.10f, 0.01, PlayerImg, TRUE);
	//DrawCircleAA(location.x, location.y, radius, 10, 0xffffff,FALSE);
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
	else {
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
	else {
		MoveY = 0;
	}
}

void Player::Player_Aim() {

		// 50 は 半径
	X = location.x + Aiming_RadiusX * cosf(rd);
	Y = location.y + Aiming_RadiusY * sinf(rd);

	//照準　右スティック
	//横
	if (Provisional_RStickX > MOVE_RIGHT) {
		
		rd = Angle + float(-M_PI / 2);

		//AimingX = AimingX + Additional_Value * Provisional_RStickX;
	}
	else if (Provisional_RStickX < MOVE_LEFT) {
		
		rd = Angle + float(-M_PI / 2);

		//AimingX = AimingX + Additional_Value * Provisional_RStickX;
	}

	//縦
	if (Provisional_RStickY > MOVE_UP) {
		
		rd = Angle + float(-M_PI / 2);

		//AimingY = AimingY - Additional_Value * Provisional_RStickY;
	}
	else if (Provisional_RStickY < MOVE_DOWN) {

		rd = Angle + float(-M_PI / 2);

		//AimingY = AimingY - Additional_Value * Provisional_RStickY;
	}
}

void Player::Player_Avoidance() {

	if (!firstAvoidanceFlg) {
		relativeCursorLocation.x = Provisional_LStickX;
		relativeCursorLocation.y = Provisional_LStickY;
		relativeCursorLocation.length = sqrtf((relativeCursorLocation.x * relativeCursorLocation.x) + (relativeCursorLocation.y * relativeCursorLocation.y));

		unitRelativeCursorLocation.x = relativeCursorLocation.x / relativeCursorLocation.length;
		unitRelativeCursorLocation.y = relativeCursorLocation.y / relativeCursorLocation.length;
		unitRelativeCursorLocation.length = relativeCursorLocation.length / relativeCursorLocation.length;

		firstAvoidanceFlg = true;
	}


	//回避　Aボタン
	//横
	if (relativeCursorLocation.x > MOVE_RIGHT) {
		//Additional_Value3.x = Additional_Value3.x + Upper_speed;	//回避の速度
		Additional_Value3.x = unitRelativeCursorLocation.x + Upper_speed * 5;	//回避の速度
		if (camera_flg_left_right) {	//壁際
			location.x += Additional_Value3.x * unitRelativeCursorLocation.x;
		}
		else{
			MoveX = Additional_Value3.x * unitRelativeCursorLocation.x;
			MovingX = MovingX - MoveX;
		}
	
		//if (Additional_Value3.x > fabsf( unitRelativeCursorLocation.x) * Upper_Limit) {		//終了
		//	Additional_Value3.x = Initial_Value;
		//	CoolTime = true;
		//	firstAvoidanceFlg = false;
		//}
	}
	else if (relativeCursorLocation.x < MOVE_LEFT) {
		Additional_Value3.x = unitRelativeCursorLocation.x + Upper_speed * 5;	//回避の速度
		//Additional_Value3.x = Additional_Value3.x + Upper_speed;
		if (camera_flg_left_right) {
			location.x += Additional_Value3.x * unitRelativeCursorLocation.x;
		}
		else {
			MoveX = Additional_Value3.x * unitRelativeCursorLocation.x;
			MovingX = MovingX - MoveX;
		}

		/*if (Additional_Value3.x > fabsf(unitRelativeCursorLocation.x) * Upper_Limit) {
			Additional_Value3.x = Initial_Value;
			CoolTime = true;
			firstAvoidanceFlg = false;
		}*/
	}
	/*else if (Provisional_LStickX == 0) {
		Additional_Value3 = 0.0f;
		MoveX = 0;
	}*/

	//縦 下方向
	if (relativeCursorLocation.y < MOVE_DOWN) {
		//Additional_Value3.y = Additional_Value3.y + Upper_speed;
		Additional_Value3.y = unitRelativeCursorLocation.y + Upper_speed * 5;	//回避の速度

		if (camera_flg_top_bottom) {
			location.y += -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
		}
		else {
			MoveY = -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
			MovingY = MovingY + MoveY;
		}
		/*if (Additional_Value3.y > fabsf(unitRelativeCursorLocation.y) * Upper_Limit) {
			Additional_Value3.y = Initial_Value;
			CoolTime = true;
			firstAvoidanceFlg = false;
		}*/
	}
	//縦　上方向
	else if (relativeCursorLocation.y > MOVE_UP) {
		//Additional_Value3.y = Additional_Value3.y + Upper_speed;
		Additional_Value3.y = unitRelativeCursorLocation.y + Upper_speed * 5;	//回避の速度

		if (camera_flg_top_bottom) {
			location.y += -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
		}
		else {
			MoveY = -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
			MovingY = MovingY + MoveY;
		}
		/*if (Additional_Value3.y > fabsf(unitRelativeCursorLocation.y) * Upper_Limit) {
			Additional_Value3.y = Initial_Value;
			CoolTime = true;
			firstAvoidanceFlg = false;
		}*/
	}
	/*else if (Provisional_LStickY == 0) {
		Additional_Value3 = 0.0f;
		MoveY = 0;
	}*/

	
	if (AvoidanceCnt++ > 20) {
		Additional_Value3.x = Initial_Value;
		Additional_Value3.y = Initial_Value;
		CoolTime = true;
		firstAvoidanceFlg = false;
		AvoidanceCnt = 0;
	}



	/*MoveX = unitRelativeCursorLocation.x * 10;
	MovingX = MovingX - MoveX;*/

	/*location.x += unitRelativeCursorLocation.x * 10;
	location.y += unitRelativeCursorLocation.y * 10;*/





}

void Player::Player_CoolTime() {
	
	CoolTime_fps++;

	if (CoolTime_fps > 59) {
		CoolTime_fps = 0;
		Second++;
		if (/*Second > Cool_Limit*/true) {
			A_value = false;
			CoolTime = false;
			
			Additional_Value3 = { 0.0f,0.0f };
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
		camera_flg_left_right = true;
	}
	if (location.x > 640 && lefttop.x > -50) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		location.x = 640;
		camera_flg_left_right = false;
	}
	//上
	if (lefttop.y > -50) {
		MoveY = 0;
		location.y += -1 * Additional_Value2 * Provisional_LStickY;
		camera_flg_top_bottom = true;
	}
	if (location.y > 360 && lefttop.y > -50) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		location.y = 360;
		camera_flg_top_bottom = false;
	}
	//右
	if (rightbottom.x < 50) {
		MoveX = 0;
		location.x += Additional_Value2 * Provisional_LStickX;
		camera_flg_left_right = true;
	}
	if (location.x < 640 && rightbottom.x < 50) {
		MoveX = Additional_Value2 * Provisional_LStickX;
		location.x = 640;
		camera_flg_left_right = false;
	}
	//下
	if (rightbottom.y < 50) {
		MoveY = 0;
		location.y += -1 * Additional_Value2 * Provisional_LStickY;
		camera_flg_top_bottom = true;
	}
	if (location.y < 360 && rightbottom.y < 50) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		location.y = 360;
		camera_flg_top_bottom = false;
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

	return X;
}

int Player::Player_AimingY() {

	return Y;
}

//回避の速度を返す
float Player::GetPlayer_Upperlimit() {

	return Upper_speed;
}

//回避の速度をセットする
void Player::SetPlayer_Upperlimit(float value) {

	Upper_speed = value;
}

int Player::Player_invincible(int value) {

	Hit_cooltime = value;

	return Hit_cooltime;
}

// プレイヤーの移動速度を返す
float Player::GetPlayer_Speed() {

	return Additional_Value2;
}

//プレイヤーの移動速度をセットする
void Player::SetPlayer_Speed(float value) {

	Additional_Value2 =  value;
}

//照準Xを返す
float Player::GetPlayer_RadiusX() {

	return Aiming_RadiusX;
}

// 照準Xをセットする
void  Player::SetPlayer_RadiusX(float value) {

	Aiming_RadiusX = Aiming_RadiusX + value;
}

//照準Yを返す
float Player::GetPlayer_RadiusY() {

	return Aiming_RadiusY;
}

//照準Yをセットする
void  Player::SetPlayer_RadiusY(float value) {

	Aiming_RadiusY = Aiming_RadiusY + value;
}

//回避のクールタイムを返す
float Player::GetAvoidance_limit() {

	return Cool_Limit;
}

// 回避のクールタイムの時間をセットする
void Player::SetAvoidance_limit(float value) {

	Cool_Limit =  value;
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

bool Player::GetPlayer_Avoidance() {
	
	return Avoidance_Flg;
}

void Player::SetPlayer_HP(float value) {

	Player_HP = Player_HP - value;
	if (Player_HP > MAX_HP)
	{
		Player_HP = MAX_HP;
	}
}

void Player::SetPlayerHP(float value){
	Player_HP = value;
}

Location Player::Player_Location(){
	return location;
}
