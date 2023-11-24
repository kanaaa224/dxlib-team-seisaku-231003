#pragma once
#include "DxLib.h"
#include "weapon.h"

class Player;

//struct Location
//{
//	float x;
//	float y;
//};

//struct Vector
//{
//	float x;
//	float y;
//};

struct DiffVector
{
	float x;
	float y;
};

struct DiffLocation
{
	float x;
	float y;
};

struct CaleVector
{
	float x;
	float y;
};

struct TmpVector
{
	float x;
	float y;
};

class SphereCollider
{
protected:
	Location location;	//座標
	DiffVector diff;	//プレイヤーの移動量
	Vector vector;		//移動量
	float radius;		//半径
	DiffLocation dL;
	CaleVector caleVector;
	TmpVector tmpVector;

public:
	//
	SphereCollider();

	//当たり判定処理
	int CheckCollision(SphereCollider sphereCollider, Player* player);

	//
	void HitVectorCale(SphereCollider sphereCollider, Player* player);

	//プレイヤーの移動量を加算
	void SetPlayerAmountOfTravel_X(float x);
	void SetPlayerAmountOfTravel_Y(float y);

	float GetEnemyRadius();

	Location GetLocation()
	{
		return location;
	}
};

