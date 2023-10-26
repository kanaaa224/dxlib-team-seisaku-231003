#include "EnemyBase.h"
#include "Common.h"
#include <math.h>

EnemyBase::EnemyBase()
{
	radius = 20;
}

float EnemyBase::PlayerLoad_X(float location_x)
{
	float r = PLAYER_LOCATION_X - location_x;
	return r;
}

float EnemyBase::PlayerLoad_Y(float location_y)
{
	float r = PLAYER_LOCATION_Y - location_y;
	return r;
}

float EnemyBase::Normalization_X(float location_x, float location_y)
{
	float a = sqrt(location_x * location_x + location_y * location_y);
	float r = location_x / a;
	return r;
}

float EnemyBase::Normalization_Y(float location_x, float location_y)
{
	float a = sqrt(location_x * location_x + location_y * location_y);
	float r = location_y / a;
	return r;
}

void EnemyBase::SetRespawnPoint()
{
	respawnPosition = GetRand(3);

	switch(respawnPosition){
	case 0://上
		location.x = SetGetRand(-100, 1380);
		location.y = 0;
		break;
	case 1://下
		location.x = SetGetRand(-100, 1380);
		location.y = 720;
		break;
	case 2://右
		location.x = 1280;
		location.y = SetGetRand(-100, 820);
		break;
	case 3://左
		location.x = 0;
		location.y = SetGetRand(-100, 820);
		break;
	}
}

int EnemyBase::SetGetRand(int min, int max) {
	if (min > max) {
		// minとmaxの値を交換する
		int temp = min;
		min = max;
		max = temp;
	}

	if (min >= 0) {
		// 両方の値が0以上の場合
		return GetRand(max - min + 1) + min;
	}
	else if (max >= 0) {
		// minがマイナスでmaxが0以上の場合
		return GetRand(max + abs(min) + 1) - abs(min);
	}
	else {
		// 両方の値がマイナスの場合
		return GetRand(abs(min) - abs(max) + 1) + max;
	}
}