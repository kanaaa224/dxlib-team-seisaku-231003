#pragma once

#include "scene.h"

class weapon;								// 最初の武器
class second_weapon;						// 二つ目の武器

class ResultScene : public Scene
{
private:

	// 画像用変数
	int img_button_a;				// Aボタン

	// マップアイコン読込用変数
	int img_battle;					// 通常ステージ
	int img_event;					// イベント
	int img_rest;					// 休憩
	int img_anvil;					// 鍛冶
	int img_boss;					// ボス

	// 武器画像読込用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			//大剣
	int img_question_mark;			// はてなマーク（武器無しの場合）
	int img_spear;					// 槍
	int img_frail;					// フレイア
	int img_book;					// 本

	// ロゴ画像読込用変数
	int img_logo_result;
	int img_logo_lv;
	int img_logo_title;
	int img_logo_totaldamage;

	// 武器名ロゴ画像
	int img_logo_dagger;
	int img_logo_sword;
	int img_logo_greatsword;
	int img_logo_spear;
	int img_logo_frail;
	int img_logo_book;

	// レベル7の武器名ロゴ画像
	int img_logo_assasinsdagger;
	int img_logo_legendsword;
	int img_logo_windslash;
	int img_logo_royallance;
	int img_logo_threechain;
	int img_logo_blessing;

	// レベル8の武器名ロゴ画像
	int img_logo_throwingknife;
	int img_logo_magicsword;
	int img_logo_dustsword;
	int img_logo_gungnir;
	int img_logo_earthcrusher;
	int img_logo_bullet;

	// マップアイコン同士の幅
	int img_width;

	// フェード演出
	int value;						// 不透明度

	struct weapon_info
	{
		int type;					// 種類
		int level;					// レベル
		int damage;					// ダメージ総量
	};

	weapon_info weapon1_info;		// 武器1
	weapon_info weapon2_info;		// 武器2

	struct map_info
	{
		int battle_count;			// 通常ステージ
		int event_count;			// イベント
		int rest_count;				// 休憩
		int anvil_count;			// 鍛冶
		int boss_count;				// ボス
	};

	map_info map_info;				// マップ情報

public:
	ResultScene(int result_info[11]);
	~ResultScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;
};