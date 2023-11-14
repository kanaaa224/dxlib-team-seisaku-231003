#pragma once

class weapon;
class second_weapon;
class WeaponLevelUp;

class Blacksmith
{
private:
	enum ActionNum
	{
		levelup,
		reset_level
	};

	// 画像読込用変数
	//int img_tree_diagram;			// 樹形図
	int img_cursor;					// カーソル
	//int img_branch_point;			// レベル分岐点
	//int img_chooce;					// レベル選択位置
	//int img_background;			// 背景

	int img_hammer;					// ハンマー
	int img_spark;					// 火花
	int img_question_mark;			// はてなマーク
	int img_exclamation_mark;		// ビックリマーク
	int img_arrow;					// 矢印

	// 武器画像読込用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			// 大剣
	int img_spear;					// 槍
	int img_frail;					// フレイア
	int img_book;					// 本

	// 武器の情報
	struct weapon_information
	{
		int num;
		int type;					// 武器の種類
		int level;					// 武器のレベル
		int cursor_pos;				// 武器のレベルアップ時カーソル表示位置
		int level_hierarchy;		// 武器のレベルの階層
	};

	weapon_information weapon1_info;		// 武器1
	weapon_information weapon2_info;		// 武器2

	int interval;					// インターバル
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int level_cursor_pos;			// レベルアップ時カーソル表示位置
	int point;						// レベルアップ用ポイント
	int weapon_number;				// 武器番号
	bool weapon_selection;			// 武器の選択
	bool is_blacksmith;				// 鍛冶で呼び出されているか

	// 画像パラメータ
	int img_x;						// 画像のX座標
	int img_y;						// 画像のY座標
	int img_branch_point_x;			// 樹形図の起点X座標
	int img_branch_point_y;			// 樹形図の起点Y座標
	int branch_point_x[2][5];		// 選択した分岐点のX座標を格納
	int branch_point_y[2][5];		// 選択した分岐点のY座標を格納
	bool is_chooce[2][5];			// どのレベル階層まで選択したか

	bool action_selection;			// 行動の選択
	int action_number;
	bool restore_cursor_position;

public:
	Blacksmith();
	~Blacksmith();

	// 更新
	void update(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup);

	// 描画
	void draw(WeaponLevelUp* weapon_levelup)const;
};