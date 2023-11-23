#include "Slime.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"
#include"Stage.h"

#define DEBUG

Slime::Slime(Player* player,int arrayNum, int SlimeMaxNum)
{
	//画像読込
	img = LoadGraph("resources/images/enemy_tmp_images/slime_cat.png");
	//変数の初期化
	hp = SLIME_HP_MAX;
	damage = SLIME_ATTAK_DAMAGE;
	location.x = 0;
	location.y = 0;
	vector.x = 0;
	vector.y = 0;
	

	respawnTimeCnt = 0;
	respawnTime = SetRespawnTime(arrayNum, SlimeMaxNum, 10);

	//リスポーンポイント決め
	SetRespawnPoint(player,10,arrayNum);
}

void Slime::Update(int arrayNum, Player* player, weapon* w, Stage stage)
{
	if (respawnFlg == true && hp > 0) {
		//プレイヤーの移動量をdiffにセット
		SetPlayerAmountOfTravel_X(player->Player_MoveX());
		SetPlayerAmountOfTravel_Y(player->Player_MoveY());
		//プレイヤーの座標をdiffLocationにセット
		SetPlayer_Location(player->GetLocation());

		//移動処理//
		if (hitWeaponFlg == false) {
			X();
			location.x += vector.x - diff.x;
			Y();
			location.y += vector.y - diff.y;
		}
		else if (hitWeaponFlg == true) {
			vector.x = -vector.x * KNCKBACK;
			location.x += vector.x - diff.x;
			vector.y = -vector.y * KNCKBACK;
			location.y += vector.y - diff.y;
			//武器からの攻撃とHPが０以上なら赤く表示する
			if (hitWeaponFlg == true && hp > 0) {
				redDrawFlg = true;
			}
			hitWeaponFlg = false;
		}
	}

	if (hp <= 0) {
		alphaNum -= 5;
	}

	//Cnt
	if (respawnTimeCnt == respawnTime) {//設定された時間になったらrespawnFlgをtrue
		respawnFlg = true;
	}
	respawnTimeCnt++;//リスポーンCnt

	
	if (redFrameCounter == RED_FRAME) {
		redDrawFlg = false;
		redFrameCounter = 0;
	}
	if (redDrawFlg == true) {
		redFrameCounter++;
	}

	//デバッグ（マクロのDEBUGをコメントアウト又はReleaseにすれば使えなくなります）
#ifdef DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_D) == PRESS && hp >= 0) {
		hitWeaponFlg = true;
		hp -= 10;
	}
	else {
		hitWeaponFlg = false;
	}
#endif // DEBUG
	
}

void Slime::Draw(int arrayNum) const
{
	if (respawnFlg == true) {
		
		if (hp <= 0) {//HPが０の時
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaNum);
			DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else {//通常時
			DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
		}

		if (redDrawFlg == true) {//武器からダメージを受けた時とHPが０じゃない時、敵を赤色表示
			SetDrawBright(255, 0, 0);
			DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
			SetDrawBright(255, 255, 255);
		}

		//デバッグ表示（マクロのDEBUGをコメントアウト又はReleaseにすれば使えなくなります）
#ifdef DEBUG
		float hpRate = hp / SLIME_HP_MAX;
		float sizeRate = -20.0f + 40.0f * hpRate;
		
		if (InputCtrl::GetKeyState(KEY_INPUT_H) == PRESSED) {//HP表示
			if (hp > 0) {
				DrawBox((int)location.x - 20, (int)location.y - 30, (int)location.x + 20, (int)location.y - 25, C_BLACK, TRUE);
				DrawBox((int)location.x - 20, (int)location.y - 30, (int)location.x + (int)sizeRate, (int)location.y - 25, C_RED, TRUE);
				DrawFormatString((int)location.x, (int)location.y, C_RED, "hpRate:%.2f", hpRate);
				DrawFormatString((int)location.x, (int)location.y + 15, C_RED, "sizeRate:%.2f", sizeRate);
			}
		}

		if (InputCtrl::GetKeyState(KEY_INPUT_S) == PRESSED) {//ステータス表示
			DrawFormatString((int)location.x, (int)location.y, C_RED, "array:%d", arrayNum);
			DrawFormatString((int)location.x, (int)location.y + 15, C_RED, "VX:%.2f, VY:%.2f", vector.x, vector.y);
			DrawFormatString((int)location.x, (int)location.y + 30, C_RED, "dx:%.2f, dy:%.2f", diff.x, diff.y);
			DrawFormatString((int)location.x, (int)location.y + 45, C_RED, "HP:%d", hp);
			DrawFormatString((int)location.x, (int)location.y + 60, C_RED, "HitFlg:%d", hitFlg);
		}
#endif // DEBUG
	}
}

void Slime::X()
{
	if (hitFlg == HIT) {
		vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
		vector.x = vector.x + caleVector.x;
	}
	else if (hitFlg == NO_COLLISION) {
		vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
	}
}

void Slime::Y()
{
	if (hitFlg == HIT) {
		vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
		vector.y = vector.y + caleVector.y;
		hitFlg = NO_COLLISION;
	}
	else if (hitFlg == NO_COLLISION) {
		vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
	}
}

float Slime::GetSlimeDamage()
{
	return damage;
}
