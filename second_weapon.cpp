#include "second_weapon.h"
#include "inputCtrl.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "Player.h"


second_weapon::second_weapon()
{
	weaponType = none;
	baseVec = { 80,0,80 };
	relativeRot = 0.0f;		//武器によって変える
	maxRot = 90.0f;
	coolTime = 20;
	isAttacking = false;
	weaponLevel = 0;
	levelUpFlg = false;

	LevelState();

	P_aiming_radiusX = 0.0f;
	P_aiming_radiusY = 0.0f;

	tmp = 0;

	location = { 640.360 };

	spear_img = LoadGraph("resources/images/武器/槍50・50.png");
	frail_img = LoadGraph("resources/images/chain_iron ball.png");
	book_img = LoadGraph("resources/images/tsurugi_bronze_blue.png");
	bullet_img = LoadGraph("resources/images/magic_bullet.png");
	ironball_img = LoadGraph("resources/images/chain_iron ball.png");
	barrier_img = LoadGraph("resources/images/baria_blue.png");
	attackbuf_img = LoadGraph("resources/images/attack_buf.png");
	arrow_img = LoadGraph("resources/images/arrow_red.png");
	crack_img = LoadGraph("resources/images/crack.png");
	thunder_img[0] = LoadGraph("resources/images/Thunder_1.png");
	thunder_img[1] = LoadGraph("resources/images/Thunder_2.png");
	thunder_img[2] = LoadGraph("resources/images/Thunder_3.png");

	spear_move_cnt = 0.0f;
	spear_move = { 0,0,0 };
	thunderRadius = 1000.0f;
	for (int i = 0; i < 64; i++){
		thunder[i].flg = false;
		thunder[i].fps = 0;
	}

	frailRadius = 30.0f;
	frailRate = 1.0f;
	isFrailAttacking = false;
	level7FrailFlg = false;
	level8FrailRadius = 100.0f;
	frailDistance = 0.0f;

	Bullet_speed = 10;

	book_move = { 0,0,0 };
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		bullets[i].v = { 0,0,0 };
		bullets[i].l = { 0,0 };
		bullets[i].flg = false;
	}
	barrierFlg = false;

	totalDamage = 0;

}

second_weapon::second_weapon(int type)
{
	//使うか不明
	weaponType = type;
	switch (weaponType)
	{
	case spear:
		baseVec = { 80,0,80 };
		break;

	case frail:
		baseVec = { 50,0,50 };
		break;

	case book:
		baseVec = { 100,0,100 };
		break;
	}
}

second_weapon::~second_weapon()
{
	DeleteGraph(spear_img);
	DeleteGraph(frail_img);
	DeleteGraph(book_img);
	DeleteGraph(bullet_img);
	DeleteGraph(ironball_img);
	DeleteGraph(barrier_img);
	DeleteGraph(attackbuf_img);
	DeleteGraph(crack_img);
	DeleteGraph(thunder_img[0]);
	DeleteGraph(thunder_img[1]);
	DeleteGraph(thunder_img[2]);
}

