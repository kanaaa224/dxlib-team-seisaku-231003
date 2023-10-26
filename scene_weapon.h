#pragma once
#include"scene.h"

class weapon;

#define INTERVAL 15
#define SELECT_WEAPON 3

class Weapon_Selection
{
private:
	int interval;
	int cursor_num;
	int cursor_x;

	int sword_image;
	int cursor_image;

public:
	//コンストラクタ
	Weapon_Selection();

	//デストラクタ
	~Weapon_Selection();

	//描画に関すること以外の更新を実装する
	virtual void update(weapon* _weapon, bool &flg);

	//描画に関することの更新を実装する
	virtual void draw()const;
};