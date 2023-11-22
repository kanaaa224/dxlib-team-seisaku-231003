#include "Minotaur.h"
#include "Common.h"
#include "Player.h"
#include <math.h>

#define DEBUG

Minotaur::Minotaur()
{
	debugCnt = 0;

	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;

	tackleTmpL.x = 0;
	tackleTmpL.y = 0;

	vector.x = 0;
	vector.y = 0;

	radius = 100;

	tackleFlg = false;
	doOneFlg = false;
	coolTimeFlg = false;
	tackleCoolTimeCnt = 0;
	tackleCoolTime = 60;
	tackleSpeed = TACKLE_SPEED;

	//
	boxX_a = 0;
	boxY_a = 0;

	boxX_d = 0;
	boxY_d = 0;

	//
	lineSize = 1;
	lineSizeChageCnt = 0;
}

void Minotaur::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	TackleUpdate();//タックル
	
	//移動処理
	if (tackleFlg == false) {
		location.x = location.x - diff.x;
		location.y = location.y - diff.y;
	}
	else if (tackleFlg == true) {//タックル中
		location.x += vector.x - diff.x;
		location.y += vector.y - diff.y;
	}
}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	
	if (coolTimeFlg == false && tackleFlg == false) {
		TackleDraw();
	}

#ifdef DEBUG
	DrawFormatString(300, 600, C_GREEN, "X:%.2f Y:%.2f", location.x ,location.y);
	DrawFormatString(300, 620, C_GREEN, "VX:%.2f VY:%.2f", vector.x, vector.y);
	DrawFormatString(300, 640, C_GREEN, "TX:%.2f TY:%.2f", tackleTmpL.x, tackleTmpL.y);
	DrawFormatString(300, 660, C_GREEN, "CTC:%d", tackleCoolTimeCnt);
	DrawFormatString(300, 680, C_GREEN, "DC:%d", debugCnt);

	//Flg
	DrawFormatString(500, 600, C_GREEN, "CTF:%d", coolTimeFlg);
	DrawFormatString(500, 620, C_GREEN, "TF:%d", tackleFlg);
	DrawFormatString(500, 640, C_GREEN, "DOF:%d", doOneFlg);

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
			lineSizeChageCnt++;
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
	
	
	//タックル開始直後
	if (tackleFlg == true) {
		if (doOneFlg == false) {
			//タックルした時に最終的に移動する場所
			tackleTmpL.x = location.x - boxX_a;
			tackleTmpL.y = location.y - boxY_a;
			debugCnt++;
			//タックル中の移動量をセット
			vector.x = Normalization_X(M_PLX(location.x), M_PLY(location.y));
			vector.y = Normalization_Y(M_PLX(location.x), M_PLY(location.y));
			doOneFlg = true;
		}

		if (diff.x < 0) {
			tackleTmpL.x += diff.x;
		}
		else if (diff.x > 0) {
			tackleTmpL.x -= diff.x;
		}
		
		if (diff.y < 0) {
			tackleTmpL.y += diff.y;
		}
		else if (diff.y > 0) {
			tackleTmpL.y -= diff.y;
		}

		//タックルの最終地点移動
		if (tackleTmpL.x == location.x && tackleTmpL.y == location.y) {
			tackleFlg = false;
			coolTimeFlg = true;
			doOneFlg = false;
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

}

void Minotaur::RoarDraw() const
{

}
