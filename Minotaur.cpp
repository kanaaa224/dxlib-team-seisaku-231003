#include "Minotaur.h"
#include "Common.h"
#include "Player.h"
#include <math.h>
#include "inputCtrl.h"

//#define DEBUG

Minotaur::Minotaur()
{
	debugCnt = 0;

	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	hp = MINOTAUR_MAX_HP;
	damage = 10;
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;

	tackleTmpL.x = 0;
	tackleTmpL.y = 0;

	vector.x = 0;
	vector.y = 0;

	radius = 50;

	respawnFlg = true;

	tackleFlg = false;
	doOneFlg = false;
	coolTimeFlg = false;
	tackleCoolTimeCnt = 0;
	tackleCoolTime = 240;
	tackleSpeed = TACKLE_SPEED;
	nowTackleCnt = 0;
	tackleCnt = 0;

	roarStartFlg = false;

	//-----タックル-----//
	//薄い赤色の矩形
	boxX_a = 0;
	boxY_a = 0;
	boxX_d = 0;
	boxY_d = 0;

	//濃い赤色の矩形
	lineSize = 1;
	lineSizeChageCnt = 0;

	//-----咆哮-----//
	roarCnt = 0;
	roarFlg = false;
	roarRadius = 0;
	roarFinFlg = false;
	playerRoarHitFlg = false;

	//-----その他-----//
	hpRate = 1;
	hpSize = 0;
}

void Minotaur::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	if (roarStartFlg == false) {
		TackleUpdate();//タックル
	}
	else if (roarStartFlg == true) {
		RoarUpdate();//咆哮
		if (roarEffectFlg == true) {
			RoarEffectUpdate();
		}
	}
	
	
	//移動処理
	if (tackleFlg == false) {
		location.x = location.x - diff.x;
		location.y = location.y - diff.y;
	}
	else if (tackleFlg == true) {//タックル中
		location.x += vector.x * TACKLE_SPEED - diff.x;
		location.y += vector.y * TACKLE_SPEED - diff.y;
	}

	if (hp <= 0) {
		respawnFlg = false;
	}

#ifdef DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_D) == PRESS && hp >= 0) {
		hitWeaponFlg = true;
		hp -= 10;
	}
	else {
		hitWeaponFlg = false;
	}
#endif // DEBUG

}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	
	if (coolTimeFlg == false && tackleFlg == false) {
		TackleDraw();
	}
	
	if (roarStartFlg == true) {
		RoarDraw();
	}

#ifdef DEBUG
	DrawFormatString(300, 560, C_RED, "%d", tackleCnt);

	DrawCircle(location.x, location.y, radius, C_RED, FALSE, 1);
	DrawFormatString(300, 500, C_GREEN, "HP:%.2f", hp);

	

	DrawLine(location.x, location.y, location.x, location.y - boxY_a, C_GREEN, 5);//縦
	DrawLine(location.x, location.y, location.x - boxX_a, location.y, C_BLUE, 5);//横
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, 10);
#endif // DEBUG

}

void Minotaur::TackleUpdate()
{
	pLength = PlayerLoad(location, false);
	if (coolTimeFlg == false && tackleFlg == false) {

		boxX_a = location.x - dL.x;
		boxY_a = location.y - dL.y;

		//長さを一定にする
		boxX_d = fabsf(BOX_MAX_LENGTH / PlayerLoad(location, false));
		boxX_a *= boxX_d;
		boxY_d = fabsf(BOX_MAX_LENGTH / PlayerLoad(location, false));
		boxY_a *= boxY_d;
	}

	if (coolTimeFlg == false) {
		//濃い赤色の矩形の太さ//
		if (lineSize <= BOX_MAX_WIDTH) {//太さが最大の太さじゃないなら
			lineSizeChageCnt += 4;
		}
		else if (lineSize >= BOX_MAX_WIDTH) {//太さが最大の太さなら
			lineSize = 0;
			tackleFlg = true;
		}

		if (lineSizeChageCnt >= tackleSpeed) {
			lineSize++;
			lineSizeChageCnt = 0;
		}
	}
	
	
	//タックル開始
	if (tackleFlg == true) {
		if (doOneFlg == false) {
			//タックルした時に最終的に移動する場所
			tackleTmpL.x = location.x - boxX_a;
			tackleTmpL.y = location.y - boxY_a;
			//タックル中の移動量をセット
			vector.x = Normalization_X(M_PLX(location.x), M_PLY(location.y));
			vector.y = Normalization_Y(M_PLX(location.x), M_PLY(location.y));
			doOneFlg = true;
		}

		nowTackleCnt++;
		//タックルの最終地点移動
		if (nowTackleCnt >= BOX_MAX_LENGTH / TACKLE_SPEED) {
			tackleFlg = false;
			coolTimeFlg = true;
			doOneFlg = false;
			nowTackleCnt = 0;
			tackleCnt++;
			lineSize = 0;
		}
	}

	//タックルのクールタイム
	if (coolTimeFlg == true && tackleFlg == false) {
		tackleCoolTimeCnt++;
	}
	else if (coolTimeFlg == false) {
		tackleCoolTimeCnt = 0;
	}

	if (tackleCoolTimeCnt >= tackleCoolTime) {
		coolTimeFlg = false;
	}

	if (tackleCnt >= 3) {
		roarStartFlg = true;
	}
}

void Minotaur::TackleDraw() const
{
	//薄い赤色の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, BOX_MAX_WIDTH);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//濃い赤色の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, lineSize);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Minotaur::TackleEffectUpdate()
{

}

void Minotaur::TackleEffectDraw() const
{

}

float Minotaur::M_PLX(float location_X)
{
	float r = dL.x - location.x;
	return r;
}

float Minotaur::M_PLY(float location_Y)
{
	float r = dL.y - location.y;
	return r;
}

void Minotaur::RoarUpdate()
{
	roarFlg = true;
	if (roarRadius <= ROAR_RADIUS) {
		roarRadius += 2;
	}
	else if (roarRadius >= ROAR_RADIUS) {
		roarEffectFlg = true;
	}

	if (roarEffectFinFlg == true) {
		roarFinFlg = true;
	}

	if (roarFinFlg == true) {
		roarFlg = false;
		roarStartFlg = false;
		tackleCnt = 0;
		roarRadius = 0;
		roarFinFlg = false;
		roarEffectFinFlg = false;
		roarEffectFlg = false;
	}
}

void Minotaur::RoarDraw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawCircle(location.x, location.y, ROAR_RADIUS, C_RED, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawCircle(location.x, location.y, roarRadius, C_RED, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Minotaur::RoarEffectUpdate()
{
	//プレイヤーとの当たり判定
	float a = location.x - dL.x;
	float b = location.y - dL.y;
	float c = sqrtf(pow(a, 2) + pow(b, 2));
	if (c <= ROAR_RADIUS + PLAYER_RADIUS) {//当たった
		playerRoarHitFlg = true;
	}
	else {
		playerRoarHitFlg = false;
	}


	roarEffectFinFlg = true;
}

void Minotaur::RoarEffectDraw() const
{

}

bool Minotaur::GetRoarHitFlg()
{
	return playerRoarHitFlg;
}

void Minotaur::DeathEffectUpdate()
{

}

void Minotaur::DeathEffectDraw() const
{
	
}

float Minotaur::GetHP()
{
	return hp;
}
