#include "Minotaur.h"
#include "Common.h"
#include "Player.h"
#include <math.h>

//#define DEBUG

Minotaur::Minotaur()
{
	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;
	vector.x = 1;
	vector.y = 1;
	radius = 100;

	tackleFlg = false;
	doOneFlg = false;
	coolTimeFlg = false;
	tackleCoolTimeCnt = 0;
	tackleCoolTime = 0;
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
	
	//移動
	if (tackleFlg = false) {
		location.x = location.x - diff.x;
		location.y = location.y - diff.y;

		vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
		vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
	}
	else if (tackleFlg == true) {
		location.x += vector.x - diff.x;
		location.y += vector.y - diff.y;
		if (location.y == tackleTmpL.y) {
			doOneFlg = false;
			tackleFlg = false;
		}
	}
}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	
	if (coolTimeFlg == false) {
		TackleDraw();
	}

#ifdef DEBUG
	DrawFormatString(300, 600, C_GREEN, "%.2f", pLength);
	DrawFormatString(300, 620, C_GREEN, "%.2f", boxX_d);

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
	
	//タックルのクールタイムを決める
	if (pLength >= 200) {
		tackleCoolTime = 60;
	}
	else if (pLength < 200) {
		tackleCoolTime = 0;
	}

	if (coolTimeFlg == false) {
		//濃い赤色の矩形の太さ//
		if (lineSize <= BOX_MAX_WIDTH) {//太さが最大の太さじゃないなら
			lineSizeChageCnt++;
		}
		else if (lineSize >= BOX_MAX_WIDTH) {//太さが最大の太さなら
			//doOneFlg = false;
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
		//
		if (doOneFlg == false && coolTimeFlg == false) {
			tackleTmpL.x = location.x - boxX_a;
			tackleTmpL.y = location.y - boxY_a;
			doOneFlg = true;
		}

		/*location.x = location.x - boxX_a;
		location.y = location.y - boxY_a;*/
		
		coolTimeFlg = true;
	}

	//タックルのクールタイム
	if (coolTimeFlg == true) {
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, lineSize);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Minotaur::RoarUpdate()
{

}

void Minotaur::RoarDraw() const
{

}
