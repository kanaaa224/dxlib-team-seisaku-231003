#pragma once
#include"scene.h"

class weapon;
class second_weapon;

#define INTERVAL 15
#define SELECT_WEAPON 3

class Weapon_Selection
{
private:
	int interval;				//インターバル
	int cursor_num;				//カーソル番号
	int select_num;				//選択した番号
	int cursor_x;				//カーソルｘの座標

	int dagger_image;			//短剣の画像
	int sword_image;			//片手剣の画像
	int great_sword_image;		//大剣の画像
	//int spear_image;			//槍の画像
	//int frail_image;			//フレイルの画像
	//int magic_book;				//魔導書の画像

	int button_image;			//ボタンの画像
	int cursor_image;			//カーソル画像

	bool is_selecting;			//武器を選択している？
	bool was_selected;			//すでに武器を選択した？

public:
	//コンストラクタ
	Weapon_Selection(const bool selected);

	//デストラクタ
	~Weapon_Selection();

	//描画に関すること以外の更新を実装する
	virtual void update(weapon* _weapon, second_weapon* _second_weapon, bool& is_weapon_select);

	//描画に関することの更新を実装する
	virtual void draw()const;
};