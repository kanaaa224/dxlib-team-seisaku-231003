#include "Minotaur.h"
#include "Common.h"
#include "Player.h"
#include <math.h>

#define DEBUG

Minotaur::Minotaur()
{
	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;
	radius = 100;

	tackleFlg = false;
	doOneFlg = false;
	coolTimeFlg = false;
	tackleCoolTimeCnt = 0;

	//
	boxX_a = 0;
	boxY_a = 0;

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
	
	//座標計算
	location.x = location.x - diff.x;
	location.y = location.y - diff.y;
}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	
	if (coolTimeFlg == false) {
		TackleDraw();
	}

#ifdef DEBUG

	//DrawLine(location.x, location.y, location.x, location.y - tmpy, C_GREEN, 5);//縦
	//DrawLine(location.x, location.y, location.x - tmpx, location.y, C_BLUE, 5);//横
	//DrawLine(location.x, location.y, location.x - tmpx, location.y - tmpy, C_RED, 10);
#endif // DEBUG

}

void Minotaur::TackleUpdate()
{
	if (doOneFlg == false && coolTimeFlg == false) {
		boxX_a = location.x - dL.x;
		boxY_a = location.y - dL.y;

		//箱の長さを５０大きくする
		if (boxY_a < 0) {
			boxY_a = -300;
		}
		else if (boxY_a > 0) {
			boxY_a = +300;
		}

		//プレイヤーとの距離が箱の長さの最大を超えるなら
		if (boxY_a >= 390) {
			boxY_a = 390;
		}
		doOneFlg = true;
	}
	
	

	if (coolTimeFlg == false) {
		//濃い赤色の矩形の太さ//
		if (lineSize <= BOX_MAX_WIDTH) {//太さが最大の太さじゃないなら
			lineSizeChageCnt++;
		}
		else if (lineSize >= BOX_MAX_WIDTH) {//太さが最大の太さなら
			doOneFlg = false;
			lineSize = 0;
			tackleFlg = true;
		}

		if (lineSizeChageCnt >= TACKLE_SPEED) {
			lineSize++;
			lineSizeChageCnt = 0;
		}
	}
	
	//タックル開始直後
	if (tackleFlg == true) {
		location.x = location.x - boxX_a;
		location.y = location.y - boxY_a;
		tackleFlg = false;
		coolTimeFlg = true;
	}

	//タックルのクールタイム
	if (coolTimeFlg == true) {
		tackleCoolTimeCnt++;
	}
	else if (coolTimeFlg == false) {
		tackleCoolTimeCnt = 0;
	}

	if (tackleCoolTimeCnt >= TACKLE_COOLTIME) {
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
