#include "EnemyBase.h"
#include "Common.h"
#include <math.h>
#include <cmath>
#include"Stage.h"

EnemyBase::EnemyBase()
{
	hitFlg = NO_COLLISION;
	respawnFlg = false;
	radius = ENEMY_RADIUS;
	alphaNum = MAX_ALPHA;
}

float EnemyBase::PlayerLoad_X(float location_x)
{
	float r = dL.x - location_x;
	if (dL.x > location_x)
	{
		r -= (radius + 5);
	}
	else
	{
		r += (radius + 5);
	}
	return r;
}

float EnemyBase::PlayerLoad_Y(float location_y)
{
	float r = dL.y - location_y;
	if (dL.y > location_y)
	{
		r -= (radius + 5);
	}
	else
	{
		r += (radius + 5);
	}
	return r;
}

float EnemyBase::PlayerLoad(Location location, bool absFlg)
{
	float x = dL.x - location.x;
	float y = dL.y - location.y;
	float r = sqrt(pow(x, 2) + pow(y, 2));

	//absFlgがtrueなら絶対値で返す
	if (absFlg == true) {
		r = abs(r);
	}
	
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

float EnemyBase::HitMoveCale_X(float mylx, float hitlx)
{
	float r = (mylx + hitlx) / 2;
	return r;
}

float EnemyBase::HitMoveCale_Y(float myly, float hitly) 
{
	float r = (myly + hitly) / 2;
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

int EnemyBase::checkHitEnemyProximity(Location location, float hlx, float hly) 
{
	float calcAns = sqrt(pow(hlx - location.x, 2) + pow(hly - location.y, 2));
	calcAns = fabs(calcAns);//絶対値に変更

	//１フレーム前の値を更新
	previousFrameValue = currentFrameValue;

	//現在の値を設定
	currentFrameValue = calcAns;

	if (previousFrameValue + ENEMY_RADIUS < currentFrameValue + ENEMY_RADIUS) {
		return DISTANT;//遠ざかっている
	}
	else if (previousFrameValue + ENEMY_RADIUS > currentFrameValue + ENEMY_RADIUS) {
		return APPROACH;//近づいている
	}
	else if (previousFrameValue + ENEMY_RADIUS == currentFrameValue + ENEMY_RADIUS) {
		return SAME;//同じ
	}
}

int EnemyBase::CheckImgAngle()
{
	if (dL.x < location.x) {
		return IMG_L;
	}
	else if (dL.x > location.x) {
		return IMG_R;
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

bool EnemyBase::GetRespwanFlg()
{
	return respawnFlg;
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

void EnemyBase::SetRespawnPoint(Player* player, int WaveNum, int arrayNum)
{
	Location pl = player->GetLocation();
	int i = 360 / WaveNum;
	i *= arrayNum;

	if (arrayNum > WaveNum) {
		i -= 360;
	}

	location.x = pl.x + (cos(i) * 400);
	location.y = pl.y + (sin(i) * 400);
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

int EnemyBase::SetRespawnTime(int arrayNum, int MAX_ENEMY_STAGE_NUM, int WaveNum)
{
	int s = 0;
	int fixArrayNum = arrayNum + 1;

	int a = fixArrayNum / (WaveNum + 1);
	s = a * 3;


	return SECOND_FRAME(s);
}

void EnemyBase::SetCloudOfDustHitFlg(bool flg)
{
	cloudOfDustHitFlg = flg;
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

