#include "Slime.h"
#include "Common.h"

Slime::Slime()
{
	//画像読込
	img = LoadGraph("resources/images/slime_cat.png");
	//変数の初期化
	location.x = 0;
	location.y = 0;
	vector.x = 0;
	vector.y = 0;

	//リスポーンポイント決め
	int tmp = GetRand(11);
	if (tmp == 0) {
		respawnPosition = 0;
		location.x = POINT_0_X;
		location.y = POINT_0_Y;
	}
	else if (tmp == 1) {
		respawnPosition = 1;
		location.x = POINT_1_X;
		location.y = POINT_1_Y;
	}
	else if (tmp == 2) {
		respawnPosition = 2;
		location.x = POINT_2_X;
		location.y = POINT_2_Y;
	}
	else if (tmp == 3) {
		respawnPosition = 3;
		location.x = POINT_3_X;
		location.y = POINT_3_Y;
	}
	else if (tmp == 4) {
		respawnPosition = 4;
		location.x = POINT_4_X;
		location.y = POINT_4_Y;
	}
	else if (tmp == 5) {
		respawnPosition = 5;
		location.x = POINT_5_X;
		location.y = POINT_5_Y;
	}
	else if (tmp == 6) {
		respawnPosition = 6;
		location.x = POINT_6_X;
		location.y = POINT_6_Y;
	}
	else if (tmp == 7) {
		respawnPosition = 7;
		location.x = POINT_7_X;
		location.y = POINT_7_Y;
	}
	else if (tmp == 8) {
		respawnPosition = 8;
		location.x = POINT_8_X;
		location.y = POINT_8_Y;
	}
	else if (tmp == 9) {
		respawnPosition = 9;
		location.x = POINT_9_X;
		location.y = POINT_9_Y;
	}
	else if (tmp == 10) {
		respawnPosition = 10;
		location.x = POINT_10_X;
		location.y = POINT_10_Y;
	}
	else if (tmp == 11) {
		respawnPosition = 11;
		location.x = POINT_11_X;
		location.y = POINT_11_Y;
	}
}

void Slime::Update()
{
	//移動処理//
	X();
	location.x += vector.x;
	Y();
	location.y += vector.y;
}

void Slime::Draw()
{
	DrawGraph((int)location.x, (int)location.y, img, TRUE);
}

void Slime::X()
{
	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y));
}

void Slime::Y()
{
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y));
}
