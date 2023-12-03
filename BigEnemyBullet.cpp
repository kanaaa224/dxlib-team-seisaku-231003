#include "BigEnemyBullet.h"
#include "Common.h"
#define DEBUG

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
	speed = 1.0f;
	lifeTimeCnt = SECOND_FRAME(10);
	SetPlayer_Location(player->GetLocation());
	vector.x = Normalization_X(PlayerLoadX(location.x), PlayerLoadY(location.y)) * speed;
	vector.y = Normalization_Y(PlayerLoadX(location.x), PlayerLoadY(location.y)) * speed;
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
	RedFlashing();
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

#ifdef DEBUG
	DrawFormatString(location.x, location.y, C_BLACK, "lifeTime:%d",lifeTimeCnt);
#endif // DEBUG

}

void BigEnemyBullet::RedFlashing()
{
	if (redDrawCounter >= 510) {
		if (redDrawCounter % 15 == 0 || redDrawCounter % 15 == 1 || redDrawCounter % 15 == 2 || redDrawCounter % 15 == 3 || redDrawCounter % 15 == 4) {
			redDrawFlg = true;
		}
		else {
			redDrawFlg = false;
		}
	}
}
