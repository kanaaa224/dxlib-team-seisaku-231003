#include"main.h"

EnemyBullet::EnemyBullet(Location spawnLocation , Player* player)
{
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/kintama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	diff.x = 0;
	diff.y = 0;
	radius = BULLET_RADIUS;
	damage = BULLET_ATTAK_DAMAGE;
	speed = BULLET_SPEED;
	lifeTimeCnt = BULLET_LIFE_TIME;

	angle = 0;

	//プレイヤーの移動量をdiffにセット
	//SetPlayerAmountOfTravel_X(player->Player_MoveX());
	//SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	////プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());
	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * BULLET_SPEED;
	angle = asin(PlayerLoad_Y(location.y) / PlayerLoad(this->location, true));
	angle = angle * (180 / (M_PI));
}

void EnemyBullet::Update(Player* player, Wizard* enemy)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());

	//angle = acos(PlayerLoad_X(location.x) / PlayerLoad(this->location, false));
	float dis_x = PlayerLoad_X(location.x);
	float dis_a = PlayerLoad(this->location, true);
	//angle = angle * (360 / (M_PI * 2));

	location.x += cosf(angle) * speed;
	location.y += sinf(angle) * speed;

	//if (angle < 180)
	//{
	//	if (angle < 90)
	//	{
	//		location.x += cosf(angle) * speed;
	//	}
	//	else
	//	{
	//		location.x -= cosf(angle) * speed;
	//	}
	//	location.y += sinf(angle) * speed;
	//}
	//else
	//{
	//	if (angle < 270)
	//	{
	//		location.x -= cosf(angle) * speed;
	//	}
	//	else
	//	{
	//		location.x += cosf(angle) * speed;
	//	}
	//	location.y -= sinf(angle) * speed;
	//}

	//if (enemy->GetEnemyLocation().x < player->GetLocation().x)
	//{
	//	location.x += cosf(angle) * speed;
	//}
	//else
	//{
	//	location.x -= cosf(angle) * speed;
	//}

	//if (enemy->GetEnemyLocation().y < player->GetLocation().y)
	//{
	//	location.y += sinf(angle) * speed;
	//}
	//else
	//{
	//	location.y -= sinf(angle) * speed;
	//}
	lifeTimeCnt--;
}

void EnemyBullet::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	DrawFormatString(location.x, location.y - radius, 0xffffff, "angle:%f", angle);
}

int EnemyBullet::GetDamage()
{
	return damage;
}

int EnemyBullet::GetlifeTimeCnt()
{
	return lifeTimeCnt;
}
