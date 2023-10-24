#include "weapon.h"
#include "inputCtrl.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define d_r(_d) _d * (M_PI / 180)
#define r_d(_r) _r * (180 / M_PI)


weapon::weapon()
{
	weaponType = none;
	baseVec = { 80,0,80 };
	relativeRot = 90.0f;		//武器によって変える
	maxRot = 90.0f;
	coolTime = 120;
	isAttacking = false;
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

void weapon::Update()
{
	//debug
	//x y length　にはプレイヤーとカーソルのベクトルを入れる
	float x = InputCtrl::GetMouseCursor().x - 640;
	float y = InputCtrl::GetMouseCursor().y - 360;
	float length = sqrt((x) * (x) + (y) * (y));

	float innerProduct = ((x) * baseVec.x) + ((y) * baseVec.y);
	float angle = acos(innerProduct / (length * baseVec.length));
	if (y > 0) {
		angle = (M_PI - angle);
		angle += M_PI;
	}

	//武器所有中なら
	if (weaponType != none) {
		//クールタイム中
		if (!(isAttacking) && --coolTime <= 0) {
			isAttacking = true;
			coolTime = 120;
		}

		//攻撃中
		if (isAttacking) {

			if (relativeRot < - maxRot) {
				relativeRot = maxRot;
				isAttacking = false;
			}
			rot = -1 * (angle - (d_r(relativeRot)));

			collisionX = (baseVec.x * cos((rot)) - baseVec.y * sin((rot))) + 640;
			collisionY = (baseVec.x * sin((rot)) + baseVec.y * cos((rot))) + 360;

			relativeRot -= 4.0f;
		}

	}
}

void weapon::Draw() const
{
	//debug
	int x = InputCtrl::GetMouseCursor().x;
	int y = InputCtrl::GetMouseCursor().y;

	DrawFormatString(0, 0, 0xffffff, "%d", x);
	DrawFormatString(0, 30, 0xffffff, "%f", baseVec.x);
	DrawFormatString(0, 60, 0xffffff, "%f", baseVec.y);
	DrawFormatString(0, 90, 0xffffff, "%f", rot);

	if (isAttacking) {
		DrawCircle(collisionX, collisionY, 3, 0xff0000, TRUE);
		DrawLine(640, 360, collisionX, collisionY, 0xffffff);
	}
	

	DrawCircle(640, 360, 3, 0xff0000, TRUE);
}

void weapon::SetWeaponType(int type)
{
	weaponType = type;
	switch (weaponType)
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
	}
}

//回転の公式
//r: 角度(ラジアン)
//x : 元のX座標
//y : 元のY座標

//X = x * cos(r) - y * sin(r)
//Y = x * sin(r) + y * cos(r)