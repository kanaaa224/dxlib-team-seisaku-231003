#include "weapon.h"
#include "inputCtrl.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "Player.h"
//#include "SphereCollider.h"





weapon::weapon()
{
	weaponType = none;
	baseVec = { 80,0,80 };
	relativeRot = 90.0f;		//武器によって変える
	maxRot = 90.0f;
	coolTime = 20;
	isAttacking = false;
	oldIsAttacking = false;
	weaponLevel = 0;
	levelUpFlg = false;
	
	P_speed = 0.0;
	P_cooltime = 0;
	P_limit = 0.0;

	tmp = 0;

	location = { 640.360 };

	sword_img = LoadGraph("resources/images/sword_longsword_brown.png");
	dagger_img = LoadGraph("resources/images/sword_shortsword_brown.png");
	greatsword_img = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	rotSpeed = 4.0f;
	for (int i = 0; i < 10; i++)
	{
		swordSlash[i] = { {0,0},{0,0,0},false };
	}
	hitCnt = 0;
	fpsCnt = 0;
	heelAmount = 10;
	for (int i = 0; i < 10; i++)
	{
		throwDagger[i] = { {0,0},{0,0,0},false };
	}
	slash_img = LoadGraph("resources/images/nc284514.png");
	slashFlg = false;

	avoidanceDamageFlg = false;
}

weapon::weapon(int type)
{
	//使うか不明
	weaponType = type;
	switch (weaponType)
	{
	case sword:
		baseVec = { 80,0,80 };
		break;

	case dagger:
		baseVec = { 50,0,50 };
		break;

	case greatSword:
		baseVec = { 100,0,100 };
		break;
	}
}

weapon::~weapon()
{
}

