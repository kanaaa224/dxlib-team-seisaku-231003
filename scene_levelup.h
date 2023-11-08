#pragma once

#include"inputCtrl.h"

//#define MAX_LEVEL					8		// レベルの最大値
#define MAX_LEVEL_HIERARCHY			4		// レベル階層の最大値
#define LEVEL_HIERARCHY_HEIGHT		90		// 1階層の高さ

class weapon;
class second_weapon;

class WeaponLevelUp
{
private:
	enum WeaponNum
	{
		weapon1,
		weapon2
	};

	// 画像読込用変数
	//int img_tree_diagram;			// 樹形図
	int img_cursor;					// カーソル
	int img_branch_point;			// レベル分岐点
	int img_chooce;					// レベル選択位置
	//int img_background;			// 背景

	// 武器画像読込用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			// 大剣
	int img_spear;					// 槍
	int img_frail;					// フレイア
	int img_book;					// 本

	int interval;					// インターバル
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int level_cursor_pos;			// レベルアップ時カーソル表示位置
	int point;						// レベルアップ用ポイント
	int weapon_number;				// 武器番号
	bool weapon_selection;			// 武器の選択

	// 画像パラメータ
	int img_x;						// 画像のX座標
	int img_y;						// 画像のY座標
	int img_branch_point_x;			// 樹形図の起点X座標
	int img_branch_point_y;			// 樹形図の起点Y座標
	int branch_point_x[2][5];		// 選択した分岐点のX座標を格納
	int branch_point_y[2][5];		// 選択した分岐点のY座標を格納
	bool is_chooce[2][5];			// どのレベル階層まで選択したか

	// 武器1
	int weapon1_type;				// 武器1の種類
	int weapon1_level;				// 武器1のレベル
	int weapon1_cursor_pos;			// 武器1のレベルアップ時カーソル表示位置
	int weapon1_level_hierarchy;	// 武器1のレベルの階層

	// 武器2
	int weapon2_type;				// 武器2の種類
	int weapon2_level;				// 武器2のレベル
	int weapon2_cursor_pos;			// 武器2のレベルアップ時カーソル表示位置
	int weapon2_level_hierarchy;	// 武器2のレベルの階層

public:
	WeaponLevelUp();
	~WeaponLevelUp();

	// 更新
	void update(weapon* weapon, second_weapon* second_weapon, bool& restor_cursor_position);

	// 描画
	void draw()const;

	// レベルアップ詳細のテキスト群
	void DrawLevelUpDetails()const;
};