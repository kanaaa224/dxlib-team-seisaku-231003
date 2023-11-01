#pragma once

#include"inputCtrl.h"

#define MAX_LEVEL		8			// レベルの最大値
#define MAX_WEAPON		2			// 所持できる武器の最大数
#define NONE_WEAPON		99			// 武器無し

class weapon;

class WeaponLevelUp
{
private:
	// 画像用変数
	//int img_tree_diagram;			// 樹形図
	//int img_cursor;					// カーソル
	//int img_background;			// 背景

	// 武器画像用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			// 大剣

	int interval;					// インターバル
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int weapon_number;				// 武器番号
	bool weapon_selection;			// 武器の選択

	// 武器1
	int weapon1_type;				// 武器1の種類
	int weapon1_level;				// 武器1のレベル

	// 武器2
	int weapon2_type;				// 武器2の種類
	int weapon2_level;				// 武器2のレベル

public:
	WeaponLevelUp();
	~WeaponLevelUp();

	// 更新
	void update(weapon* weapon, bool& restor_cursor_position);

	// 描画
	void draw()const;
};

