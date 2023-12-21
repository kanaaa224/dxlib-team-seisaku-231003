//#include "Devil_king.h"
//#include "Common.h"
//#include <math.h>
//#include "inputCtrl.h"
#include"main.h"
//#define BTN_DEBUG
//#define DEBUG

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
	beamPosition = 0;
	//画像読込
	beamChargeImg = LoadGraph("resources/images/enemy_images/devilKing/Weapon/Beam_Cannon_1.png");
	beamShootImg = LoadGraph("resources/images/enemy_images/devilKing/Weapon/Beam_Cannon_0.png");
}

Devil_king::~Devil_king()
{
	DeleteGraph(img);
	DeleteGraph(beamChargeImg);
	DeleteGraph(beamShootImg);
}

void Devil_king::Update(Player* player)
{
	if (InitFlg == false) {
		beamPosition = 0;
		InitFlg = true;
	}

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
	if (shieldFlg == false && DEVILKING_MAX_HP / 3 >= hp) {//シールドがある時と魔王のHPが3/1を下回ったら
		BeamUpdate(player);
		downTime = SECOND_FRAME(1.7);
	}
	else if (shieldFlg == true) {//シールドが無い時
		SoundManager::StopSoundSE("se_enemy_beam_charge");
		SoundManager::StopSoundSE("se_enemy_beam_fire");
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
		if (skyWalkFlg && !shieldFlg)
		{
			SoundManager::PlaySoundSE("se_enemy_barrier_close");
		}
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
		if (downTimeCounter >= downTime) {
			SoundManager::PlaySoundSE("se_enemy_barrier_open");
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
	DrawFormatString(500, 600, C_RED, "%d", beamPosition);
#endif // DEBUG

}

//魔王の移動処理（テレポート）
void Devil_king::Teleportation()
{
	//瞬間移動する条件
	//プレイヤーとの距離判定
	float a = location.x - dL.x;
	float b = location.y - dL.y;
	float c = sqrtf(pow(a, 2) + pow(b, 2));
	if (c <= TELEPORTATION_RADIUS_N + PLAYER_RADIUS) {//設定した範囲内
		teleportationFlg = true;//瞬間移動する
		//SoundManager::PlaySoundSE("se_enemy_teleportation");
	}
	else {
		teleportationFlg = false;//しない
	}

	//瞬間移動する処理
	if (teleportationFlg == true) {
		location.x = SetGetRand(100, 1180);
		location.y = SetGetRand(100, 620);
		shadowLocation.x = location.x - diff.x;
		shadowLocation.y = (location.y + vector.y) - diff.y;
	}
}

//ビームのアップデート
void Devil_king::BeamUpdate(Player* player)
{
	if (beamPossibleFlg == true) {
		if (lineSize < BEAM_MAX_WIDTH) {//濃い攻撃予測がまだ薄い攻撃予測と同じ太さじゃないなら
			SoundManager::PlaySoundSE("se_enemy_beam_charge");
			lineSize += 1;//濃い攻撃予測の広がる速度
			beamDrawFlg = false;//ビームの描画用Flgをfalse
		}
		else if (lineSize >= BEAM_MAX_WIDTH) {//濃い攻撃予測がまだ薄い攻撃予測と同じ太さなら
			if (nowBeamFlg == true) {//ビーム発射前
				beamPossibleCounter = 0;
				beamPossibleFlg = false;
				lineSize = 0;
				beamShootFinFlg = true;
				nowBeamFlg = false;

				if (beamPosition == BEAM_POSITION_CROSS) {
					beamPosition = BEAM_POSITION_DIAGONAL;
				}
				else if (beamPosition == BEAM_POSITION_DIAGONAL) {
					beamPosition = BEAM_POSITION_CROSS;
				}
			}
			else if (nowBeamFlg == false) {//ビーム発射中
				SoundManager::PlaySoundSE("se_enemy_beam_fire");
				nowBeamCounter++;
				//ビームの当たり判定
				BeamCollision(player);
				if (NOW_BEAM_TIME <= nowBeamCounter) {//ビームの照射時間を過ぎたら
					nowBeamFlg = true;
					nowBeamCounter = 0;
				}
			}
			beamDrawFlg = true;
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

//ビームの描画
void Devil_king::BeamDraw() const
{
	switch (beamPosition)
	{
	case BEAM_POSITION_CROSS:
		//右
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[RIGHT].x, beamLocation[RIGHT].y, beamLocation[RIGHT].x + BEAM_SIZE_C, beamLocation[RIGHT].y, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[RIGHT].x, beamLocation[RIGHT].y, beamLocation[RIGHT].x + BEAM_SIZE_C, beamLocation[RIGHT].y, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {//発射前の画像描画
			DrawRotaGraph2(beamLocation[RIGHT].x, beamLocation[RIGHT].y + 110, 0, 200,1.0f, 0, beamChargeImg, TRUE);
		}
		if (beamDrawFlg == true) {//発射後の画像描画
			DrawRotaGraph2(beamLocation[RIGHT].x, beamLocation[RIGHT].y + 110, 0, 200, 1.0f, 0, beamShootImg, TRUE);
		}

		//左
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LEFT].x, beamLocation[LEFT].y, beamLocation[LEFT].x - BEAM_SIZE_C, beamLocation[LEFT].y, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LEFT].x, beamLocation[1].y, beamLocation[LEFT].x - BEAM_SIZE_C, beamLocation[LEFT].y, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[LEFT].x, beamLocation[LEFT].y - 110, 0, 200,1.0f, 3.1f, beamChargeImg, TRUE);
		}
		if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[LEFT].x, beamLocation[LEFT].y - 110, 0, 200, 1.0f, 3.141f, beamShootImg, TRUE);
		}

		//下
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER].x, beamLocation[LOWER].y, beamLocation[2].x, beamLocation[LOWER].y + BEAM_SIZE_C, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER].x, beamLocation[LOWER].y, beamLocation[LOWER].x, beamLocation[LOWER].y + BEAM_SIZE_C, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[LOWER].x - 110, beamLocation[LOWER].y, 0, 200,1.0f, 1.55f, beamChargeImg, TRUE);
		}
		if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[LOWER].x - 110, beamLocation[LOWER].y, 0, 200, 1.0f, 1.57f, beamShootImg, TRUE);
		}

		//上
		//薄い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER].x, beamLocation[UPPER].y, beamLocation[UPPER].x, beamLocation[UPPER].y - BEAM_SIZE_C, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER].x, beamLocation[UPPER].y, beamLocation[UPPER].x, beamLocation[UPPER].y - BEAM_SIZE_C, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[UPPER].x + 110, beamLocation[UPPER].y, 0, 200,1.0f, -1.55f, beamChargeImg, TRUE);
		}
		if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[UPPER].x + 110, beamLocation[UPPER].y, 0, 200, 1.0f, -1.57f, beamShootImg, TRUE);
		}

		break;
	case BEAM_POSITION_DIAGONAL:
		//右上
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER_RIGHT].x, beamLocation[UPPER_RIGHT].y, beamLocation[UPPER_RIGHT].x + BEAM_SIZE_D, beamLocation[UPPER_RIGHT].y - BEAM_SIZE_D, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER_RIGHT].x, beamLocation[UPPER_RIGHT].y, beamLocation[UPPER_RIGHT].x + BEAM_SIZE_D, beamLocation[UPPER_RIGHT].y - BEAM_SIZE_D, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[UPPER_RIGHT].x + 75, beamLocation[UPPER_RIGHT].y + 76, 0, 200, 1.0f, -0.78f, beamChargeImg, TRUE);
		}
		else if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[UPPER_RIGHT].x + 75, beamLocation[UPPER_RIGHT].y + 76, 0, 200, 1.0f, -0.78f, beamShootImg, TRUE);
		}

		//左上
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[UPPER_LEFT].x, beamLocation[UPPER_LEFT].y, beamLocation[UPPER_LEFT].x - BEAM_SIZE_D, beamLocation[UPPER_LEFT].y - BEAM_SIZE_D, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[UPPER_LEFT].x, beamLocation[UPPER_LEFT].y, beamLocation[UPPER_LEFT].x - BEAM_SIZE_D, beamLocation[UPPER_LEFT].y - BEAM_SIZE_D, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[UPPER_LEFT].x + 75, beamLocation[UPPER_LEFT].y - 76, 0, 200, 1.0f, -2.35f, beamChargeImg, TRUE);
		}
		else if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[UPPER_LEFT].x + 75, beamLocation[UPPER_LEFT].y - 76, 0, 200, 1.0f, -2.35f, beamShootImg, TRUE);
		}

		//右下
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER_RIGHT].x, beamLocation[LOWER_RIGHT].y, beamLocation[LOWER_RIGHT].x + BEAM_SIZE_D, beamLocation[LOWER_RIGHT].y + BEAM_SIZE_D, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER_RIGHT].x, beamLocation[LOWER_RIGHT].y, beamLocation[LOWER_RIGHT].x + BEAM_SIZE_D, beamLocation[LOWER_RIGHT].y + BEAM_SIZE_D, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[LOWER_RIGHT].x - 75, beamLocation[LOWER_RIGHT].y + 70, 0, 200, 1.0f, 0.79f, beamChargeImg, TRUE);
		}
		else if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[LOWER_RIGHT].x - 75, beamLocation[LOWER_RIGHT].y + 70, 0, 200, 1.0f, 0.79f, beamShootImg, TRUE);
		}

		//左下
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		DrawLine(beamLocation[LOWER_LEFT].x, beamLocation[LOWER_LEFT].y, beamLocation[LOWER_LEFT].x - BEAM_SIZE_D, beamLocation[LOWER_LEFT].y + BEAM_SIZE_D, C_RED, BEAM_MAX_WIDTH);
		//濃い赤色の矩形
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawLine(beamLocation[LOWER_LEFT].x, beamLocation[LOWER_LEFT].y, beamLocation[LOWER_LEFT].x - BEAM_SIZE_D, beamLocation[LOWER_LEFT].y + BEAM_SIZE_D, C_RED, lineSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (beamDrawFlg == false) {
			DrawRotaGraph2(beamLocation[LOWER_LEFT].x - 73, beamLocation[LOWER_LEFT].y - 75, 0, 200, 1.0f, 2.36f, beamChargeImg, TRUE);
		}
		else if (beamDrawFlg == true) {
			DrawRotaGraph2(beamLocation[LOWER_LEFT].x - 73, beamLocation[LOWER_LEFT].y - 75, 0, 200, 1.0f, 2.36f, beamShootImg, TRUE);
		}

		break;
	default:
		break;
	}
}

