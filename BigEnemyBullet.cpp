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

	//赤色の点滅表示処理
	redDrawCounter++;
	if (redDrawCounter >= redDrawInterval) {
		redDrawInterval -= redDrawCounter / 2;
		if (redDrawInterval <= 0) {
			redDrawInterval = 1;
		}
		redDrawCounter = 0;
		redDrawFlg = true;
	}

	if (redDrawCounter == 1) {
		redDrawFlg = false;
	}
}

void BigEnemyBullet::Draw() const
{
	if (redDrawFlg == false) {
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
	}
	else if (redDrawFlg == true) {
		SetDrawBright(255, 0, 0);
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
		SetDrawBright(255, 255, 255);
	}
}
