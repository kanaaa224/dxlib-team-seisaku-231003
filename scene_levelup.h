#pragma once

#include"inputCtrl.h"

//#define MAX_LEVEL				8			// レベルの最大値
#define MAX_LEVEL_HIERARCHY		4			// レベル階層の最大値
#define MAX_WEAPON				2			// 所持できる武器の最大数
#define NONE_WEAPON				99			// 武器無し
#define CURSOR_LEFT				-85			// レベル選択時のカーソル位置
#define CURSOR_RIGHT			85			// レベル選択時のカーソル位置

class weapon;

class WeaponLevelUp
{
private:
	// 画像読込用変数
	int img_tree_diagram;			// 樹形図
	int img_cursor;					// カーソル
	int img_choose;					// レベル分岐点（仮）
	//int img_background;			// 背景

	// 武器画像読込用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			// 大剣

	int interval;					// インターバル
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int point;						// レベルアップ用ポイント
	int weapon_number;				// 武器番号
	bool weapon_selection;			// 武器の選択

	int img_x;						// 画像のX座標
	int img_y;						// 画像のY座標

	int cursor_pos;					// レベルアップ時カーソル表示位置

	int weapon1_cursor_pos;			// 武器1のレベルアップ時カーソル表示位置
	int weapon2_cursor_pos;			// 武器2のレベルアップ時カーソル表示位置
	int weapon1_level_hierarchy;	// 武器1のレベルの階層
	int weapon2_level_hierarchy;	// 武器2のレベルの階層

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