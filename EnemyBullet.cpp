#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(Location spawnLocation)
{
	//ïœêîÇÃèâä˙âª
	img = LoadGraph("resources/images/enemy_tmp_images/kintama.png");
	spwLocation.x = spawnLocation.x;
	spwLocation.y = spawnLocation.y;
	speed = BULLET_SPEED;
	//vector = CaleVector(spwLocation);
	location.x = spwLocation.x;
	location.y = spwLocation.y;
	vector.x = 0;
	vector.y = 0;
	radius = BULLET_RADIUS;
	damage = BULLET_ATTAK_DAMAGE;
	lifeTimeCnt = 0;
	
}

void EnemyBullet::Update()
{
	location.x = location.x + vector.x;
	location.y = location.y + vector.y;

	lifeTimeCnt++;
}

void EnemyBullet::Draw()
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}

Vector EnemyBullet::CaleVector(Location location)
{
	Vector r;
	Location tmp;
	tmp.x = dL.x - location.x;
	tmp.y = dL.y - location.y;
	r.x = sqrt(pow(tmp.x, 2) + pow(tmp.y, 2));
	r.y = r.x;

	return r;
}

int EnemyBullet::GetDamage()
{
	return damage;
}

int EnemyBullet::GetlifeTimeCnt()
{
	return lifeTimeCnt;
}