//・・・・・・・ビームの当たり判定・・・・・・・//
void Devil_king::BeamCollision(Player* player)
{
	switch (beamPosition)
	{
	case BEAM_POSITION_CROSS://十字
		//右
		BeamCollisionRight(player);
		//左
		BeamCollisionLeft(player);
		//下
		BeamCollisionLower(player);
		//上
		BeamCollisionUpper(player);
		beamShootFinFlg = false;
		break;
	case BEAM_POSITION_DIAGONAL://斜め
		//右上
		BeamCollisionUpperRight(player);
		//左上
		BeamCollisionUpperLeft(player);
		//右下
		BeamCollisionLowerRight(player);
		//左下
		BeamCollisionLowerLeft(player);
		beamShootFinFlg = false;
		break;
	default:

		break;
	}
}

//・・・・・・・・・・十字・・・・・・・・・・//
//右
void Devil_king::BeamCollisionRight(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_C; i++) {

		float a = (beamLocation[RIGHT].x + (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = beamLocation[RIGHT].y - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[0] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[0] = false;
		}
	}
}
//左
void Devil_king::BeamCollisionLeft(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_C; i++) {

		float a = (beamLocation[LEFT].x - (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = beamLocation[LEFT].y - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[1] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[1] = false;
		}
	}
}
//下
void Devil_king::BeamCollisionLower(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_C; i++) {

		float a = beamLocation[LOWER].x - dL.x;
		float b = (beamLocation[LOWER].y + (BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[2] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[2] = false;
		}
	}
}
//上
void Devil_king::BeamCollisionUpper(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_C; i++) {

		float a = beamLocation[LOWER].x - dL.x;
		float b = (beamLocation[LOWER].y -(BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[3] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[3] = false;
		}
	}
}

