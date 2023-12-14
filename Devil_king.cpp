#include "Devil_king.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"
#define BTN_DEBUG
#define DEBUG

Devil_king::Devil_king()
{
	img = LoadGraph("resources/images/enemy_images/devilking/devilking_syoumen.png");
	hp = DEVILKING_MAX_HP;
	damage = DEVILKING_ATTAK_DAMAGE;
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 60;
	vector.x = 0;
	vector.y = 0;

	//シールド
	shield = MAX_SHIELD;
	shieldFlg = false;

	//影
	shadowLocation.x = location.x;
	shadowLocation.y = location.y;

	//・・・・・・ビーム・・・・・・//
	beamPosition = BEAM_POSITION_CROSS;
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

	//移動処理
	if (skyWalkFlg == true && shieldFlg == false) {//浮遊
		//瞬間移動
		Teleportation();
		//影
		shadowLocation.x = shadowLocation.x - (vector.x + diff.x);
		shadowLocation.y = shadowLocation.y - (vector.y + diff.y);
		//魔王(浮遊処理)
		skyWalkCounter++;
		for (int i = 0; i < SECOND_FRAME(0.7); i++) {
			skyWalkVectorY = sinf((skyWalkCounter + i) / 13.0f);
		}
		location.x = location.x - (vector.x + diff.x);
		location.y = (location.y + skyWalkVectorY) - (vector.y + diff.y);
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

	//ビーム
	if (shieldFlg == false /*&& DEVILKING_MAX_HP / 3 >= hp*/) {//シールドがある時と魔王のHPが3/1を下回ったら
		BeamUpdate();
		BeamCollision();
	}
	else if (shieldFlg == true) {//シールドが無い時
		beamPossibleCounter = 0;
		beamPossibleFlg = false;
		lineSize = 0;
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
	if (shieldFlg == false && beamPossibleFlg == true) {
		BeamDraw();
	}

#ifdef DEBUG
	


	DrawFormatString(500, 600, C_RED, "%.2f", diff.x);
	DrawFormatString(500, 620, C_RED, "%.2f", diff.y);
	DrawFormatString(500, 660, C_RED, "%.2f", location.x);
	DrawFormatString(500, 680, C_RED, "%.2f", location.y);
	DrawFormatString(570, 660, C_RED, "%.2f", vector.x);
	DrawFormatString(570, 680, C_RED, "%.2f", vector.y);
#endif // DEBUG

}

void Devil_king::Teleportation()
{
	//瞬間移動する条件
	//プレイヤーとの当たり判定
	float a = location.x - dL.x;
	float b = location.y - dL.y;
	float c = sqrtf(pow(a, 2) + pow(b, 2));
	if (c <= TELEPORTATION_RADIUS + PLAYER_RADIUS) {//当たった
		teleportationFlg = true;//瞬間移動する
	}
	else {
		teleportationFlg = false;//しない
	}

	//瞬間移動する処理
	if (teleportationFlg == true) {
		/*float tmp = location.x;
		location.x = location.y;
		location.y = tmp;
		shadowLocation.x = location.x;
		shadowLocation.y = location.y;*/
	}
}

void Devil_king::BeamUpdate()
{
	if (beamPossibleFlg == true) {
		if (lineSize < BEAM_MAX_WIDTH) {
			lineSize++;
		}
		else if (lineSize >= BEAM_MAX_WIDTH) {
			beamPossibleCounter = 0;
			beamPossibleFlg = false;
			lineSize = 0;

			if (beamPosition == BEAM_POSITION_CROSS) {
				beamPosition = BEAM_POSITION_DIAGONAL;
			}
			else if (beamPosition == BEAM_POSITION_DIAGONAL) {
				beamPosition = BEAM_POSITION_CROSS;
			}
		}

		switch (beamPosition)
		{
		case BEAM_POSITION_CROSS://十字
			//右
			beamLocation[RIGHT].x = location.x + DEVILKING_BEAM_SPACE;
			beamLocation[RIGHT].y = location.y;
			//左
			beamLocation[LEFT].x = location.x - DEVILKING_BEAM_SPACE;
			beamLocation[LEFT].y = location.y;
			//下
			beamLocation[LOWER].x = location.x;
			beamLocation[LOWER].y = location.y + DEVILKING_BEAM_SPACE;
			//上
			beamLocation[UPPER].x = location.x;
			beamLocation[UPPER].y = location.y - DEVILKING_BEAM_SPACE;

			break;
		case BEAM_POSITION_DIAGONAL://斜め
			//右上
			beamLocation[UPPER_RIGHT].x = location.x + DEVILKING_BEAM_SPACE;
			beamLocation[UPPER_RIGHT].y = location.y - DEVILKING_BEAM_SPACE;
			//左上
			beamLocation[UPPER_LEFT].x = location.x - DEVILKING_BEAM_SPACE;
			beamLocation[UPPER_LEFT].y = location.y - DEVILKING_BEAM_SPACE;
			//右下
			beamLocation[LOWER_RIGHT].x = location.x + DEVILKING_BEAM_SPACE;
			beamLocation[LOWER_RIGHT].y = location.y + DEVILKING_BEAM_SPACE;
			//左下
			beamLocation[LOWER_LEFT].x = location.x - DEVILKING_BEAM_SPACE;
			beamLocation[LOWER_LEFT].y = location.y + DEVILKING_BEAM_SPACE;

			break;
		default:
			break;
		}
	}
	else if (beamPossibleFlg == false) {
		beamPossibleCounter++;
		if (beamPossibleCounter >= BEAM_CAN_TIEM) {
			beamPossibleFlg = true;
		}
	}
	
}

void Devil_king::BeamDraw() const
{
	switch (beamPosition)
	{
	case BEAM_POSITION_CROSS:
		//右
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[RIGHT].x, beamLocation[RIGHT].y, beamLocation[RIGHT].x + BEAM_SIZE, beamLocation[RIGHT].y, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[RIGHT].x, beamLocation[RIGHT].y, beamLocation[RIGHT].x + BEAM_SIZE, beamLocation[RIGHT].y, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//左
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LEFT].x, beamLocation[LEFT].y, beamLocation[LEFT].x - BEAM_SIZE, beamLocation[LEFT].y, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LEFT].x, beamLocation[1].y, beamLocation[LEFT].x - BEAM_SIZE, beamLocation[LEFT].y, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//下
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER].x, beamLocation[LOWER].y, beamLocation[2].x, beamLocation[LOWER].y + BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER].x, beamLocation[LOWER].y, beamLocation[LOWER].x, beamLocation[LOWER].y + BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//上
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER].x, beamLocation[UPPER].y, beamLocation[UPPER].x, beamLocation[UPPER].y - BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER].x, beamLocation[UPPER].y, beamLocation[UPPER].x, beamLocation[UPPER].y - BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		break;
	case BEAM_POSITION_DIAGONAL:
		//右上
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER_RIGHT].x, beamLocation[UPPER_RIGHT].y, beamLocation[UPPER_RIGHT].x + BEAM_SIZE, beamLocation[UPPER_RIGHT].y - BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER_RIGHT].x, beamLocation[UPPER_RIGHT].y, beamLocation[UPPER_RIGHT].x + BEAM_SIZE, beamLocation[UPPER_RIGHT].y - BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//左上
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER_LEFT].x, beamLocation[UPPER_LEFT].y, beamLocation[UPPER_LEFT].x - BEAM_SIZE, beamLocation[UPPER_LEFT].y - BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER_LEFT].x, beamLocation[UPPER_LEFT].y, beamLocation[UPPER_LEFT].x - BEAM_SIZE, beamLocation[UPPER_LEFT].y - BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//右下
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER_RIGHT].x, beamLocation[LOWER_RIGHT].y, beamLocation[LOWER_RIGHT].x + BEAM_SIZE, beamLocation[LOWER_RIGHT].y + BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER_RIGHT].x, beamLocation[LOWER_RIGHT].y, beamLocation[LOWER_RIGHT].x + BEAM_SIZE, beamLocation[LOWER_RIGHT].y + BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//左下
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER_LEFT].x, beamLocation[LOWER_LEFT].y, beamLocation[LOWER_LEFT].x - BEAM_SIZE, beamLocation[LOWER_LEFT].y + BEAM_SIZE, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER_LEFT].x, beamLocation[LOWER_LEFT].y, beamLocation[LOWER_LEFT].x - BEAM_SIZE, beamLocation[LOWER_LEFT].y + BEAM_SIZE, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		break;
	default:
		break;
	}
}

