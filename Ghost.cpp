#include "Ghost.h"
#include "Common.h"
//#define DEBUG

Ghost::Ghost(int arrayNum)
{
	img = LoadGraph("resources/images/enemy_images/devilKing/Weapon/ghost.png");
	hp = 1;
	respawnTime = SetRespawnTimeGhost(arrayNum);
	location = SetRespawnPostionGhost(arrayNum);
	radius = 5;
	damage = 1;
}

Ghost::~Ghost()
{
	DeleteGraph(img);
}

void Ghost::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * 1.0f;
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * 1.0f;
	location.x += vector.x - diff.x;
	location.y += vector.y - diff.y;
}

void Ghost::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawRotaGraph((int)location.x, (int)location.y, 1.5, 0, img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

#ifdef DEBUG
	DrawCircle((int)location.x, (int)location.y, radius, C_RED, FALSE, 2);
#endif // DEBUG

}

int Ghost::SetRespawnTimeGhost(int arrayNum)
{
	float r;
	if (arrayNum >= 100) {
		r = SECOND_FRAME(10);
	}
	else {
		r = SECOND_FRAME(0);
	}

	return r;
}

Location Ghost::SetRespawnPostionGhost(int arrayNum)
{
	Location r;
	int section = GetRand(3);
	
	switch (section)
	{
	case 0://上
		r.y = 10;
		r.x = SetGetRand(10, 1270);
		break;
	case 1://下
		r.y = 710;
		r.x = SetGetRand(10, 1270);
		break;
	case 2://右
		r.x = 1270;
		r.y = SetGetRand(10, 710);
		break;
	case 3://左
		r.x = 10;
		r.y = SetGetRand(10, 710);
		break;
	default:
		break;
	}

	return r;
}
