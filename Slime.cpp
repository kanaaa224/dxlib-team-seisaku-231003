#include "Slime.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"
#include"Stage.h"

//#define DEBUG

Slime::Slime(Player* player,int arrayNum, int SlimeMaxNum, int stage)
{
	//変数の初期化
	hp = EnemyHP(stage,SLIME_HP_MAX);
	damage = EnemyAttckDamage(stage, SLIME_ATTAK_DAMAGE);
	location.x = 0;
	location.y = 0;
	vector.x = 0;
	vector.y = 0;
	tmpVector.x = 0;
	tmpVector.y = 0;

	respawnTimeCnt = 0;
	respawnTime = SetRespawnTime(arrayNum, SlimeMaxNum, 10);

	//リスポーンポイント決め
	SetRespawnPoint(player,10,arrayNum);

	//-----画像に関わる変数-----//
	//画像読込
	imgArray[0] = LoadGraph("resources/images/enemy_images/slime/slime03_blue01_9.png");
	imgArray[1] = LoadGraph("resources/images/enemy_images/slime/slime03_blue01_10.png");
	//画像切り替え用フレームカウント変数の初期化
	imgFrameCounter = 0;
	//画像格納用変数の初期化
	img = imgArray[0];
	//画像左右
	imgAngle = 0;
}

Slime::~Slime()
{
	//画像をdelete
	DeleteGraph(imgArray[0]);
	DeleteGraph(imgArray[1]);
	DeleteGraph(img);
}

void Slime::Update(int arrayNum, Player* player, weapon* w, Stage stage)
{
	//画像切り替え用フレームカウントをインクリメント
	imgFrameCounter++;

	//リスポーンしていてHPが０より大きいなら
	if (respawnFlg == true && hp > 0) {

		//画像左右
		imgAngle = CheckImgAngle();

		//画像切り替え
		if (imgFrameCounter >= 1 && imgFrameCounter <= 60) {
			img = imgArray[0];
		}
		else if (imgFrameCounter >= 61 && imgFrameCounter <= 120) {
			img = imgArray[1];
		}

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
			if (cloudOfDustHitFlg == false) {//砂塵当たってない
				vector.x = -vector.x * KNCKBACK;
				location.x += vector.x - diff.x;
				vector.y = -vector.y * KNCKBACK;
				location.y += vector.y - diff.y;
			}
			else if (cloudOfDustHitFlg == true) {//砂塵当たった
				X();
				Y();

				vector.x *= 0.6f;
				vector.y *= 0.6f;

				if (fabsf(vector.x) <= 0.05f) {
					if (vector.x < 0) {
						vector.x = -0.05f;
					}
					else if (vector.x > 0) {
						vector.x = 0.05f;
					}
				}

				if (fabsf(vector.y) <= 0.05f) {
					if (vector.y < 0) {
						vector.y= -0.05f;
					}
					else if (vector.y > 0) {
						vector.y = 0.05f;
					}
				}
				
				location.x += vector.x - diff.x;
				location.y += vector.y - diff.y;

				cloudOfDustHitFlg = false;
			}
			
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

	//画像切り替え用フレームカウント変数が３０になったら０にする
	if (imgFrameCounter >= 120) {
		imgFrameCounter = 0;
	}

	else {
			hitWeaponFlg = false;
	}
	//デバッグ（マクロのDEBUGをコメントアウト又はReleaseにすれば使えなくなります）
//#ifdef DEBUG
//	if (InputCtrl::GetKeyState(KEY_INPUT_D) == PRESS && hp >= 0) {
//		hitWeaponFlg = true;
//		hp -= 9999;
//	}
//	else {
//		hitWeaponFlg = false;
//	}
//#endif // DEBUG
	
}

void Slime::Draw(int arrayNum) const
{
	if (respawnFlg == true) {
		
		if (imgAngle == IMG_L) {//左向き表示
			if (hp <= 0) {//HPが０の時
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaNum);
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_L);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
			else {//通常時
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_L);
			}

			if (redDrawFlg == true) {//武器からダメージを受けた時とHPが０じゃない時、敵を赤色表示
				SetDrawBright(255, 0, 0);
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_L);
				SetDrawBright(255, 255, 255);
			}
		}
		else if (imgAngle == IMG_R) {//右向き表示
			if (hp <= 0) {//HPが０の時
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaNum);
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_R);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
			else {//通常時
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_R);
			}

			if (redDrawFlg == true) {//武器からダメージを受けた時とHPが０じゃない時、敵を赤色表示
				SetDrawBright(255, 0, 0);
				DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE, IMG_R);
				SetDrawBright(255, 255, 255);
			}
		}
	}
}

void Slime::X()
{
	if (hitFlg == HIT) {
		vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;

		vector.x = /*vector.x +*/ caleVector.x;
	}
	else if (hitFlg == NO_COLLISION) {
		vector.x = Normalization_X(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;
	}
}

void Slime::Y()
{
	if (hitFlg == HIT) {
		vector.y = Normalization_Y(PlayerLoad_X(location.x), PlayerLoad_Y(location.y)) * ENEMY_SPEED;

		vector.y = /*vector.y +*/ caleVector.y;


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