void second_weapon::Update(float cursorX, float cursorY, Location playerLocation, Vector playerVec, Player* player)
{
	location = playerLocation;
	playerVector = playerVec;
	//debug
	//x y length　にはプレイヤーとカーソルのベクトルを入れる
	/*float x = InputCtrl::GetMouseCursor().x - 640;
	float y = InputCtrl::GetMouseCursor().y - 360;*/


	float x = cursorX - location.x; //kk
	float y = cursorY - location.y;	//kk
	float length = sqrt((x) * (x)+(y) * (y));

	float innerProduct = ((x)*baseVec.x) + ((y)*baseVec.y);
	if (!isAttacking) {
		weaponAngle = acos(innerProduct / (length * baseVec.length));
		if (y > 0) {
			weaponAngle = (M_PI - weaponAngle);
			weaponAngle += M_PI;
		}
	}


	//武器所有中なら
	if (weaponType != none) {
		//クールタイム中
		if (!(isAttacking) && --coolTime < 0) {
			isAttacking = true;
			coolTime = maxCoolTime;
		}

		//攻撃中
		if (isAttacking) {

			/*if (relativeRot < -maxRot) {
				relativeRot = maxRot;
				isAttacking = false;
			}*/
			rot = -1 * (weaponAngle - (d_r(relativeRot)));

			//回転中の武器の座標
			collisionX = (baseVec.x * cos((rot)) - baseVec.y * sin((rot))) + location.x;	//kk
			collisionY = (baseVec.x * sin((rot)) + baseVec.y * cos((rot))) + location.y;	//kk

			//回転中の武器のベクトル
			collisionVec.x = collisionX - location.x;	//kk
			collisionVec.y = collisionY - location.y;	//kk
			collisionVec.length = sqrt((collisionVec.x) * (collisionVec.x) + (collisionVec.y) * (collisionVec.y));

			//回転
			/*relativeRot -= 4.0f;*/


			//単位ベクトル
			unitVec.x = collisionVec.x / collisionVec.length;
			unitVec.y = collisionVec.y / collisionVec.length;
			unitVec.length = sqrt((unitVec.x) * (unitVec.x) + (unitVec.y) * (unitVec.y));

			switch (weaponType)
			{
			case spear:
				SpearAnim();
				break;

			case frail:
				isAttacking = false;
				isFrailAttacking = true;

				frailLcation = location;

				collisionX = cursorX;
				collisionY = cursorY;

				frailLcationCursor = { cursorX,cursorY };

				level7FrailRot = rot;
				frailDistance = 0.0f;

				if (weaponLevel == 7) {
					level7FrailFlg = true;
				}
				else {
					level7FrailFlg = false;
				}

				break;

			case book:
				isAttacking = false;
				if (weaponLevel != 7) {
					if (weaponLevel == 8) {
						for (int i = 0; i < 6; i++){
							SpawnBookBullets(i);
						}
					}
					else {
						SpawnBookBullets(0);
					}
					
				}
				break;

			default:
				break;
			}
			

		}

		if (weaponType == book) {
			MoveBookBullet();
		}

		if (isFrailAttacking && FrailAnim()) {
			isFrailAttacking = false;
		}
		else if (!isFrailAttacking) {
			frailLcation.x += -1 * playerVector.x;
			frailLcation.y += -1 * playerVector.y;
			if (weaponLevel == 7) {
				frailLocation1.x += -1 * playerVector.x;
				frailLocation1.y += -1 * playerVector.y;
				frailLocation2.x += -1 * playerVector.x;
				frailLocation2.y += -1 * playerVector.y;
			}

			if (weaponLevel == 8) {
				frailRadius = FRAIL_RADIUS_LEVEL8;
			}
			else {
				frailRadius = FRAIL_RADIUS;
			}
		}

		if (weaponType == spear && weaponLevel == 8) {
			SpearThunder();
		}

	}



	//レベルアップデバッグ
	if (levelUpFlg) {
		if (InputCtrl::GetKeyState(KEY_INPUT_K) == PRESS) {
			levelUpFlg = false;
		}

		if (InputCtrl::GetKeyState(KEY_INPUT_0) == PRESS) {
			weaponLevel = 0;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
			weaponLevel = 1;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
			weaponLevel = 2;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
			weaponLevel = 3;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_4) == PRESS) {
			weaponLevel = 4;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_5) == PRESS) {
			weaponLevel = 5;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_6) == PRESS) {
			weaponLevel = 6;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_7) == PRESS) {
			weaponLevel = 7;
			LevelState();

		}else if (InputCtrl::GetKeyState(KEY_INPUT_8) == PRESS) {
			weaponLevel = 8;
			LevelState();

		}

	}
	else if (InputCtrl::GetKeyState(KEY_INPUT_K) == PRESS) {
		levelUpFlg = true;
	}
}

