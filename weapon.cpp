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
	baseVec = { 100,0,100 };
	

	relativeRot = 90.0f;		//武器によって変える
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


	relativeRot -= 4.0f;
	if (relativeRot < -90.0f) {
		relativeRot = 90.0f;
	}
	rot = -1 * (angle - (d_r(relativeRot)));

	collisionX = (baseVec.x * cos((rot)) - baseVec.y * sin((rot))) + 640;
	collisionY = (baseVec.x * sin((rot)) + baseVec.y * cos((rot))) + 360;

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
	DrawCircle(collisionX, collisionY, 3, 0xff0000, TRUE);
	DrawCircle(640, 360, 3, 0xff0000, TRUE);
	DrawLine(640, 360, collisionX, collisionY, 0xffffff);
	
}

//回転の公式
//r: 角度(ラジアン)
//x : 元のX座標
//y : 元のY座標

//X = x * cos(r) - y * sin(r)
//Y = x * sin(r) + y * cos(r)