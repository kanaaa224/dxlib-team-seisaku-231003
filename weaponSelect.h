#pragma once

class weapon;
class second_weapon;

#define INTERVAL 15
#define SELECT_WEAPON 3

class Weapon_Selection
{
private:
	int cnt;					//カウント
	int interval;				//インターバル
	int select_interval;
	int cursor_num;				//カーソル番号
	int select_num;				//選択した番号
	int cursor_x;				//カーソルｘの座標
	int image_shift;			//画像調整用

	int dagger_image;			//短剣の画像
	int sword_image;			//片手剣の画像
	int great_sword_image;		//大剣の画像
	int spear_image;			//槍の画像
	int frail_image;			//フレイルの画像
	int book_image;				//魔導書の画像

	int button_image;			//ボタンの画像
	int cursor_image;			//カーソル画像
	int logo_choice_image;		//武器を選べ！の画像
	int logo_dicision_image;	//決定の画像

	int logo_dagger_iamge;		//短剣のロゴ画像
	int logo_sword_image;		//片手剣のロゴ画像
	int logo_great_sword_image;	//大剣のロゴ画像
	int logo_spear_image;		//槍のロゴ画像
	int logo_frail_image;		//フレイルのロゴ画像
	int logo_book_image;		//魔導書のロゴ画像

	bool is_selecting;			//武器を選択している？

public:
	//コンストラクタ
	Weapon_Selection(const bool selected);

	//デストラクタ
	~Weapon_Selection();

	//描画に関すること以外の更新を実装する
	virtual void update(weapon* _weapon, second_weapon* _second_weapon, bool& is_weapon_select, int& mode);

	//描画に関することの更新を実装する
	virtual void draw(bool flg)const;
};