void second_weapon::Draw() const
{
	//武器描画
	if (isAttacking) {
		switch (weaponType)
		{
		case spear:
			DrawRotaGraph2(spearlocation.x, spearlocation.y, 45, 0, 2.5, rot + (M_PI / 4) + d_r(12), spear_img, TRUE);
			break;
		case frail:
			DrawRotaGraph2(location.x, location.y, -50, 550, 0.1, rot + (M_PI / 4), frail_img, TRUE, TRUE);
			break;
		case book:
			DrawRotaGraph2(location.x, location.y, 0, 500, 0.2, rot + (M_PI / 4), book_img, TRUE, TRUE);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < 64; i++){
		if (thunder[i].flg /*&& thunder[i].fps > 0*/) {
			
			if (thunder[i].fps > 10) {
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[2], TRUE, TRUE);
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[1], TRUE, TRUE);
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[0], TRUE, TRUE);
			}
			else if (thunder[i].fps > 5) {
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[1], TRUE, TRUE);
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[0], TRUE, TRUE);
			}
			else {
				DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.15, 0, thunder_img[0], TRUE, TRUE);
			}
			//DrawRotaGraph2(thunder[i].l.x, thunder[i].l.y, 917 / 2, 1001 / 2, 0.1, 0, thunder[i].img[0], TRUE, TRUE);
		}
	}

	//弾
	for (int i = 0; i < MAX_BULLETS_NUM; i++){
		if (bullets[i].flg == true) {
			//DrawCircle(bullets[i].l.x, bullets[i].l.y, 10, 0xffff00, TRUE);
			DrawRotaGraph2(bullets[i].l.x, bullets[i].l.y, 250, 250, 0.05, rot + (M_PI / 4), bullet_img, TRUE, TRUE);
		}
	}

	//フレイル
	if (weaponType == frail) {
		//DrawCircle(frailLcation.x, frailLcation.y, frailRadius, 0x000000, TRUE);
		if (weaponLevel == 8) {
			
			//DrawCircle(frailLcation.x, frailLcation.y, level8FrailRadius, 0x000000, FALSE);
			if (frailRate == 1.0f) {
				DrawRotaGraph2(frailLcation.x, frailLcation.y, 1480 / 2, 1110 / 2, 0.2, rot + (M_PI / 4), crack_img, TRUE, TRUE);
			}
		}
		DrawRotaGraph2(frailLcation.x, frailLcation.y, 550 / 2, 450 / 2, 0.2 * frailRate, rot + (M_PI / 4), frail_img, TRUE, TRUE);
		if (level7FrailFlg) {
			/*DrawCircle(frailLocation1.x, frailLocation1.y, frailRadius, 0x000000, TRUE);
			DrawCircle(frailLocation2.x, frailLocation2.y, frailRadius, 0x000000, TRUE);*/
			DrawRotaGraph2(frailLocation1.x, frailLocation1.y, 550 / 2, 450 / 2, 0.2 * frailRate, rot + (M_PI / 4), frail_img, TRUE, TRUE);
			DrawRotaGraph2(frailLocation2.x, frailLocation2.y, 550 / 2, 450 / 2, 0.2 * frailRate, rot + (M_PI / 4), frail_img, TRUE, TRUE);
		}
		
	}

	if (attackBufRate >= 2.0f) {
		/*DrawRotaGraph2(location.x - 25, location.y - 47, 250, 250, 0.07, 0, attackbuf_img, TRUE, TRUE);
		
		DrawRotaGraph2(location.x + 5, location.y - 47, 250, 250, 0.05, M_PI / 2 + M_PI, arrow_img, TRUE, TRUE);
		DrawRotaGraph2(location.x - 5, location.y - 47, 250, 250, 0.05, M_PI / 2 + M_PI, arrow_img, TRUE, TRUE);*/
	}

	//バリア
	if (weaponType == book && weaponLevel == 7 && barrierFlg) {
		DrawRotaGraph2(location.x, location.y, 1000, 1000, 0.05, 0, barrier_img, TRUE, TRUE);
	}

	
	//spear
	/*DrawCircle(spearlocation.x, spearlocation.y, 3, 0xff0000, TRUE);
	DrawLine(location.x, location.y, spearlocation.x, spearlocation.y, 0xffffff);*/

	//debug
	int x = InputCtrl::GetMouseCursor().x;
	int y = InputCtrl::GetMouseCursor().y;

	/*DrawFormatString(0, 0, 0xffffff, "武器タイプ %d 1,片手剣 2,短剣 3,大剣 100,なし", weaponType+1);*/
	/*DrawFormatString(0, 30, 0xffffff, "武器レベル %d", weaponLevel);
	DrawFormatString(0, 60, 0xffffff, "クールタイム　%d", maxCoolTime);
	DrawFormatString(0, 90, 0xffffff, "クールタイムカウント　%d", coolTime);
	DrawFormatString(0, 120, 0xffffff, "fraillength %f", frailLength);
	DrawFormatString(0, 150, 0xffffff, "fraillengthCursor %f", frailLengthCursor);*/
	//DrawFormatString(0, 180, 0xffffff, "totaldamage 2 %d", totalDamage);
	/*DrawFormatString(0, 210, 0xffffff, "フレイルY %d", thunder[1].fps);
	DrawFormatString(0, 240, 0xffffff, " %f", attackBufRate);*/
	

	if (isAttacking) {
		/*DrawCircle(collisionX, collisionY, 3, 0xff0000, TRUE);
		DrawLine(location.x, location.y, collisionX, collisionY, 0xffffff);*/
	}

	/*DrawCircle(collisionX, collisionY, 3, 0xff0000, TRUE);
	
	DrawLine(location.x, location.y, collisionX, collisionY, 0xffffff);*/

	//DrawCircle(640, 360, 3, 0xff0000, TRUE);
	/*if (tmp == 0) {
		DrawCircle(680, 310, 10, 0xff0000, TRUE);
	}*/

	/*if (levelUpFlg) {
		DrawFormatString(450, 60, 0xffffff, "武器をレベルアップします。レベルを入力してください.(0~8)");
		DrawFormatString(450, 90, 0xffffff, "武器レベル :: %d     Kキーで閉じる",weaponLevel);
	}
	else {
		DrawFormatString(450, 90, 0xffffff, "Kキーでレベルアップメニューを開く(武器２)");
	}*/

}