void weapon::Update(float cursorX, float cursorY, Location playerLocation, Player* player)
{
	location = playerLocation;
	playerVector = { player->Player_MoveX(),player->Player_MoveY() };
	oldIsAttacking = isAttacking;
	//debug
	//x y length　にはプレイヤーとカーソルのベクトルを入れる
	/*float x = InputCtrl::GetMouseCursor().x - 640;
	float y = InputCtrl::GetMouseCursor().y - 360;*/

	float x = cursorX - location.x; //kk
	float y = cursorY - location.y;	//kk
	float length = sqrt((x) * (x) + (y) * (y));


	float innerProduct = ((x) * baseVec.x) + ((y) * baseVec.y);
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

			if (weaponLevel == 7 && weaponType == greatSword) {
				if (relativeRot < 0) {
					relativeRot = maxRot;
					isAttacking = false;
					slashFlg = false;
				}
			}
			else {
				if (relativeRot < -maxRot) {
					relativeRot = maxRot;
					isAttacking = false;
					slashFlg = false;
				}
			}
			rot = -1 * (weaponAngle - (d_r(relativeRot)));

			//回転中の武器の座標
			collisionX = (baseVec.x * cos((rot)) - baseVec.y * sin((rot))) + location.x;	//kk
			collisionY = (baseVec.x * sin((rot)) + baseVec.y * cos((rot))) + location.y;	//kk

			//回転中の武器のベクトル
			collisionVec.x = collisionX - location.x;	//kk
			collisionVec.y = collisionY - location.y;	//kk
			collisionVec.length = sqrt((collisionVec.x) * (collisionVec.x) + (collisionVec.y) * (collisionVec.y));

			//回転
			relativeRot -= rotSpeed;


			//単位ベクトル
			unitVec.x = collisionVec.x / collisionVec.length;
			unitVec.y = collisionVec.y / collisionVec.length;
			unitVec.length = sqrt((unitVec.x) * (unitVec.x) + (unitVec.y) * (unitVec.y));
			

			//(仮)斬撃
			if (weaponType == sword && weaponLevel == 7) {
				if (relativeRot < 0 && !slashFlg) {
					SpawnSwordSlash();
					slashFlg = true;
					slashRot = rot;
				}
			}
			//(仮)投げナイフ
			if (weaponType == dagger && weaponLevel == 8) {
				if (relativeRot < 0 && !slashFlg) {
					for (int i = 0; i < 5; i++) {
						SpawnThrowDagger(i);
					}
					slashFlg = true;
					slashRot = rot;
				}
			}
		
		}

		//回避中にダメージ
		if (weaponType == dagger && weaponLevel == 7) {
			if (player->GetPlayer_Avoidance()) {
				avoidanceDamageFlg = true;
			}
			else {
				avoidanceDamageFlg = false;
			}
		}




		SwordSlashAnim();
		ThrowDaggerAnim();
	}

	SwordLevel8(player);

	//レベルアップデバッグ
	if (levelUpFlg) {
		if (InputCtrl::GetKeyState(KEY_INPUT_L) == PRESS) {
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
	else if (InputCtrl::GetKeyState(KEY_INPUT_L) == PRESS) {
		levelUpFlg = true;
	}
}

void weapon::Draw() const
{
	//武器描画	
	if (isAttacking) {
		switch (weaponType)
		{
		case sword:
			DrawRotaGraph2(location.x, location.y, 0, 500, 0.16, rot + (M_PI / 4), sword_img, TRUE, TRUE);
			break;
		case dagger:
			DrawRotaGraph2(location.x, location.y, -50, 550, 0.1, rot + (M_PI / 4), dagger_img, TRUE, TRUE);
			break;
		case greatSword:
			DrawRotaGraph2(location.x, location.y, 0, 500, 0.2, rot + (M_PI / 4), greatsword_img, TRUE, TRUE);
			break;
		default:
			break;
		}
	}
	//斬撃
	for (int i = 0; i < 10; i++){
		if (swordSlash[i].flg) {
			/*DrawCircle(swordSlash[i].collsion1.x, swordSlash[i].collsion1.y, 10, 0xff0000, TRUE);
			DrawCircle(swordSlash[i].collsion2.x, swordSlash[i].collsion2.y, 10, 0xff0000, TRUE);*/
			DrawRotaGraph2(swordSlash[i].l.x, swordSlash[i].l.y, 256, 256, 0.3, slashRot - (M_PI / 4), slash_img, TRUE);
		}
	}
	//投げナイフ
	for (int i = 0; i < MAX_THROW_DAGGER; i++){
		if (throwDagger[i].flg) {
			DrawRotaGraph2(throwDagger[i].l.x, throwDagger[i].l.y, -50, 550, 0.1, throwDagger[i].rot + d_r(throwDagger[i].relativeRot) +(M_PI / 4), dagger_img, TRUE, TRUE);
		}
	}

	//回避中のダメージ
	if (avoidanceDamageFlg) {
		int randx = rand() % 200 - 100;
		int randy = rand() % 200 - 100;
		int randrot = rand() % 360;
		DrawRotaGraph2(location.x + randx /*+ (playerVector.x * -10)*/, location.y + randy /*+ (playerVector.y * -10)*/, 256, 256, 0.3, d_r(randrot), slash_img, TRUE);
		DrawCircle(location.x, location.y, AVOIDANCE_DAMAGE_RADIUS, 0xff0000, FALSE);
	}

	//debug
	int x = InputCtrl::GetMouseCursor().x;
	int y = InputCtrl::GetMouseCursor().y;

	//DrawFormatString(0, 0, 0xffffff, "武器タイプ %d 1,片手剣 2,短剣 3,大剣 100,なし", weaponType + 1);
	//DrawFormatString(0, 30, 0xffffff, "武器レベル %d", weaponLevel);
	/*DrawFormatString(0, 120, 0xffffff, "クールタイム　%d", maxCoolTime);
	DrawFormatString(0, 90, 0xffffff, "クールタイムカウント　%d", coolTime);*/
	DrawFormatString(0, 140, 0xffffff, "攻撃範囲 %f", maxRot);
	DrawFormatString(0, 160, 0xffffff, "ダメージ %d", damage);
	DrawFormatString(0, 180, 0xffffff, "単位ベクトルX %f", sl[0].x);
	DrawFormatString(0, 210, 0xffffff, "単位ベクトルY %f", sl[0].y);
	DrawFormatString(0, 240, 0xffffff, "rennzoku %d",hitCnt );




	//kk
	if (isAttacking) {
		/*DrawCircle(collisionX, collisionY, 3, 0xff0000, TRUE);
		DrawLine(location.x, location.y, collisionX, collisionY, 0xffffff);*/
	}
	

	//DrawCircle(640, 360, 3, 0xff0000, TRUE);
	/*if (tmp == 0) {
		DrawCircle(680, 310, 10, 0xff0000, TRUE);
	}*/

	if (levelUpFlg) {
		DrawFormatString(450, 60, 0xffffff, "武器をレベルアップします。レベルを入力してください.(0~8)");
		DrawFormatString(450, 90, 0xffffff, "武器レベル :: %d     Lキーで閉じる",weaponLevel);
	}
	else {
		DrawFormatString(450, 60, 0xffffff, "Lキーでレベルアップメニューを開く(武器１)");
	}


	
}

void weapon::SetWeaponType(int type)
{
	weaponType = type;
	LevelState();
	/*switch (weaponType)
	{
	case sword:
		baseVec = { 80,0,80 };
		maxRot = 60.0f;
		break;

	case dagger:
		baseVec = { 50,0,50 };
		maxRot = 60.0f;
		break;

	case greatSword:
		baseVec = { 100,0,100 };
		maxRot = 90.0f;
		break;
	}*/
}

void weapon::LevelUpDebug(int num)
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

void weapon::LevelState()
{
	switch (weaponLevel)
	{
	case 0:
		switch (weaponType)
		{
		case sword:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_SWORD; //片手剣は、大剣　短剣の強化内容を全て取り入れる
			damage = INIT_DAMAGE_SWORD;
			break;

		case dagger:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER; //プレイヤーの移動速度、回避の速度等を上げれるようにする
			damage = INIT_DAMAGE_DAGGER;
			break;

		case greatSword:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_GREATSWORD; //クールダウンは一撃が重い分　激重にしたい
			damage = INIT_DAMAGE_GREATSWORD;
			break;
		}

		break;
	case 1://少しだけ全てのステータスを上げる
		switch (weaponType)
		{
		case sword:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_SWORD * 0.8f; // クールタイムを微量ながら上げる
			damage = INIT_DAMAGE_SWORD;
			break;

		case dagger:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.9f; //短剣は弱すぎるため最初は敵を４回で倒せるようにする
			damage = INIT_DAMAGE_DAGGER + 1;
			
			break;

		case greatSword:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 5.0f; // 60 + 10 = 70度
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.8f;
			damage = INIT_DAMAGE_GREATSWORD + 25; // 序盤のステージは一回で敵を倒したい
			break;
		}

		break;
	case 2:
		switch (weaponType)
		{
		case sword:
			//片手剣　攻撃範囲を上げる　移動速度を上げる
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD + 5.0f; // 60 + 20 = 80
			maxCoolTime = INIT_COOLTIME_SWORD * 0.7f;
			damage = INIT_DAMAGE_SWORD;
			P_speed = Player::Player_Speed(2.1);
			break;

		case dagger:
			//短剣　ダメージを上げる　移動速度を上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.8f;
			damage = INIT_DAMAGE_DAGGER + 2;
			P_speed = Player::Player_Speed(2.5);
			break;

		case greatSword:
			//大剣　ダメージを多く上げる
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 5.0f; // 60 + 10 = 70度
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.8f;
			damage = INIT_DAMAGE_GREATSWORD + 10; // 35
			break;
		}

		break;
	case 3:
		switch (weaponType)
		{
		case sword:
			//片手剣　回避のスピードを上げる　ダメージを上げる
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_SWORD * 0.7f;
			damage = INIT_DAMAGE_SWORD + 1;
			P_limit = Player::Player_Upperlimit(2.0f);
			break;

		case dagger:
			//短剣　ダメージよりも振る速度を上げる　回避の速度を上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.7f;
			damage = INIT_DAMAGE_DAGGER + 1;
			P_limit = Player::Player_Upperlimit(2.5f);
			break;

		case greatSword:
			//大剣　攻撃範囲を上げる
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 10.0f; // 60 + 20 = 80度
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.8f;
			damage = INIT_DAMAGE_GREATSWORD + 5; // 30
			break;
		}

		break;
	case 4:
		switch (weaponType)
		{
		case sword:
			//片手剣　攻撃範囲を上げる　移動速度を上げる
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD + 15; // 60 + 30 = 90 
			maxCoolTime = INIT_COOLTIME_SWORD * 0.7f;
			damage = INIT_DAMAGE_SWORD;
			P_speed = Player::Player_Speed(2.5f);
			break;

		case dagger:
			//短剣　ダメージを上げる　移動速度を上げる
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.7f;
			damage = INIT_DAMAGE_DAGGER;
			P_speed = Player::Player_Speed(3.0f);
			break;

		case greatSword:
			//大剣　ダメージを多く上げる
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 10.0f; // 60 + 20 = 80
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.8f;
			damage = INIT_DAMAGE_GREATSWORD + 25; // 45
			break;
		}

		break;
	case 5:
		switch (weaponType)
		{
		case sword:
			//片手剣　回避のスピードを上げる　ダメージを上げる
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD + 5; // 60 + 10 = 70
			maxCoolTime = INIT_COOLTIME_SWORD * 0.7f;
			damage = INIT_DAMAGE_SWORD + 1;
			P_limit = Player::Player_Upperlimit(2.3f);
			P_cooltime = Player::Avoidance_limit(0);
			break;

		case dagger:
			//短剣　ダメージよりも振る速度を上げる　回避のクールタイムを短くする
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.5f;
			damage = INIT_DAMAGE_DAGGER;
			P_cooltime = Player::Avoidance_limit(0);
			break;

		case greatSword:
			//大剣　攻撃範囲を上げる
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 20.0f; // 60 + 40 = 100
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.8f;
			damage = INIT_DAMAGE_GREATSWORD + 10; // 35
			break;
		}

		break;
	case 6:
		switch (weaponType)
		{
		case sword:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD + 10; // 60 + 20 = 90
			maxCoolTime = INIT_COOLTIME_SWORD * 0.6f;
			damage = INIT_DAMAGE_SWORD + 2;
			P_limit = Player::Player_Upperlimit(2.1f);
			P_cooltime = Player::Avoidance_limit(1);
			P_speed = Player::Player_Speed(2.2f);
			break;

		case dagger:
			baseVec = { 70,0,70 };
			// 内容は、4 5 の時よりかは低いが最終強化するとあほみたいに強くなる
			maxRot = INIT_ROTATION_DAGGER + 5.0f; // 60 + 10 = 70
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.5f;
			damage = INIT_DAMAGE_DAGGER + 3;
			P_cooltime = Player::Avoidance_limit(1);
			P_speed = Player::Player_Speed(3.0);
			break;

		case greatSword:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD + 30.0f; // 60 + 60 = 120度
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.7f;
			damage = INIT_DAMAGE_GREATSWORD + 20; // 45
			break;
		}

		break;
	case 7:		//最終強化１
		switch (weaponType)
		{
		case sword:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_SWORD * 0.4f;
			damage = INIT_DAMAGE_SWORD;
			break;

		case dagger:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.4f;
			damage = INIT_DAMAGE_DAGGER * 1000;
			P_cooltime = Player::Avoidance_limit(0);
			break;

		case greatSword: //回転攻撃
			baseVec = { 120,0,120 };
			maxRot = 360.0f;
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.4f;
			damage = INIT_DAMAGE_GREATSWORD;
			rotSpeed = 8.0f;
			break;
		}

		break;
	case 8:
		switch (weaponType)
		{
		case sword:
			baseVec = { 100,0,100 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_SWORD * 0.3f;
			damage = INIT_DAMAGE_SWORD;
			break;

		case dagger:
			baseVec = { 70,0,70 };
			maxRot = INIT_ROTATION_DAGGER;
			maxCoolTime = INIT_COOLTIME_DAGGER * 0.4f;
			damage = INIT_DAMAGE_DAGGER;
			break;

		case greatSword:
			baseVec = { 120,0,120 };
			maxRot = INIT_ROTATION_SWORD;
			maxCoolTime = INIT_COOLTIME_GREATSWORD * 0.3f;
			damage = INIT_DAMAGE_GREATSWORD;
			break;
		}

		break;
	default:
		break;
	}
	coolTime = maxCoolTime;
}

bool weapon::WeaponCollision(Location enemyLocation, float radius)
{
	Location weaponCollisionLocation = { 0,0 };

	if (isAttacking) {

		for (int i = 0; i < (baseVec.length / 10) + 1; i++) {
			weaponCollisionLocation.x = location.x + unitVec.x * (i * 10);		//プレイヤー座標＋単位ベクトル＊半径	//kk
			weaponCollisionLocation.y = location.y + unitVec.y * (i * 10);			//kk

			float tmp_x = weaponCollisionLocation.x - enemyLocation.x;
			float tmp_y = weaponCollisionLocation.y - enemyLocation.y;
			float tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

			if (tmp_length < radius + 10) {
				return true;
			}
		}
	}

	
	//飛ぶ斬撃
	if (weaponLevel == 7 && weaponType == sword) {
		for (int i = 0; i < 10; i++) {
			if (swordSlash[i].flg) {
				float tmpx = swordSlash[i].collsion1.x - swordSlash[i].collsion2.x;
				float tmpy = swordSlash[i].collsion1.y - swordSlash[i].collsion2.y;
				float slashLength = sqrtf(tmpx * tmpx + tmpy * tmpy);
				Vector uv = { tmpx / slashLength ,tmpy / slashLength };
				uv.length = sqrtf(uv.x * uv.x + uv.y * uv.y);

				for (int j = 0; j < (slashLength / 10) + 1; j++) {
					weaponCollisionLocation.x = swordSlash[i].collsion2.x + (uv.x * (i * 10));
					weaponCollisionLocation.y = swordSlash[i].collsion2.y + (uv.y * (i * 10));

					float tmp_x2 = weaponCollisionLocation.x - enemyLocation.x;
					float tmp_y2 = weaponCollisionLocation.y - enemyLocation.y;
					float tmp_length2 = sqrt(tmp_x2 * tmp_x2 + tmp_y2 * tmp_y2);

					if (tmp_length2 < radius + 100) {
						return true;
					}
				}

			}
		}
	}
	
	//投げナイフ
	if (weaponLevel == 8 && weaponType == dagger) {
		for (int i = 0; i < MAX_THROW_DAGGER; i++){
			if (throwDagger[i].flg) {
				for (int i = 0; i < (baseVec.length / 10) + 1; i++) {
					weaponCollisionLocation.x = throwDagger[i].l.x + throwDagger[i].unit.x * (i * 10);		//プレイヤー座標＋単位ベクトル＊半径	//kk
					weaponCollisionLocation.y = throwDagger[i].l.y + throwDagger[i].unit.y * (i * 10);			//kk

					float tmp_x = weaponCollisionLocation.x - enemyLocation.x;
					float tmp_y = weaponCollisionLocation.y - enemyLocation.y;
					float tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

					if (tmp_length < radius + 30) {
						return true;
					}
				}
			}
		}
	}

	//回避中のダメージ
	if (weaponLevel == 7 && weaponType == dagger && avoidanceDamageFlg) {
		float tmp_x = location.x - enemyLocation.x;
		float tmp_y = location.y - enemyLocation.y;
		float tmp_length = sqrt(tmp_x * tmp_x + tmp_y * tmp_y);

		if (tmp_length < radius + AVOIDANCE_DAMAGE_RADIUS) {
			return true;
		}
	}
	return false;
}

bool weapon::SpawnSwordSlash()
{
	for (int i = 0; i < 10; i++) {
		if (!swordSlash[i].flg) {
			swordSlash[i].flg = true;
			swordSlash[i].v.x = unitVec.x * 10;
			swordSlash[i].v.y = unitVec.y * 10;
			swordSlash[i].l.x = collisionX;
			swordSlash[i].l.y = collisionY;
			return true;
		}
	}


	return false;
}

void weapon::SwordSlashAnim()
{
	for (int i = 0; i < 10; i++){
		if (swordSlash[i].flg) {
			swordSlash[i].l.x += swordSlash[i].v.x;
			swordSlash[i].l.y += swordSlash[i].v.y;
		}

		if (swordSlash[i].l.x < 0 || swordSlash[i].l.x > 1280 ||
			swordSlash[i].l.y < 0 || swordSlash[i].l.y > 720) {
			swordSlash[i].flg = false;
		}

		for (int i = 0; i < 10; i++) {
			if (swordSlash[i].flg) {
				swordSlash[i].collsion1.x = baseVec.x * cos(d_r(90.0f) + slashRot) - baseVec.y * sin(d_r(90.0f) + slashRot) + swordSlash[i].l.x;
				swordSlash[i].collsion1.y = baseVec.x * sin(d_r(90.0f) + slashRot) + baseVec.y * cos(d_r(90.0f) + slashRot) + swordSlash[i].l.y;

				swordSlash[i].collsion2.x = baseVec.x * cos(d_r(270.0f) + slashRot) - baseVec.y * sin(d_r(270.0f) + slashRot) + swordSlash[i].l.x;
				swordSlash[i].collsion2.y = baseVec.x * sin(d_r(270.0f) + slashRot) + baseVec.y * cos(d_r(270.0f) + slashRot) + swordSlash[i].l.y;
			}
		}
	}

	
}

void weapon::SwordLevel8(Player* player)
{
	if (weaponType == sword && weaponLevel == 8) {

		if (isAttacking && !oldIsAttacking) {
			if (player->GetPlayer_HP() > MAX_HP / 2) {
				player->SetPlayer_HP(MAX_HP / 100);//ダメージを受ける

				damage = INIT_DAMAGE_SWORD * 2;
			}
		}

		if (damage == INIT_DAMAGE_SWORD * 2) {
			fpsCnt++;
			if (fpsCnt > 120) {
				damage = INIT_COOLTIME_SWORD;
				fpsCnt = 0;
			}
		}
	}
}

void weapon::SwordLevel8Heel(Player* player)
{
	if (weaponType == sword && weaponLevel == 8) {
		if (hitCnt > 15) {
			heelAmount = 5;
			player->SetPlayer_HP(-heelAmount);
		}
		else if (hitCnt > 12) {
			heelAmount = 4;
			player->SetPlayer_HP(-heelAmount);
		}
		else if (hitCnt > 9) {
			heelAmount = 3;
			player->SetPlayer_HP(-heelAmount);
		}
		else if (hitCnt > 6) {
			heelAmount = 2;
			player->SetPlayer_HP(-heelAmount);
		}
		else if (hitCnt > 3) {
			heelAmount = 1;
			player->SetPlayer_HP(-0.1);
		}
	}
}

bool weapon::SpawnThrowDagger(int num)
{
	for (int i = 0; i < MAX_THROW_DAGGER; i++) {
		if (!throwDagger[i].flg) {
			throwDagger[i].flg = true;
			throwDagger[i].relativeRot = (num * 20) - 40;
			throwDagger[i].rot = rot;
			throwDagger[i].v.x = 8 * cos(d_r(throwDagger[i].relativeRot) + rot);
			throwDagger[i].v.y = 8 * sin(d_r(throwDagger[i].relativeRot) + rot);
			throwDagger[i].v.length = sqrtf(throwDagger[i].v.x * throwDagger[i].v.x + throwDagger[i].v.y * throwDagger[i].v.y);
			throwDagger[i].l.x = location.x;
			throwDagger[i].l.y = location.y;

			throwDagger[i].unit.x = throwDagger[i].v.x / throwDagger[i].v.length;
			throwDagger[i].unit.y = throwDagger[i].v.y / throwDagger[i].v.length;
			return true;
		}
	}

	return false;
}

void weapon::ThrowDaggerAnim()
{
	for (int i = 0; i < MAX_THROW_DAGGER; i++) {
		if (throwDagger[i].flg) {
			throwDagger[i].l.x += throwDagger[i].v.x;
			throwDagger[i].l.y += throwDagger[i].v.y;

			if (throwDagger[i].l.x < 0 || throwDagger[i].l.x > 1280 ||
				throwDagger[i].l.y < 0 || throwDagger[i].l.y > 720) {
				throwDagger[i].flg = false;
			}
		}
	}
}

void weapon::InitWeapon()
{
	LevelState();
	isAttacking = false;
	oldIsAttacking = false;

	for (int i = 0; i < 10; i++)
	{
		swordSlash[i] = { {0,0},{0,0,0},false };
	}
	hitCnt = 0;
	fpsCnt = 0;
	heelAmount = 10;
	for (int i = 0; i < 10; i++)
	{
		throwDagger[i] = { {0,0},{0,0,0},false };
	}

	slashFlg = false;

	avoidanceDamageFlg = false;
}


//collisionX = (baseVec.x * cos((rot)) - baseVec.y * sin((rot))) + location.x;	//kk
//collisionY = (baseVec.x * sin((rot)) + baseVec.y * cos((rot))) + location.y;	//kk

//回転の公式
//r: 角度(ラジアン)
//x : 元のX座標
//y : 元のY座標

//X = x * cos(r) - y * sin(r)
//Y = x * sin(r) + y * cos(r)