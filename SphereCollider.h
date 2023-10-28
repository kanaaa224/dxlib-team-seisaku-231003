#pragma once
#include "DxLib.h"
#include "weapon.h"
#include "Player.h"

struct Location
{
	float x;
	float y;
};

//struct Vector
//{
//	float x;
//	float y;
//};

struct DiffLocation
{
	float x;
	float y;
};

class SphereCollider
{
protected:
	Location location;	//座標
	DiffLocation diff;	//プレイヤーの移動量
	Vector vector;		//移動量
	float radius;		//半径

public:
	//
	SphereCollider();

	//当たり判定処理
	int CheckCollision(SphereCollider sphereCollider, Player* player);

	//プレイヤーの移動量を加算
	void SetPlayerAmountOfTravel_X(float x);
	void SetPlayerAmountOfTravel_Y(float y);

};

