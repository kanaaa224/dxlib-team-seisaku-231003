#include "EnemyBase.h"
#include "Common.h"
#include <math.h>

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
