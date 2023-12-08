#include "SmallEnemyBullet.h"
#include "Common.h"

SmallEnemyBullet::SmallEnemyBullet(Location spawnLocation)
{
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/tama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	diff.x = 0;
	diff.y = 0;
	radius = 5;
	damage = 1.0f;
	speed = SetGetRand(2, 3);
	vector.x = Normalization_X(SetGetRand(-1, 1), SetGetRand(-1, 1)) * speed;
	vector.y = Normalization_Y(SetGetRand(-1, 1), SetGetRand(-1, 1)) * speed;

	lifeTimeCnt = SECOND_FRAME(20);
}

SmallEnemyBullet::~SmallEnemyBullet()
{
	DeleteGraph(img);
}

void SmallEnemyBullet::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());

	location.x += vector.x - diff.x;
	location.y += vector.y - diff.y;

	lifeTimeCnt--;
}

void SmallEnemyBullet::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}

int SmallEnemyBullet::GetLifeTimeCnt()
{
	return lifeTimeCnt;
}