void second_weapon::SetWeaponType(int type)
{
	weaponType = type;
	LevelState();
}

void second_weapon::LevelUpDebug(int num)
{
	weaponLevel = num;
	switch (weaponLevel)
	{
	case 0:


		break;
	case 1:


		break;
	case 2:


		break;
	case 3:


		break;
	case 4:


		break;
	case 5:


		break;
	case 6:


		break;
	case 7:


		break;
		/*case 8:
			weaponLevel++;*/

		break;
	default:
		break;
	}

}

void second_weapon::LevelState()
{
	attackBufRate = 1.0f;
	InitWeapon(0);

	switch (weaponLevel)
	{
	case 0:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL;
			damage = INIT_DAMAGE_FRAIL;
			frailRadius = 30.0f;//初期値
			P_aiming_radiusX = 200.0f;//初期値
			P_aiming_radiusY = 200.0f;//初期値
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 1:
		switch (weaponType)
		{
		case spear:
			//ダメージとクールタイムのみ クールタイムだけ上昇
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.8f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			//クールタイムを少し上昇
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.8f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			//ダメージとクールタイムと弾の発射速度のみ クールタイムだけ上昇
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.9f;
			damage = INIT_DAMAGE_BOOK;
			Bullet_speed;
			break;
		}

		break;
	case 2:
		switch (weaponType)
		{
		case spear:
			//クールタイムのみ　ダメージは微量
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.6f;
			damage = INIT_DAMAGE_SPEAR + 2;
			break;

		case frail:
			//フレイル　クールタイムを上げる 鉄球の半径を上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.6f;
			damage = INIT_DAMAGE_FRAIL + 3;
			frailRadius = 40.0f;
			P_aiming_radiusX = 200.0f;//初期値
			P_aiming_radiusY = 200.0f;//初期値
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			//魔導書　クールタイムを上げる　ダメージは微量
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.6f;
			damage = INIT_DAMAGE_BOOK + 2;
			break;
		}

		break;
	case 3:
		switch (weaponType)
		{
		case spear:
			//ダメージのみ　クールタイムは微量
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.8f;
			damage = INIT_DAMAGE_SPEAR + 5;
			break;

		case frail:
			//フレイル　攻撃範囲(照準)をでかくする　ダメージを上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.8f;
			damage = INIT_DAMAGE_FRAIL + 5;
			frailRadius = 30.0f;//初期値
			P_aiming_radiusX = 250.0f;
			P_aiming_radiusY = 250.0f;
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			//魔導書　ダメージを上げる　弾のスピードを上げる
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.8f;
			damage = INIT_DAMAGE_BOOK;
			Bullet_speed = 15.0f;
			break;
		}

		break;
	case 4:
		switch (weaponType)
		{
		case spear:
			//クールタイムのみ　ダメージは微量
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.4f;
			damage = INIT_DAMAGE_SPEAR + 5;
			break;

		case frail:
			//フレイル　クールタイムを上げる 鉄球の半径を上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.5f;
			damage = INIT_DAMAGE_FRAIL + 5;
			frailRadius = 100.0f;
			P_aiming_radiusX = 200.0f;//初期値
			P_aiming_radiusY = 200.0f;//初期値
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.5f;
			damage = INIT_DAMAGE_BOOK + 5;
			Bullet_speed = 15;
			break;
		}

		break;
	case 5:
		switch (weaponType)
		{
		case spear:
			//ダメージのみ　クールタイムは微量
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.7f;
			damage = INIT_DAMAGE_SPEAR + 10;
			break;

		case frail:
			//フレイル　攻撃範囲(照準)をでかくする　ダメージを上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.7f;
			damage = INIT_DAMAGE_FRAIL + 10;
			frailRadius = 30.0f;//初期値
			P_aiming_radiusX = 300.0f;
			P_aiming_radiusY = 300.0f;
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.7f;
			damage = INIT_DAMAGE_BOOK + 10;
			Bullet_speed = 30.0f;
			break;
		}

		break;
	case 6:
		switch (weaponType)
		{
			//今までに強化してきたものを全て追加する
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.4f;
			damage = INIT_DAMAGE_SPEAR + 10;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.5f;
			damage = INIT_DAMAGE_FRAIL + 10;
			frailRadius = 100.0f;
			P_aiming_radiusX = 300.0f;
			P_aiming_radiusY = 300.0f;
			Player::SetPlayer_RadiusX(P_aiming_radiusX);
			Player::SetPlayer_RadiusY(P_aiming_radiusY);
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.5f;
			damage = INIT_DAMAGE_BOOK + 10;
			Bullet_speed = 30.0f;
			break;
		}

		break;
	case 7:
		switch (weaponType)
		{
		case spear://ロイヤルランス
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.4f;
			damage = INIT_DAMAGE_SPEAR;
			attackBufRate = 2.0f;
			break;

		case frail://三つ首
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.4f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book://賢者の加護
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK_LEVEL7;
			damage = INIT_DAMAGE_BOOK;
			attackBufRate = 2.0f;
			break;
		}

		break;
	case 8:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.3f;
			damage = INIT_DAMAGE_SPEAR;
			thunderDamage = 100.0f;
			break;

		case frail://アースクラッシャー
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.4f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book://エンチャントバレット
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 1.5f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	default:
		break;
	}
	coolTime = maxCoolTime;
}

