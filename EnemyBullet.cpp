#include "EnemyBullet.h"
#include "Player.h"

EnemyBullet::EnemyBullet(Location spawnLocation)
{
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/kintama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	radius = BULLET_RADIUS;
	damage = BULLET_ATTAK_DAMAGE;
	speed = BULLET_SPEED;
	lifeTimeCnt = BULLET_LIFE_TIME;
	
}

void EnemyBullet::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
	location.x = location.x + vector.x;
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
	location.y = location.y + vector.y;

	lifeTimeCnt--;
}

void EnemyBullet::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}

int EnemyBullet::GetDamage()
{
	return damage;
}

int EnemyBullet::GetlifeTimeCnt()
{
	return lifeTimeCnt;
}
