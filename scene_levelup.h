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
	int img_question_mark;			// はてなマーク（武器無しの場合）

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

	// 鍛冶とのやり取り
	bool is_blacksmith;				// 鍛冶で呼び出されているか
	bool is_close_level_up;			// 鍛冶でレベルアップ画面を閉じても良いか

	// 画像パラメータ
	int img_x;						// 画像のX座標
	int img_y;						// 画像のY座標
	int img_branch_point_x;			// 樹形図の起点X座標
	int img_branch_point_y;			// 樹形図の起点Y座標
	int branch_point_x[2][5];		// 選択した分岐点のX座標を格納
	int branch_point_y[2][5];		// 選択した分岐点のY座標を格納
	bool is_chooce[2][5];			// どのレベル階層まで選択したか

public:
	WeaponLevelUp();
	~WeaponLevelUp();

	// 更新
	void update(weapon* weapon, second_weapon* second_weapon, bool& restor_cursor_position);

	// 描画
	void draw()const;

private:
	// 初期化処理
	void Init(weapon* weapon, second_weapon* second_weapon, bool& restor_cursor_position);

	// レベルアップ処理
	void LevelUp(weapon* weapon, second_weapon* second_weapon, weapon_information* info);

	// レベルアップのカーソル移動
	void LevelUpCursorMove(weapon_information* info);

	// レベルアップカーソルの位置を戻す
	void ReturnLevelUpCursorPos(weapon_information* info);

	// レベルアップ詳細のテキスト群
	void DrawLevelUpDetails()const;

public:
	/***********************
	**	Set関数、Get関数
	***********************/

	// 鍛冶で返却されたポイントの設定
	void SetLevelUpPoint(int return_point)
	{
		point += return_point;
	}

	// 現在所持しているポイントの取得
	int GetLevelUpPoint() { return point; }

	// 鍛冶で使うやつ
	void SetIsBlacksmith(bool set_bool)
	{
		is_blacksmith = set_bool;
	}

	bool GetIsCloseLevelUp()const
	{ 
		return is_close_level_up;
	}

	// レベル階層の取得
	int GetWeapon1LevelHierarchy() { return weapon1_info.level_hierarchy; }
	int GetWeapon2LevelHierarchy() { return weapon2_info.level_hierarchy; }

	void SetWeapon1LevelHierarchy()
	{
		weapon1_info.level_hierarchy = 0;
	}

	void SetWeapon2LevelHierarchy()
	{
		weapon2_info.level_hierarchy = 0;
	}

	void SetWeapon1LevelDisplay()
	{
		for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
		{
			is_chooce[0][i] = false;
		}
	}

	void SetWeapon2LevelDisplay()
	{
		for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
		{
			is_chooce[1][i] = false;
		}
	}

};