bool second_weapon::WeaponCollision(Location enemyLocation, float radius)
{
	Location weaponCollisionLocation;
	float tmp_x, tmp_y, tmp_length;
	float spearlen;
	if (isAttacking) {
		switch (weaponType)
		{
		case spear:
			spearlen = sqrtf((spearlocation.x - location.x) * (spearlocation.x - location.x) + (spearlocation.y - location.y) * (spearlocation.y - location.y));
			for (int i = 0; i < (spearlen / 10) + 1; i++) {
				weaponCollisionLocation.x = location.x + unitVec.x * (i * 10);		//プレイヤー座標＋単位ベクトル＊半径
				weaponCollisionLocation.y = location.y + unitVec.y * (i * 10);			

				tmp_x = weaponCollisionLocation.x - enemyLocation.x;
				tmp_y = weaponCollisionLocation.y - enemyLocation.y;
				tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

				if (tmp_length < radius + 10) {
					return true;
				}
			}
			break;
		case frail:
			/*weaponCollisionLocation.x = frailLcation.x;
			weaponCollisionLocation.y = frailLcation.y;

			tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (tmp_length < radius + frailRadius) {
				return true;
			}*/
			break;
		case book:
			//下に記載
		default:
			break;
		}
		
	}

	//フレイル
	if (isFrailAttacking && frailRate <= 1.0f) {
		if (weaponLevel == 7) {		//level7の判定
			for (int i = 0; i < 3; i++)
			{
				switch (i)
				{
				case 0:
					weaponCollisionLocation.x = frailLcation.x;
					weaponCollisionLocation.y = frailLcation.y;

					tmp_x = weaponCollisionLocation.x - enemyLocation.x;
					tmp_y = weaponCollisionLocation.y - enemyLocation.y;
					tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

					if (tmp_length < radius + frailRadius) {
						return true;
					}
					break;
				case 1:
					weaponCollisionLocation.x = frailLocation1.x;
					weaponCollisionLocation.y = frailLocation1.y;

					tmp_x = weaponCollisionLocation.x - enemyLocation.x;
					tmp_y = weaponCollisionLocation.y - enemyLocation.y;
					tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

					if (tmp_length < radius + frailRadius) {
						return true;
					}
					break;
				case 2:
					weaponCollisionLocation.x = frailLocation2.x;
					weaponCollisionLocation.y = frailLocation2.y;

					tmp_x = weaponCollisionLocation.x - enemyLocation.x;
					tmp_y = weaponCollisionLocation.y - enemyLocation.y;
					tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

					if (tmp_length < radius + frailRadius) {
						return true;
					}
					break;
				default:
					break;
				}
			}
		}
		else {		//通常とlevel8の判定
			weaponCollisionLocation.x = frailLcation.x;
			weaponCollisionLocation.y = frailLcation.y;

			tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (weaponLevel == 8) {
				if (tmp_length < radius + frailRadius + level8FrailRadius) {
					return true;
				}
			}
			else {
				if (tmp_length < radius + frailRadius) {
					return true;
				}
			}
		}
	}

	//弾
	for (int i = 0; i < MAX_BULLETS_NUM; i++) {
		if (bullets[i].flg) {
			weaponCollisionLocation = bullets[i].l;

			tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (tmp_length < radius + 10) {
				return true;
			}
		}
	}
	

	return false;
}

