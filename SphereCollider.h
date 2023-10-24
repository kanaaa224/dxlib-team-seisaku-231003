#pragma once
#include "DxLib.h"
#include"weapon.h"

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
	SphereCollider();

	int CheckCollision(SphereCollider sphereCollider);

};

