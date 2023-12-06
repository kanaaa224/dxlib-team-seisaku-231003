#include "BigEnemyBullet.h"
#include "Common.h"
#define DEBUG

BigEnemyBullet::BigEnemyBullet(Location spawnLocation, Player* player)
{
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());
	//変数の初期化
	img = LoadGraph("resources/images/enemy_tmp_images/dekatama.png");

	location.x = spawnLocation.x;
	location.y = spawnLocation.y;

	float x = spawnLocation.x - dL.x;
	float y = spawnLocation.y - dL.y;
	float at = atan2f(y, x);

	location.x += cosf(at) * -70;
	location.y += sinf(at) * -70;

	//location.x = spawnLocation.x;
	//location.y = spawnLocation.y;
	vector.x = 0;
	vector.y = 0;
	diff.x = 0;
	diff.y = 0;
	radius = 25;
	damage = 1;
	speed = 2.0f;
	lifeTimeCnt = SECOND_FRAME(LIFETIME);
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
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());
	
	//移動処理
	if (hitWeapon == false) {
		location.x += vector.x - diff.x;
		location.y += vector.y - diff.y;
	}
	else if (hitWeapon == true) {
		//プレイヤーのカーソルの位置を取得する関数
		float x, y;
		x = player->Player_AimingX() - dL.x;
		y = player->Player_AimingY() - dL.y;
		
		vector.x = Normalization_X(x, y) * speed;
		vector.y = Normalization_Y(x, y) * speed;
		location.x += vector.x - diff.x;
		location.y += vector.y - diff.y;
		hitWeapon = false;
	}
	

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
	
#endif // DEBUG

}

void BigEnemyBullet::RedFlashing()
{
	if (redDrawCounter >= SECOND_FRAME(LIFETIME)- SECOND_FRAME(1)) {
		if (redDrawCounter % 15 == 0 || redDrawCounter % 15 == 1 || redDrawCounter % 15 == 2 || redDrawCounter % 15 == 3 || redDrawCounter % 15 == 4) {
			redDrawFlg = true;
		}
		else {
			redDrawFlg = false;
		}
	}
}