bool second_weapon::SpearAnim()
{
	if (++spear_move_cnt > SPEAR_MAX_MOVE) {
		isAttacking = false;
		spear_move = { 0,0,0 };
		spear_move_cnt = 0;
		return true;
	}

	spearlocation = location;

	spear_move.x += unitVec.x * 7;
	spear_move.y += unitVec.y * 7;

	spearlocation.x += spear_move.x;
	spearlocation.y += spear_move.y;

	return false;
}

bool second_weapon::SpearThunder()
{
	for (int i = 0; i < 64; i++){
		if (thunder[i].flg) {

			thunder[i].l.x -= playerVector.x;
			thunder[i].l.y -= playerVector.y;

			if (thunder[i].fps++ > 120) {
				thunder[i].fps = 0;
				thunder[i].flg = false;
			}
		}
	}
	return false;
}

bool second_weapon::SpearThunderCollision(Location enemyLocation, float radius)
{
	Location weaponCollisionLocation;
	float tmp_x, tmp_y, tmp_length;

	for (int i = 0; i < 64; i++){
		if (thunder[i].flg && thunder[i].fps > 0) {

			weaponCollisionLocation.x = thunder[i].l.x;
			weaponCollisionLocation.y = thunder[i].l.y;

			tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (tmp_length < radius + thunderRadius) { 
				return true;
			}

		}
	}
	
	return false;
}

void second_weapon::SpawnBookBullets(int num)
{
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		if (!bullets[i].flg) {
			bullets[i].flg = true;
			bullets[i].v = unitVec;
			bullets[i].l = location;
			bullets[i].rot = 60 * num;
			bullets[i].relativeRot = 0;
			bullets[i].distance = 5 * num;
			break;
		}
	}
}

void second_weapon::MoveBookBullet()
{
	int cnt = 0;

	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		if (bullets[i].flg) {
			if (weaponLevel == 8) {
				bullets[i].rot += 4.0f;
				if (bullets[i].rot > 360.0f) {
					bullets[i].rot = bullets[i].rot - 360.0f;
				}
				bullets[i].distance += 1.0f;
				bullets[i].l.x = bullets[i].distance * cos(d_r(bullets[i].rot)) - 0 * sin(d_r(bullets[i].rot)) + location.x + playerVector.x * -1;
				bullets[i].l.y = bullets[i].distance * sin(d_r(bullets[i].rot)) + 0 * cos(d_r(bullets[i].rot)) + location.y + playerVector.y * -1;

			}
			else {
				bullets[i].l.x += bullets[i].v.x * Bullet_speed + playerVector.x * -1;
				bullets[i].l.y += bullets[i].v.y * Bullet_speed + playerVector.y * -1;
			}

			if (bullets[i].distance > 300) {
				bullets[i].flg = false;
			}

			if (bullets[i].l.x < 0 || bullets[i].l.x > 1280 ||
				bullets[i].l.y < 0 || bullets[i].l.y > 720) {
				bullets[i].flg = false;
			}
		}
	}
}

