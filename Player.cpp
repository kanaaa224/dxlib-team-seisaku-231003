#include "main.h"
//#include "Player.h"

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
	if (PlayerArrayImg[0] = LoadGraph("resources/images/player_images/Player_right50・50.png")) {}
	if (PlayerArrayImg[1] = LoadGraph("resources/images/player_images/Player_right_move1鎧150.50.png")) {}
	if (PlayerArrayImg[2] = LoadGraph("resources/images/player_images/Player_right_move2鎧250.50.png")) {}

	if (AimingImg = LoadGraph("resources/images/mark_maru.png")) {}
	if (KaihiImg = LoadGraph("resources/images/yusya_kaihi.png")) {}

	PlayerImg = PlayerArrayImg[0];

	//SE
	SoundManager::SetSE("se_player_move");
	SoundManager::SetSE("se_player_avoidance");
	SoundManager::SetVolumeSEs(100);

	PlayerX = 640;
	PlayerY = 360;

	location.x = PlayerX;
	location.y = PlayerY;

	Previous_AfterImage_locationX = 0.0f;
	Previous_AfterImage_locationY = 0.0f;

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
	Additional_Value2 = 2.0f;
	Additional_Value3 = { 0.0f,0.0f };

	MoveX = 0.0;
	MoveY = 0.0;
	MoveZ = 0.0;

	MovingX = 0.0;
	MovingY = 0.0;

	Player_HP = MAX_HP;
	MaxPlayer_hp = 100.0f;

	fps = 0;
	CoolTime_fps = 0;
	Second = 0;

	A_value = false;
	CoolTime = false;
	Avoidance_Flg = false;
	Cool_Limit = 2.0f;

	is_hit = false;

	camera_flg_top_bottom = false;
	camera_flg_left_right = false;

	Hit_cooltime = 30;
	Upper_speed = 1.5f;

	firstAvoidanceFlg = false;
	AvoidanceCnt = 0;

	TurnFlg = FALSE;
	P_Cnt = 0;
	MovingFlg = false;

	p_CoolTimeCounter = 0;
	Animation_fps = 60;


	afterimageNum = 1;
	for (int i = 0; i < 64; i++)
	{
		avoidanceLocation[i] = location;
	}

	P_minotaur = false;
	Hit_minotur_fps = 0;
	P_minotaur_Hit_flg = true;

}

Player::~Player() {

	for (int i = 0; i < 3; i++) {
		DeleteGraph(PlayerArrayImg[i]);
	}

	DeleteGraph(AimingImg);
	DeleteGraph(KaihiImg);
}

void Player::update(bool minotaur) {

	fps++;
	
	if (is_hit)
	{
		// 0.5秒の間、無敵
		if (fps % Hit_cooltime == 0)
		{
			is_hit = false;
		}
	}

	//ミノタウロスの咆哮にHitしたら true
	P_minotaur = minotaur;
	
	//左スティック
	Provisional_LStickX = InputCtrl::GetStickRatio(L).x;
	Provisional_LStickY = InputCtrl::GetStickRatio(L).y;

	//右スティック
	Provisional_RStickX = InputCtrl::GetStickRatio(R).x;
	Provisional_RStickY = InputCtrl::GetStickRatio(R).y;

	Angle = atan2(Provisional_RStickX, Provisional_RStickY);

	//Aボタン
	Provisional_Abtn = InputCtrl::GetButtonState(XINPUT_BUTTON_A);
	
	if (P_minotaur == true) {
		P_Hit_minotur();
	}
	else {
		//回避フラグ ON
		if (Provisional_Abtn == PRESS && Provisional_LStickX > 0 || Provisional_Abtn == PRESS && Provisional_LStickX < 0 ||
			Provisional_Abtn == PRESS && Provisional_LStickY > 0 || Provisional_Abtn == PRESS && Provisional_LStickY < 0)
		{
			A_value = true;
		}
	}
	

	//回避の動作を実効　指定の加算値に到達するまで動く　その後クールダウンをはさむ
	if (A_value == true && CoolTime == false) {
		StopSoundMem(SE_playermove);
		Avoidance_Flg = true;
		Player_Avoidance();
		//Player_Move_Animation();

		SoundManager::PlaySoundSE("se_player_avoidance");
	}
	
	if (CoolTime == true) {
		A_value = false;
		Avoidance_Flg = false;
		Player_CoolTime();
	}

	//プレイヤーの移動　プレイヤーが回避をしていない間は動ける
	if ((A_value == false || CoolTime == true) /*&& camera_flg*/) {
		SoundManager::StopSoundSE("se_player_avoidance");
		MovingFlg = true;
		Player_Move();

		SoundManager::PlaySoundSE("se_player_move");
	}
	else {
		MovingFlg = false;
	}

	if (A_value == false && CoolTime == true && MovingFlg == false || Provisional_LStickX < 0.2 && Provisional_LStickY < 0.2 && Provisional_LStickX > -0.2 && Provisional_LStickY > -0.2) {
		SoundManager::StopSoundSE("se_player_move");
		SoundManager::StopSoundSE("se_player_avoidance");
		PlayerImg = PlayerArrayImg[0];
	}

	Player_Camera();

	Player_Aim();

	if (fps > 59) {
		fps = 0;
		P_Cnt++;
	}
	else if(P_Cnt > 4) {
		P_Cnt = 0;
	}


	avoidanceLocation[0] = location;
}

