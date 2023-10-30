#pragma once

#include"inputCtrl.h"

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
	int initial_cursor_position;	// 初期のカーソル位置

public:
	WeaponLevelUp();
	~WeaponLevelUp();

	// 更新
	void update();

	// 描画
	void draw()const;
};