void Devil_king::BeamCollision()
{
	switch (beamPosition)
	{
	case BEAM_POSITION_CROSS://十字
		//右
		
		//左

		//下

		//上

		break;
	case BEAM_POSITION_DIAGONAL://斜め

		break;
	default:

		break;
	}
}

Location Devil_king::BeamCenterCoordinatesCale(Location b_Location, int arrayNum)
{
	//関数内で使う変数の宣言
	Location r;//結果を格納
	Location upperLeft;//ビームの左上
	Location lowerRight;//ビームの右下

	//ビームの左上右下を計算
	switch (beamPosition)
	{
	case BEAM_POSITION_CROSS://十字
		switch (arrayNum)
		{
		case RIGHT://右
			upperLeft.x = b_Location.x;
			upperLeft.y = b_Location.y + (BEAM_MAX_WIDTH / 2);
			lowerRight.x = b_Location.x + BEAM_SIZE;
			lowerRight.y = b_Location.y - (BEAM_MAX_WIDTH / 2);
			break;
		case LEFT://左
			upperLeft.x = b_Location.x;
			upperLeft.y = b_Location.y + (BEAM_MAX_WIDTH / 2);
			lowerRight.x = b_Location.x - BEAM_SIZE;
			lowerRight.y = b_Location.y - (BEAM_MAX_WIDTH / 2);
			break;
		case LOWER://下
			upperLeft.x = b_Location.x + (BEAM_MAX_WIDTH / 2);
			upperLeft.y = b_Location.y;
			lowerRight.x = b_Location.x - (BEAM_MAX_WIDTH / 2);
			lowerRight.y = b_Location.y + BEAM_SIZE;
			break;
		case UPPER://上
			upperLeft.x = b_Location.x + (BEAM_MAX_WIDTH / 2);
			upperLeft.y = b_Location.y;
			lowerRight.x = b_Location.x - (BEAM_MAX_WIDTH / 2);
			lowerRight.y = b_Location.y - BEAM_SIZE;
			break;
		default:
			break;
		}
		break;
	case BEAM_POSITION_DIAGONAL://斜め
		switch (arrayNum)
		{
		case UPPER_RIGHT://右上
			break;
		case UPPER_LEFT:
			break;
		case LOWER_RIGHT:
			break;
		case LOWER_LEFT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	//矩形の中心座標計算
	r.x = (upperLeft.x + lowerRight.x) / 2;
	r.y = (upperLeft.y + lowerRight.y) / 2;

	return r;
}
