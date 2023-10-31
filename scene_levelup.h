#pragma once

#include"inputCtrl.h"

#define MAX_LEVEL 5

class WeaponLevelUp
{
private:
	// 画像用変数
	//int img_weapon1;				// 武器１
	//int img_weapon2;				// 武器２
	//int img_tree_diagram;			// 樹形図
	//int img_cursor;					// カーソル
	//int img_background;			// 背景

	int test;
	int interval;
	int initial_cursor_position;	// 初期のカーソル位置
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int weapon_number;				// 武器番号
	bool weapon_selection;			// 武器の選択
	int level_weapon1;						// 武器のレベル
	int level_weapon2;						// 武器のレベル

public:
	WeaponLevelUp();
	~WeaponLevelUp();

	// 更新
	void update();

	// 描画
	void draw()const;
};