void Player::draw()const {

	//左スティック
	DrawFormatString(0, 300, GetColor(255, 0, 0), "ミノタウロスのHitフラグ %d", P_minotaur);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "P_minotaur_Hit_flg			%d", P_minotaur_Hit_flg);
	DrawFormatString(0, 340, GetColor(255, 0, 0), "Hit_minotur_fps			 %d", Hit_minotur_fps);
	//DrawFormatString(0, 650, 0xffffff, "X:%f", Aiming_RadiusX);

	//Aボタン
	/*DrawFormatString(0, 380, GetColor(255, 0, 0), "Abtn: %d", Provisional_Abtn);
	DrawFormatString(0, 400, GetColor(255, 0, 0), "加算値　回避　: %f", Additional_Value3);*/

	//　中心線
	DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//照準の画像　描画　中心座標
	//DrawRotaGraph(AimingX - 25, AimingY - 25, 0.10f, 0.01, AimingImg, TRUE);
	DrawRotaGraph(X, Y, 0.10f, 0.01, AimingImg, TRUE);

	if (is_hit) {

		SetDrawBright(125, 50, 50);
		DrawRotaGraph2(location.x - 35, location.y - 40, 0, 0, 1.5, 0.0, PlayerImg, TRUE, TurnFlg);
		SetDrawBright(255, 255, 255);
	}
	else {

		DrawRotaGraph2(location.x - 35, location.y - 40, 0, 0, 1.5, 0.0, PlayerImg, TRUE, TurnFlg);
	}

	if (Avoidance_Flg == true) {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		for (int i = 0; i < 64; i++)
		{
			if (i % 5 == 0) {
				/*DrawRotaGraph2(avoidanceLocation[i].x - 35, avoidanceLocation[i].y - 40, 0, 0, 1.5, 0.0, PlayerImg, TRUE, TurnFlg);
				DrawFormatString(avoidanceLocation[i].x, avoidanceLocation[i].y, 0xff0000, "%d", i);*/
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}


	/*DrawFormatString(100, 340, GetColor(255, 0, 0),"%f %f", avoidanceLocation[0].x, avoidanceLocation[0].y);
	DrawFormatString(100, 370, GetColor(255, 0, 0),"%f %f", avoidanceLocation[1].x, avoidanceLocation[1].y);*/

	//DrawRotaGraph(location.x, location.y, 0.10f, 0.01, PlayerImg, TRUE);
	//DrawCircle(location.x, location.y, radius, 0xff0000, 0xffffff,TRUE);
}

void Player::Player_Move() {

	//移動　左スティック
	//横
	if (Provisional_LStickX > MOVE_RIGHT) {
		TurnFlg = FALSE;
		MoveX = Additional_Value2 * Provisional_LStickX;
		MovingX = MovingX - MoveX;
		Player_Move_Animation();
	}
	else if (Provisional_LStickX < MOVE_LEFT) {
		TurnFlg = TRUE;
		MoveX = Additional_Value2 * Provisional_LStickX;
		MovingX = MovingX - MoveX;
		Player_Move_Animation();
	}
	else {
		MoveX = 0;
	}

	//縦
	if (Provisional_LStickY < MOVE_DOWN) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		MovingY = MovingY - MoveY;
		Player_Move_Animation();

	}
	else if (Provisional_LStickY > MOVE_UP) {
		MoveY = -1 * Additional_Value2 * Provisional_LStickY;
		MovingY = MovingY - MoveY;
		Player_Move_Animation();
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

	
	

	avoidanceLocation[0] = location;


	//回避　Aボタン
	//横
	if (relativeCursorLocation.x > MOVE_RIGHT) {
		//Additional_Value3.x = Additional_Value3.x + Upper_speed;	//回避の速度
		Additional_Value3.x = unitRelativeCursorLocation.x + Upper_speed * 5;	//回避の速度
		if (camera_flg_left_right) {	//壁際
			location.x += Additional_Value3.x * unitRelativeCursorLocation.x;
			
			//avoidanceLocation[afterimageNum].x = location.x;
			avoidanceLocation[afterimageNum].x = avoidanceLocation[afterimageNum - 1].x - Additional_Value3.x * unitRelativeCursorLocation.x;
			//avoidanceLocation[afterimageNum] = location;
		}
		else{
			MoveX = Additional_Value3.x * unitRelativeCursorLocation.x;
			MovingX = MovingX - MoveX;
			
			//avoidanceLocation[afterimageNum].x = avoidanceLocation[afterimageNum - 1].x - MoveX;
			avoidanceLocation[afterimageNum].x = location.x - (MoveX * afterimageNum);
			
		}
		if (relativeCursorLocation.y < MOVE_UP && relativeCursorLocation.y > MOVE_DOWN) {
			avoidanceLocation[afterimageNum].y = location.y;
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
			//avoidanceLocation[afterimageNum].x = location.x;
			avoidanceLocation[afterimageNum].x = avoidanceLocation[afterimageNum - 1].x - Additional_Value3.x * unitRelativeCursorLocation.x;
			//avoidanceLocation[afterimageNum] = location;
		}
		else {
			MoveX = Additional_Value3.x * unitRelativeCursorLocation.x;
			MovingX = MovingX - MoveX;

			avoidanceLocation[afterimageNum].x = avoidanceLocation[afterimageNum - 1].x - MoveX;
			
			
		}
		if (relativeCursorLocation.y < MOVE_UP && relativeCursorLocation.y > MOVE_DOWN) {
			avoidanceLocation[afterimageNum].y = location.y;
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
			//avoidanceLocation[afterimageNum].y = location.y;
			avoidanceLocation[afterimageNum].y = avoidanceLocation[afterimageNum - 1].y + (-1 * Additional_Value3.y * unitRelativeCursorLocation.y);
			//avoidanceLocation[afterimageNum] = location;
		}
		else {
			MoveY = -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
			MovingY = MovingY + MoveY;

			avoidanceLocation[afterimageNum].y = avoidanceLocation[afterimageNum - 1].y - MoveY;
		
		}
		if (relativeCursorLocation.x < MOVE_RIGHT && relativeCursorLocation.x > MOVE_LEFT) {
			avoidanceLocation[afterimageNum].x = location.x;
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
			//avoidanceLocation[afterimageNum].y = location.y;
			avoidanceLocation[afterimageNum].y = avoidanceLocation[afterimageNum - 1].y + (-1 * Additional_Value3.y * unitRelativeCursorLocation.y);
			//avoidanceLocation[afterimageNum]. y= location.y;
		}
		else {
			MoveY = -1 * Additional_Value3.y * unitRelativeCursorLocation.y;
			MovingY = MovingY + MoveY;

			avoidanceLocation[afterimageNum].y = avoidanceLocation[afterimageNum - 1].y - MoveY;

		}
		if (relativeCursorLocation.x < MOVE_RIGHT && relativeCursorLocation.x > MOVE_LEFT) {
			avoidanceLocation[afterimageNum].x = location.x;
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


	//for (int i = 0; i < 64; i++)
	//{
	//	avoidanceLocation[i].x -= MoveX;
	//	avoidanceLocation[i].y -= MoveY;
	//}
	
	if (AvoidanceCnt++ > 20) {
		Additional_Value3.x = Initial_Value;
		Additional_Value3.y = Initial_Value;
		CoolTime = true;
		firstAvoidanceFlg = false;
		AvoidanceCnt = 0;

		afterimageNum = 1;
		for (int i = 1; i < 64; i++)
		{
			avoidanceLocation[i] = { -100, -100 };
		}
	}
	else {
		//avoidanceLocation[afterimageNum].x = location.x - MoveX;
	
		//avoidanceLocation[afterimageNum].y = location.y - MoveY;
		afterimageNum++;
	}



	/*MoveX = unitRelativeCursorLocation.x * 10;
	MovingX = MovingX - MoveX;*/

	/*location.x += unitRelativeCursorLocation.x * 10;
	location.y += unitRelativeCursorLocation.y * 10;*/
}

void Player::Player_CoolTime() {
	
	CoolTime_fps++;
	p_CoolTimeCounter++;
	if (CoolTime_fps > 59) {
		CoolTime_fps = 0;
		Second++;
		if (Second > Cool_Limit/*true*/) {
			CoolTime = false;

			Additional_Value3 = { 0.0f,0.0f };
			Second = 0;
			p_CoolTimeCounter = 0;
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

void Player:: Player_Move_Animation() {

	if (Avoidance_Flg == true) {

		Animation_fps = 40;

		if (fps % Animation_fps > 0 && fps % Animation_fps < 11) {
			PlayerImg = PlayerArrayImg[0];
		}
		else if (fps % Animation_fps > 10 && fps % Animation_fps < 21) {
			PlayerImg = PlayerArrayImg[1];
		}
		else if (fps % Animation_fps > 20 && fps % Animation_fps < 31) {
			PlayerImg = PlayerArrayImg[0];
		}
		else if (fps % Animation_fps > 30 && fps % Animation_fps < 41) {
			PlayerImg = PlayerArrayImg[2];
		}
	}
	else {

		Animation_fps = 60;

		if (fps % Animation_fps > 0 && fps % Animation_fps < 16) {
			PlayerImg = PlayerArrayImg[0];
		}
		else if (fps % Animation_fps > 15 && fps % Animation_fps < 31) {
			PlayerImg = PlayerArrayImg[1];
		}
		else if (fps % Animation_fps > 30 && fps % Animation_fps < 46) {
			PlayerImg = PlayerArrayImg[0];
		}
		else if (fps % Animation_fps > 45 && fps % Animation_fps < 61) {
			PlayerImg = PlayerArrayImg[2];
		}
	}
}


void Player::P_Hit_minotur() {

	Hit_minotur_fps++;

	if (Hit_minotur_fps < 359) {

		A_value = false;
		Additional_Value2 = 0.5f;
	}
	else {

		Hit_minotur_fps = 0;
		Additional_Value2 = 2.0f;
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

	Aiming_RadiusX = value;
}

//照準Yを返す
float Player::GetPlayer_RadiusY() {

	return Aiming_RadiusY;
}

//照準Yをセットする
void  Player::SetPlayer_RadiusY(float value) {

	Aiming_RadiusY = value;
}

//回避のクールタイムを返す
float Player::GetAvoidance_limit() {

	return Cool_Limit;
}

// 回避のクールタイムの時間をセットする
void Player::SetAvoidance_limit(int value) {

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

//現在の体力を返す関数
float Player::GetPlayer_HP() {

	return Player_HP;
}

bool Player::GetPlayer_Avoidance() {
	
	return Avoidance_Flg;
}

void Player::SetPlayer_HP(float value) {

	Player_HP = Player_HP - value;
	if (Player_HP > MaxPlayer_hp)
	{
		Player_HP = MaxPlayer_hp;
	}
}

void Player::SetPlayerHP(float value){
	Player_HP = value;
}

Location Player::Player_Location(){
	return location;
}


