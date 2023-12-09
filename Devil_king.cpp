#include "Devil_king.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"
#define BTN_DEBUG
//#define DEBUG

Devil_king::Devil_king()
{
	img = LoadGraph("resources/images/enemy_tmp_images/ma.png");
	hp = DEVILKING_MAX_HP;
	damage = DEVILKING_ATTAK_DAMAGE;
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;
	//シールド
	shield = MAX_SHIELD;
	shieldFlg = false;

	//-----大きい弾-----//

	//影
	shadowLocation.x = location.x;
	shadowLocation.y = location.y;
}

Devil_king::~Devil_king()
{
	DeleteGraph(img);
}

void Devil_king::Update(Player* player)
{
	//プレイヤーの移動量をdiffにセット
	SetPlayerAmountOfTravel_X(player->Player_MoveX());
	SetPlayerAmountOfTravel_Y(player->Player_MoveY());
	//プレイヤーの座標をdiffLocationにセット
	SetPlayer_Location(player->GetLocation());

	//ビーム
	BeamUpdate();

	//移動処理
	if (skyWalkFlg == true && shieldFlg == false) {//浮遊
		//影
		shadowLocation.x = shadowLocation.x - diff.x;
		shadowLocation.y = shadowLocation.y - diff.y;
		//魔王
		skyWalkCounter++;
		for (int i = 0; i < SECOND_FRAME(0.7); i++) {
			skyWalkVectorY = sinf((skyWalkCounter + i) / 13.0f);
		}
		location.x = location.x - diff.x;
		location.y = (location.y + skyWalkVectorY) - diff.y;
	}
	else if ((skyWalkFlg == false || shadowRadiusChageFlg == true) && shieldFlg == true) {
		location.x = location.x - diff.x;
		location.y = (location.y + vector.y) - diff.y;
		//影
		shadowLocation.x = shadowLocation.x - diff.x;
		shadowLocation.y = shadowLocation.y - diff.y;
	}
	
	//影の半径
	if (shieldFlg == false) {
		if (skyWalkVectorY > 0) {//地面に近づいている
			shadowRadiusX += 0.1;
			shadowRadiusY += 0.1;
		}
		else if (skyWalkVectorY < 0) {//地面から遠ざかっている
			shadowRadiusX -= 0.1;
			shadowRadiusY -= 0.1;
		}
	}

	//大きい弾の生成
	if (shieldFlg == false) {
		if (bigBulletCreateFlg == false) {
			bigBulletCreateCounter++;
		}

		if (bigBulletCreateCounter >= BIG_BULLET_CREATE_TIME) {
			bigBulletCreateFlg = true;
			bigBulletCreateCounter = 0;
		}

	}
	
	//シールド
	if (bigBulletHitFlg == true) {
		shield -= 20;//当たったらシールドを減らす値
		bigBulletHitFlg = false;
	}

	if (shield <= 0) {
		shieldFlg = true;
	}

	//シールドが０になったら地面に降りる
	if (shieldFlg == true) {
		//影の半径(シールド０)
		if (shadowRadiusX >= DARK_SHADOW_RADIUS_X && shadowRadiusY >= DARK_SHADOW_RADIUS_Y) {
			skyWalkFlg = false;
		}
		else {
			shadowRadiusChageFlg = true;
			//影の半径
			shadowRadiusX += 0.5;//1
			shadowRadiusY += 0.2;//0.4

			//ベクトル
			vector.y = 0.4;
		}
	}

	//ダウンタイム
	if (skyWalkFlg == false) {
		//downTimeCounterが設定した値になったらシールドを復活させる
		if (downTimeCounter >= DOWN_TIME) {
			shield = MAX_SHIELD;
			shieldFlg = false;
			downTimeCounter = 0;

			//浮遊
			skyWalkFlg = true;
			//影
			shadowLocation.x = location.x - diff.x;
			shadowLocation.y = location.y - diff.y;
			shadowRadiusX = LIGHT_SHADOW_RADIUS_X;
			shadowRadiusY = LIGHT_SHADOW_RADIUS_Y;
		}
		vector.y = 0;
		shadowRadiusChageFlg = false;
		downTimeCounter++;
	}

	//武器からの攻撃とHPが０以上なら赤く表示する
	if (hitWeaponFlg == true && hp > 0) {
		redDrawFlg = true;
	}
	hitWeaponFlg = false;

	//リスポーンFlg
	if (hp <= 0) {
		respawnFlg = false;
	}

	//赤く表示
	if (redFrameCounter == RED_FRAME) {
		redDrawFlg = false;
		redFrameCounter = 0;
	}
	if (redDrawFlg == true) {
		redFrameCounter++;
	}

#ifdef BTN_DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_D) == PRESS && hp >= 0) {
		if (shieldFlg == true) {
			hitWeaponFlg = true;
			hp -= 100;
		}
		else {
			hitWeaponFlg = true;
			shield -= 999;
		}
		
	}
	else {
		hitWeaponFlg = false;
	}
#endif // BTN_DEBUG
}

void Devil_king::Draw() const
{
	//影の描画
	if (skyWalkFlg == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawOval((int)shadowLocation.x, (int)shadowLocation.y + 70, DARK_SHADOW_RADIUS_X, DARK_SHADOW_RADIUS_Y, C_BLACK, TRUE);//大きい＆薄い影
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawOval((int)shadowLocation.x, (int)shadowLocation.y + 70, shadowRadiusX, shadowRadiusY, C_BLACK, TRUE);//小さい＆濃い影
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);//通常時

	//赤色表示
	if (redDrawFlg == true) {
		SetDrawBright(255, 0, 0);
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
		SetDrawBright(255, 255, 255);
	}

	//ビーム
	BeamDraw();

#ifdef DEBUG
	/*DrawFormatString(location.x, location.y, C_BLUE,      "シールド:%0.2f", shield);
	DrawFormatString(location.x, location.y + 10, C_BLUE, "   Flg  :%d", shieldFlg);*/
	DrawFormatString(location.x, location.y + 10, C_BLUE, "   cnt  :%d", debugCnt);
#endif // DEBUG

}

void Devil_king::BeamUpdate()
{
	boxX_a = location.x - dL.x;
	boxY_a = location.y - dL.y;

	//長さを一定にする
	boxX_d = fabsf(BOX_MAX_LENGTH_D / PlayerLoad(location, false));
	boxX_a *= boxX_d;
	boxY_d = fabsf(BOX_MAX_LENGTH_D / PlayerLoad(location, false));
	boxY_a *= boxY_d;
}

void Devil_king::BeamDraw() const
{
	//薄い赤色の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, BOX_MAX_WIDTH);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//濃い赤色の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawLine(location.x, location.y, location.x - boxX_a, location.y - boxY_a, C_RED, lineSize);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
