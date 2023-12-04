#include "SmallEnemyBullet.h"

SmallEnemyBullet::SmallEnemyBullet(Location spawnLocation)
{
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/kintama.png");
	location.x = spawnLocation.x;
	location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	diff.x = 0;
	diff.y = 0;
	radius = 5;
	damage = 1.0f;
	speed = 3.0f;
}

SmallEnemyBullet::~SmallEnemyBullet()
{
	DeleteGraph(img);
}

void SmallEnemyBullet::Update()
{

}

void SmallEnemyBullet::Draw() const
{

}
