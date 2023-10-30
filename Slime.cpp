#include "Slime.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"

Slime::Slime(int arrayNum)
{
	//画像読込
	img = LoadGraph("resources/images/slime_cat.png");
	//変数の初期化
	location.x = 0;
	location.y = 0;
	vector.x = 0;
	vector.y = 0;
	

	respawnTimeCnt = 0;
	respawnTime = arrayNum * 60;

	tmpVX = 0;
	tmpVY = 0;

	//リスポーンポイント決め
	SetRespawnPoint();
}

void Slime::Update(int arrayNum, Player* player)
{
	if (respawnFlg == true) {
		//プレイヤーの移動量をdiffにセット
		SetPlayerAmountOfTravel_X(player->Player_MoveX());
		SetPlayerAmountOfTravel_Y(player->Player_MoveY());

		

		//移動処理//
		if (hitFlg == HIT) {//当たった時
			X();
			vector.x = 0;
			location.x += vector.x - diff.x;
			Y();
			vector.y = 0;
			location.y += vector.y - diff.y;

			hitFlg = NO_COLLISION;
		}
		else if (hitFlg == NO_COLLISION) {//当たってない時
			X();
			location.x += vector.x - diff.x;
			Y();
			location.y += vector.y - diff.y;
		}
	}

	//Cnt
	if (respawnTimeCnt == respawnTime) {
		respawnFlg = true;
	}
	respawnTimeCnt++;
}

void Slime::Draw(int arrayNum)
{
	if (respawnFlg == true) {
		/*if (InputCtrl::GetKeyState(KEY_INPUT_H) == PRESSED) {
			DrawBox()
		}*/
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
		DrawFormatString((int)location.x, (int)location.y, C_RED, "%d", arrayNum);
		DrawFormatString((int)location.x, (int)location.y + 15, C_RED, "VX:%f, VY:%f", vector.x,vector.y);
		DrawFormatString((int)location.x, (int)location.y + 30, C_RED, "dx:%f, dy:%f", diff.x,diff.y);
	}
}

void Slime::X()
{
	vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y));
}

void Slime::Y()
{
	vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y));
}

int Slime::GetStageNum()
{
	int r = SLIME_1_STAGE_NUM;
	return r;
}

int Slime::GetSlimeDamage()
{
	return 0;
}
