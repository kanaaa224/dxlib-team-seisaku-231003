#include "Minotaur.h"
#include "Common.h"
#include "Player.h"
#include <math.h>

#define DEBUG
#define BOX_MAX_WIDTH  50  //タックル攻撃予測の矩形の最大の幅
#define BOX_MAX_LENGTH 390 //タックル攻撃予測の矩形の最大の長さ

Minotaur::Minotaur()
{
	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;
	radius = 100;

	//
	boxX_a = 0;
	boxY_a = 0;

	//
	lineSize = 1;
}

void Minotaur::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	TackleUpdate();
	
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
}

void Minotaur::TackleDraw() const
{
	//薄い赤色の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, BOX_MAX_WIDTH);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//濃い赤色の矩形
	//DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, lineSize);
}

void Minotaur::RoarUpdate()
{

}

void Minotaur::RoarDraw() const
{

}
