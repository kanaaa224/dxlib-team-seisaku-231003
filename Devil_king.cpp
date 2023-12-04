#include "Devil_king.h"
#include "Common.h"

Devil_king::Devil_king()
{
	img = LoadGraph("resources/images/enemy_tmp_images/ma.png");
	hp = DEVILKING_MAX_HP;
	shield = 100;
	damage = DEVILKING_ATTAK_DAMAGE;
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;

	//-----大きい弾-----//
}

Devil_king::~Devil_king()
{
	DeleteGraph(img);
}

void Devil_king::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	//移動処理
	location.x = location.x - diff.x;
	location.y = location.y - diff.y;

	if (bigBulletCreateFlg == false) {
		bigBulletCreateCounter++;
	}

	if (bigBulletCreateCounter >= BIG_BULLET_CREATE_TIME) {
		bigBulletCreateFlg = true;
		bigBulletCreateCounter = 0;
	}
}

void Devil_king::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}
