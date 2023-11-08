#include "second_weapon.h"
#include "inputCtrl.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>


second_weapon::second_weapon()
{
	weaponType = spear;
	baseVec = { 80,0,80 };
	relativeRot = 0.0f;		//武器によって変える
	maxRot = 90.0f;
	coolTime = 20;
	isAttacking = false;
	weaponLevel = 0;
	levelUpFlg = false;

	LevelState();

	tmp = 0;

	location = { 640.360 };

	spear_img = LoadGraph("resources/images/spear.png");
	frail_img = LoadGraph("resources/images/sword_shortsword_brown.png");
	book_img = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	spear_move_cnt = 0.0f;
	spear_move = { 0,0,0 };

	frailRadius = 30.0f;
	frailRate = 1.0f;
	isFrailAttacking = false;

	book_move = { 0,0,0 };
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		bullets[i].v = { 0,0,0 };
		bullets[i].l = { 0,0 };
		bullets[i].flg = false;
	}
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
}

void second_weapon::Update(float cursorX, float cursorY, Location playerLocation, Vector playerVec)
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
		if (!(isAttacking) && --coolTime <= 0) {
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
				/*if (++spear_move_cnt > SPEAR_MAX_MOVE) {
					isAttacking = false;
					spear_move = { 0,0,0 };
					spear_move_cnt = 0;
					
				}
				spear_move.x += unitVec.x * 3;
				spear_move.y += unitVec.y * 3;

				collisionX += spear_move.x;
				collisionY += spear_move.y;*/

				SpearAnim();
				break;

			case frail:
				isAttacking = false;
				isFrailAttacking = true;

				frailLcation = location;

				collisionX = cursorX;
				collisionY = cursorY;

				frailLcationCursor = { cursorX,cursorY };
				
				break;

			case book:
				isAttacking = false;
				SpawnBookBullets();

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
			frailRadius = 30;
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
	//武器描画	//kk
	if (isAttacking) {
		switch (weaponType)
		{
		case spear:
			DrawRotaGraph2(spearlocation.x, spearlocation.y, 475, 40, 0.25, rot + (M_PI / 4), spear_img, TRUE);
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

	for (int i = 0; i < MAX_BULLETS_NUM; i++){
		if (bullets[i].flg == true) {
			DrawCircle(bullets[i].l.x, bullets[i].l.y, 10, 0xffff00, TRUE);
		}
	}
	if (weaponType == frail) {
		DrawCircle(frailLcation.x, frailLcation.y, frailRadius, 0x000000, TRUE);
	}

	//spear
	/*DrawCircle(spearlocation.x, spearlocation.y, 3, 0xff0000, TRUE);
	DrawLine(location.x, location.y, spearlocation.x, spearlocation.y, 0xffffff);*/

	//debug
	int x = InputCtrl::GetMouseCursor().x;
	int y = InputCtrl::GetMouseCursor().y;

	/*DrawFormatString(0, 0, 0xffffff, "武器タイプ %d 1,片手剣 2,短剣 3,大剣 100,なし", weaponType+1);
	DrawFormatString(0, 30, 0xffffff, "武器レベル %d", weaponLevel);
	DrawFormatString(0, 60, 0xffffff, "クールタイム　%d", maxCoolTime);
	DrawFormatString(0, 90, 0xffffff, "クールタイムカウント　%d", coolTime);
	DrawFormatString(0, 120, 0xffffff, "fraillength %f", frailLength);
	DrawFormatString(0, 150, 0xffffff, "fraillengthCursor %f", frailLengthCursor);*/
	//DrawFormatString(0, 180, 0xffffff, "単位ベクトルX %f", unitVec.x);
	//DrawFormatString(0, 210, 0xffffff, "単位ベクトルY %f", unitVec.y);
	DrawFormatString(0, 240, 0xffffff, "rate % f", frailRate);


	//kk
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

	if (levelUpFlg) {
		DrawFormatString(450, 60, 0xffffff, "武器をレベルアップします。レベルを入力してください.(0~8)");
		DrawFormatString(450, 90, 0xffffff, "武器レベル :: %d     Lキーで閉じる",weaponLevel);
	}
	else {
		DrawFormatString(450, 90, 0xffffff, "Kキーでレベルアップメニューを開く(武器２)");
	}



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
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.9f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.9f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.9f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 2:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.8f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.8f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.8f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 3:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.7f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.7f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.7f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 4:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.7f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.7f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.7f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 5:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.6f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.6f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.6f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 6:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.5f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.5f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.5f;
			damage = INIT_DAMAGE_BOOK;
			break;
		}

		break;
	case 7:
		switch (weaponType)
		{
		case spear:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SPEAR;
			maxCoolTime = INIT_COOLTIME_SPEAR * 0.4f;
			damage = INIT_DAMAGE_SPEAR;
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.4f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.4f;
			damage = INIT_DAMAGE_BOOK;
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
			break;

		case frail:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_FRAIL;
			maxCoolTime = INIT_COOLTIME_FRAIL * 0.1f;
			damage = INIT_DAMAGE_FRAIL;
			break;

		case book:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_BOOK;
			maxCoolTime = INIT_COOLTIME_BOOK * 0.3f;
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
				weaponCollisionLocation.x = location.x + unitVec.x * (i * 10);		//プレイヤー座標＋単位ベクトル＊半径	//kk
				weaponCollisionLocation.y = location.y + unitVec.y * (i * 10);			//kk

				tmp_x = weaponCollisionLocation.x - enemyLocation.x;
				tmp_y = weaponCollisionLocation.y - enemyLocation.y;
				tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

				if (tmp_length < radius + 10) {
					return true;
				}
			}
			break;
		case frail:
			weaponCollisionLocation.x = frailLcation.x;
			weaponCollisionLocation.y = frailLcation.y;

			tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (tmp_length < radius + frailRadius) {
				return true;
			}
			break;
		case book:
			//下に記載
		default:
			break;
		}
		
	}

	if (isFrailAttacking && frailRate <= 1.0f) {
		weaponCollisionLocation.x = frailLcation.x;
		weaponCollisionLocation.y = frailLcation.y;

		tmp_x = weaponCollisionLocation.x - enemyLocation.x;
		tmp_y = weaponCollisionLocation.y - enemyLocation.y;
		tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

		if (tmp_length < radius + frailRadius) {
			return true;
		}
	}

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

	}

	spearlocation = location;

	spear_move.x += unitVec.x * 5;
	spear_move.y += unitVec.y * 5;

	spearlocation.x += spear_move.x;
	spearlocation.y += spear_move.y;

	return false;
}

void second_weapon::SpawnBookBullets()
{
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		if (!bullets[i].flg) {
			bullets[i].flg = true;
			bullets[i].v = unitVec;
			bullets[i].l = location;
			break;
		}
	}
}

void second_weapon::MoveBookBullet()
{
	for (int i = 0; i < MAX_BULLETS_NUM; i++)
	{
		if (bullets[i].flg) {
			bullets[i].l.x += bullets[i].v.x * 10 + playerVector.x * -1;
			bullets[i].l.y += bullets[i].v.y * 10 + playerVector.y * -1;

			if (bullets[i].l.x < 0 || bullets[i].l.x > 1280 ||
				bullets[i].l.y < 0 || bullets[i].l.y > 720) {
				bullets[i].flg = false;
			}
		}
	}
}

bool second_weapon::FrailAnim()
{

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

	frailRadius = 30 * (1.0f * frailRate);


	if ((int)frailLength > (int)frailLengthCursor) {
		frailRate = 1.0f;
		return true;
	}

	return false;
}