bool second_weapon::FrailAnim()
{
	if (weaponLevel == 7) {
		ThreeFrailAnim();
	}

	frailVec.x = unitVec.x * 10;
	frailVec.y = unitVec.y * 10;
	frailVec.length = sqrtf(frailVec.x * frailVec.x + frailVec.y * frailVec.y);

	frailLcation.x += frailVec.x + playerVector.x * -1;
	frailLcation.y += frailVec.y + playerVector.y * -1;
	frailLength = sqrtf((frailLcation.x - location.x) * (frailLcation.x - location.x) + (frailLcation.y - location.y) * (frailLcation.y - location.y));
	frailLengthCursor = sqrtf((frailLcationCursor.x - location.x) * (frailLcationCursor.x - location.x) + (frailLcationCursor.y - location.y) * (frailLcationCursor.y - location.y));

	if ((int)frailLength  < (int)frailLengthCursor / 2) {
		frailRate += 0.1f;
	}
	else if ((int)frailLength > (int)frailLengthCursor / 2) {
		frailRate -= 0.1f;
	}

	if (weaponLevel == 8) {
		frailRadius = FRAIL_RADIUS_LEVEL8 * (1.0f * frailRate);
	}
	else {
		frailRadius = FRAIL_RADIUS * (1.0f * frailRate);
	}


	if ((int)frailLength > (int)frailLengthCursor) {
		frailRate = 1.0f;
		return true;
	}

	return false;
}

bool second_weapon::ThreeFrailAnim()
{
	/*swordSlash[i].collsion1.x = baseVec.x * cos(d_r(90.0f) + slashRot) - baseVec.y * sin(d_r(90.0f) + slashRot) + swordSlash[i].l.x;
	swordSlash[i].collsion1.y = baseVec.x * sin(d_r(90.0f) + slashRot) + baseVec.y * cos(d_r(90.0f) + slashRot) + swordSlash[i].l.y;

	swordSlash[i].collsion2.x = baseVec.x * cos(d_r(270.0f) + slashRot) - baseVec.y * sin(d_r(270.0f) + slashRot) + swordSlash[i].l.x;
	swordSlash[i].collsion2.y = baseVec.x * sin(d_r(270.0f) + slashRot) + baseVec.y * cos(d_r(270.0f) + slashRot) + swordSlash[i].l.y;*/

	frailDistance += 7.0f;

	frailLocation1.x = frailDistance * cos(d_r(120.0f) + level7FrailRot) - 0 * sin(d_r(90.0f) + level7FrailRot) + frailLcation.x;
	frailLocation1.y = frailDistance * sin(d_r(120.0f) + level7FrailRot) + 0 * cos(d_r(90.0f) + level7FrailRot) + frailLcation.y;

	frailLocation2.x = frailDistance * cos(d_r(240.0f) + level7FrailRot) - 0 * sin(d_r(270.0f) + level7FrailRot) + frailLcation.x;
	frailLocation2.y = frailDistance * sin(d_r(240.0f) + level7FrailRot) + 0 * cos(d_r(270.0f) + level7FrailRot) + frailLcation.y;

	return false;
}

void second_weapon::InitWeapon(int type)
{
	relativeRot = 0.0f;		//武器によって変える
	isAttacking = false;
	levelUpFlg = false;

	if (type == 1) {
		LevelState();
	}

	spear_move_cnt = 0.0f;
	spear_move = { 0,0,0 };
	for (int i = 0; i < 64; i++){
		thunder[i].flg = false;
	}

	frailLcation = { -1000,-1000 };
	frailRadius = 30.0f;
	frailRate = 1.0f;
	isFrailAttacking = false;
	level7FrailFlg = false;
	level8FrailRadius = 100.0f;
	frailDistance = 0.0f;


	book_move = { 0,0,0 };
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		bullets[i].v = { 0,0,0 };
		bullets[i].l = { 0,0 };
		bullets[i].flg = false;
	}

	barrierFlg = false;
}

void second_weapon::AddTotalDamage()
{
	totalDamage += damage;
}

void second_weapon::AddTotalDamageThunder()
{
	totalDamage += thunderDamage;
}
