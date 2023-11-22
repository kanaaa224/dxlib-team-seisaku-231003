#pragma once

class weapon;
class second_weapon;
class WeaponLevelUp;
class Player;

class Blacksmith
{
private:
	enum FirstAction
	{
		levelup,
		reset_level
	};

	enum ActionState
	{
		state_first,
		state_weapon,
		//state_reset
	};

	// 画像読込用変数
	int img_cursor;					// カーソル
	int img_chooce;					// レベル選択位置
	int img_hammer;					// ハンマー
	int img_spark;					// 火花
	int img_exclamation_mark;		// ビックリマーク
	int img_arrow;					// 矢印
	int img_question_mark;			// はてなマーク（武器無しの場合）
	int img_button_b;				// Bボタン
	int img_background;			// 背景

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
		bool can_reset;				// レベルリセットできるか
	};

	weapon_information weapon1_info;		// 武器1
	weapon_information weapon2_info;		// 武器2

	int interval;					// インターバル
	int cursor_x;					// カーソルX座標
	int cursor_y;					// カーソルY座標
	int weapon_number;				// 武器番号
	bool is_blacksmith;				// 鍛冶で呼び出されているか（レベルアップ画面に渡すもの）

	// 画像パラメータ
	int img_x;						// 画像のX座標
	int img_y;						// 画像のY座標

	bool action_selection;			// 行動の選択
	int action_number;				// 選択した行動の番号格納用
	bool restore_cursor_position;	// カーソル位置を戻すか
	int cursor_action;				// 今の行動（カーソル移動で使用）

public:
	Blacksmith();
	~Blacksmith();

	// 更新
	void update(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, Player* player);

	// 描画
	void draw(WeaponLevelUp* weapon_levelup)const;

private:
	// 初期設定
	void Init(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup);

	// カーソル移動処理
	void CursorMove();

	// レベルリセット関数
	void ResetLevel(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, weapon_information* info);

	// 行動選択時の描画
	void FirstDraw(WeaponLevelUp* weapon_levelup)const;

	// レベルリセット画面描画
	void DrawResetLevel(WeaponLevelUp* weapon_levelup)const;

	// 武器の画像描画
	void DrawWeaponImages()const;

	// レベルリセット時のテキスト
	void DrawResetLevelText()const;
};