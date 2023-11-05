#include "EnemyBase.h"
#include "Common.h"
#include <math.h>
#include <cmath>
#include"Stage.h"

EnemyBase::EnemyBase()
{
	hitFlg = NO_COLLISION;
	respawnFlg = false;
	radius = 20;
	alphaNum = MAX_ALPHA;
}

float EnemyBase::PlayerLoad_X(float location_x)
{
	float r = dL.x - location_x;
	return r;
}

float EnemyBase::PlayerLoad_Y(float location_y)
{
	float r = dL.y - location_y;
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

float EnemyBase::HitMoveCale_X(float myvx, float hitvx) 
{
	float r = (myvx + hitvx) / 2;
	return r;
}

float EnemyBase::HitMoveCale_Y(float myvy, float hitvy) 
{
	float r = (myvy + hitvy) / 2;
	return r;
}

int EnemyBase::checkPlayerProximity(float pLocation_x, float pLocation_y, float eLocation_x, float eLocation_y)
{
	float calcAns = sqrt(pow(eLocation_x - pLocation_x, 2) + pow(eLocation_y - pLocation_y, 2));
	calcAns = fabs(calcAns);//絶対値に変更

	//１フレーム前の値を更新
	previousFrameValue = currentFrameValue;

	//現在の値を設定
	currentFrameValue = calcAns;

	if (previousFrameValue < currentFrameValue) {
		return DISTANT;//遠ざかっている
	}
	else if (previousFrameValue > currentFrameValue) {
		return APPROACH;//近づいている
	}
	else if (previousFrameValue == currentFrameValue) {
		return SAME;//同じ
	}
}

//----------------------Inc----------------------//

void EnemyBase::hitFrameCntInc()
{
	hitFrameCounter++;
}

//-----------------------------------------------//
//----------------------get----------------------//

Location EnemyBase::GetEnemyLocation()
{
	return location;
}

int EnemyBase::GetHitFlg()
{
	return hitFlg;
}

float EnemyBase::GetHP()
{
	return hp;
}

bool EnemyBase::GetHitWeaponFlg()
{
	return hitWeaponFlg;
}

bool EnemyBase::GetHit1stFrameFlg()
{
	return hit1stFrameFlg;
}

int EnemyBase::GetHitFrameCnt()
{
	return hitFrameCounter;
}

float EnemyBase::GetDamage() 
{
	return damage;
}

float EnemyBase::GetLX() {
	return location.x;
}

float EnemyBase::GetLY() {
	return location.y;
}

float EnemyBase::GetVX() {
	return vector.x;
}

float EnemyBase::GetVY() {
	return vector.y;
}

//-----------------------------------------------//
//----------------------set----------------------//

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

void EnemyBase::SetHitFlg(int hit)
{
	const int r = hit;
	hitFlg = r;
}

void EnemyBase::SetWeaponDamage(int d)
{
	const int r = d;
	weaponDamage = r;
}

void EnemyBase::SetHitHP(int d) {
	hp -= d;
}

void EnemyBase::SetHitWeaponFlg()
{
	hitWeaponFlg = true;
}

void EnemyBase::SetHit1stFrameFlg(bool flg)
{
	hit1stFrameFlg = flg;
}

void EnemyBase::SetHitFrameCnt(int i) {
	hitFrameCounter = i;
}

void EnemyBase::SetPlayer_Location(Location PL) {
	dL.x = PL.x;
	dL.y = PL.y;
}

void EnemyBase::SetHitLocation_X(float lx) {
	hitLX = lx;
}

void EnemyBase::SetHitLocation_Y(float ly) {
	hitLY = ly;
}

void EnemyBase::SetHitVector_X(float vx) {
	hitVX = vx;
}

void EnemyBase::SetHitVector_Y(float vy) {
	hitVY = vy;
}

//-----------------------------------------------//

bool EnemyBase::IsMoveLimit(Stage stage)
{
	bool ret = false;

	//ステージ内ならtrue
	if (stage.GetStageArray(0).x<location.x - radius && stage.GetStageArray(1).x + STAGEIMG_X>location.x + radius &&
		stage.GetStageArray(0).y<location.y - radius && stage.GetStageArray(2).y + STAGEIMG_Y>location.y + radius)
	{
		ret = true;
	}

	return ret;
}

