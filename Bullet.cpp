#include "Bullet.h"
#include "Common.h"
#include <math.h>

Bullet::Bullet(Location spawnLocation)
{
	//•Ï”‚Ì‰Šú‰»
	img = LoadGraph("resources/images/enemy_tmp_images/kintama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	radius = BULLET_RADIUS;
	damage = BULLET_ATTAK_DAMAGE;
	speed = BULLET_SPEED;
}

void Bullet::Update()
{
	vector = CaleVector(location);

	location.x = location.x + vector.x;
	location.y = location.y + vector.y;
}

void Bullet::Draw()
{
	DrawRotaGraph(location.x, location.y, 1, 0, img, TRUE);
}

Vector Bullet::CaleVector(Location location)
{
	Vector r;
	Location a;

	a.x = dL.x - location.x;
	if (dL.x > location.x) {
		a.x -= (radius + 5);
	}
	else {
		a.x += (radius + 5);
	}

	a.y = dL.y - location.y;
	if (dL.y > location.y) {
		a.y -= (radius + 5);
	}
	else {
		a.y += (radius + 5);
	}

	Location tmp;
	tmp.x = sqrt(pow(a.x, 2) + pow(a.y, 2));
	r.x = (location.x / tmp.x) * speed;

	tmp.y = sqrt(pow(a.y, 2) + pow(a.y, 2));
	r.y = (location.y / tmp.y) * speed;

	return r;
}