//・・・・・・・・・・斜め・・・・・・・・・・//
//右上
void Devil_king::BeamCollisionUpperRight(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_D; i++) {

		float a = (beamLocation[UPPER_RIGHT].x + (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = (beamLocation[UPPER_RIGHT].y - (BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[4] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[4] = false;
		}
	}
}
//左上!!(当たり判定がずれている)!!
void Devil_king::BeamCollisionUpperLeft(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_D; i++) {

		float a = (beamLocation[UPPER_LEFT].x - (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = (beamLocation[UPPER_LEFT].y - (BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[5] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[5] = false;
		}
	}
}
//右下!!(当たり判定がずれている)!!
void Devil_king::BeamCollisionLowerRight(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_D; i++) {

		float a = (beamLocation[LOWER_RIGHT].x + (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = (beamLocation[LOWER_RIGHT].y + (BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[6] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[6] = false;
		}
	}
}
//左下
void Devil_king::BeamCollisionLowerLeft(Player* player)
{
	for (int i = 1; i <= BEAM_COLLISION_CIRCLE_NUM_D; i++) {

		float a = (beamLocation[LOWER_LEFT].x - (BEAM_MAX_WIDTH / 2) * i) - dL.x;
		float b = (beamLocation[LOWER_LEFT].y + (BEAM_MAX_WIDTH / 2) * i) - dL.y;
		float c = sqrtf(pow(a, 2) + pow(b, 2));

		if (c <= (BEAM_MAX_WIDTH / 2) + PLAYER_RADIUS) {
			hitBeamPlayer[7] = true;
			player->SetPlayer_HP(BEAM_DAMAGE);
		}
		else {
			hitBeamPlayer[7] = false;
		}
	}
}
