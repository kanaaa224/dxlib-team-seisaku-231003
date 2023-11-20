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
	
	location.x = location.x - diff.x;
	location.y = location.y - diff.y;
}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	
	TackleDraw();

#ifdef DEBUG

	//DrawLine(location.x, location.y, location.x, location.y - tmpy, C_GREEN, 5);//縦
	//DrawLine(location.x, location.y, location.x - tmpx, location.y, C_BLUE, 5);//横
	//DrawLine(location.x, location.y, location.x - tmpx, location.y - tmpy, C_RED, 10);
#endif // DEBUG

}

void Minotaur::TackleUpdate()
{
	boxX_a = location.x - dL.x;
	boxY_a = location.y - dL.y;
	if (boxY_a >= 390) {
		boxY_a = 390;
	}
	

	//濃い赤色の矩形の太さ//
	if (lineSize <= BOX_MAX_WIDTH) {//太さが最大の太さじゃないなら
		lineSizeChageCnt++;
	}

	if (lineSizeChageCnt >= 5) {
		lineSize++;
		lineSizeChageCnt = 0;
	}
	//------------------------------//
	tackleFlg = true;
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
