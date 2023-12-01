#include "BigEnemyBullet.h"

BigEnemyBullet::BigEnemyBullet(Location spawnLocation, Player* player)
{
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/dekakintama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	diff.x = 0;
	diff.y = 0;
	radius = 25;
	damage = 1;
	speed = 2.0f;
	lifeTimeCnt = SECOND_FRAME(5);
	SetPlayer_Location(player->GetLocation());
	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
}

BigEnemyBullet::~BigEnemyBullet()
{

}

void BigEnemyBullet::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());

	location.x += vector.x - diff.x;
	location.y += vector.y - diff.y;

	lifeTimeCnt--;
}

void BigEnemyBullet::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}
