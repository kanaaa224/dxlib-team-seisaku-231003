#include "scene_levelup.h"
#include"weapon.h"

WeaponLevelUp::WeaponLevelUp()
{
	// 画像の読込
	img_tree_diagram = LoadGraph("resources/images/levelup.png");
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_choose = LoadGraph("resources/images/levelup_choose.png");
	img_sword = LoadGraph("resources/images/sword_longsword_brown.png");
	img_dagger= LoadGraph("resources/images/sword_shortsword_brown.png");
	img_great_sword = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	// 変数の初期化
	interval = 0;
	cursor_x = 580;
	cursor_y = 120;
	point = 10;
	weapon_number = 1;
	weapon_selection = false;

	img_x = 580;
	img_y = 140;

	cursor_pos = 0;

	weapon1_cursor_pos = 0;
	weapon2_cursor_pos = 0;
	weapon1_level_hierarchy = 0;
	weapon2_level_hierarchy = 0;

	// 武器1
	weapon1_type = NONE_WEAPON;				// 空
	weapon1_level = 0;

	// 武器2
	weapon2_type = NONE_WEAPON;				// 空
	weapon2_level = 0;
}

WeaponLevelUp::~WeaponLevelUp()
{

}

// 更新
void WeaponLevelUp::update(weapon* weapon, bool& restor_cursor_position)
{
	// カーソルの位置を元に戻す
	if (restor_cursor_position == true)
	{
		weapon_selection = false;
		weapon_number = 1;
		restor_cursor_position = false;
		// 現在の武器レベルのセット
		weapon1_level = weapon->GetWeaponLevel();
		// 武器の種類のセット
		weapon1_type = weapon->GetWeaponType();
	}

	// 15fのインターバル
	if (interval < 15)
	{
		interval++;
	}

	// 武器の選択
	if (weapon_selection == false)
	{
		// 武器を2種類持っていたら武器選択ができる
		//if (weapon2_type != NONE_WEAPON)
		//{
			if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
			{
				//左スティックを右に
				cursor_x = 960;
				weapon_number++;
				interval = 0;

				if (weapon_number > MAX_WEAPON)
				{
					cursor_x = 580;
					weapon_number = 1;
				}
			}
			else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
			{
				//左スティックを左に
				cursor_x = 580;
				weapon_number--;
				interval = 0;

				if (weapon_number < 1)
				{
					cursor_x = 960;
					weapon_number = 2;
				}
			}
		//}

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			weapon_selection = true;
		}
	}
	else
	{
		// 武器1のレベルアップ
		if (weapon_number == 1)
		{
			// レベルアップ
			if (weapon1_level_hierarchy != MAX_LEVEL_HIERARCHY && InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && point > 0)
			{
				point--;
				weapon1_level_hierarchy++;
				// レベル階層の制御
				if (weapon1_level_hierarchy > MAX_LEVEL_HIERARCHY)
				{
					weapon1_level_hierarchy = MAX_LEVEL_HIERARCHY;
				}

				if (weapon1_cursor_pos == CURSOR_LEFT)
				{
					// 樹形図の左を選択
					weapon1_level++;
				}
				else
				{
					// 樹形図の右を選択
					weapon1_level += 2;
				}

				// レベルの制御
				//if (weapon1_level > MAX_LEVEL)
				//{
				//	weapon1_level = MAX_LEVEL;
				//}
				// 武器にレベルのセット
				weapon->SetWeaponLevel(weapon1_level);
			}

			// 武器1のレベルカーソル移動
			if (weapon1_level_hierarchy == 0 || weapon1_level_hierarchy == 3)
			{
				// カーソル移動無し
				weapon1_cursor_pos = 0;
			}
			else if (weapon1_level_hierarchy == 1 || weapon1_level_hierarchy == 4)
			{
				if (weapon1_cursor_pos == 0)
				{
					// レベルの選択ができるときカーソル初期位置は左
					weapon1_cursor_pos = CURSOR_LEFT;
				}

				// レベルの選択
				if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
				{
					//左スティックを右に
					weapon1_cursor_pos = CURSOR_RIGHT;
				}
				else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
				{
					//左スティックを左に
					weapon1_cursor_pos = CURSOR_LEFT;
				}
			}
		}
		else if (weapon_number == 2)
		{
			// レベルアップ
			if (weapon2_level_hierarchy != MAX_LEVEL_HIERARCHY && InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && point > 0)
			{
				point--;
				weapon2_level_hierarchy++;
				// レベル階層の制御
				if (weapon2_level_hierarchy > MAX_LEVEL_HIERARCHY)
				{
					weapon2_level_hierarchy = MAX_LEVEL_HIERARCHY;
				}

				if (cursor_pos == CURSOR_LEFT)
				{
					// 樹形図の左を選択
					weapon2_level++;
				}
				else
				{
					// 樹形図の右を選択
					weapon2_level += 2;
				}

				// 武器にレベルのセット
				//weapon->SetWeaponLevel(weapon2_level);
			}

			// 武器2のレベルカーソル移動
			if (weapon2_level_hierarchy == 0 || weapon2_level_hierarchy == 3)
			{
				// カーソル移動無し
				weapon2_cursor_pos = 0;
			}
			else if (weapon2_level_hierarchy == 1 || weapon2_level_hierarchy == 4)
			{
				if (weapon2_cursor_pos == 0)
				{
					// レベルの選択ができるときカーソル初期位置は左
					weapon2_cursor_pos = CURSOR_LEFT;
				}

				// レベルの選択
				if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
				{
					//左スティックを右に
					weapon2_cursor_pos = CURSOR_RIGHT;
				}
				else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
				{
					//左スティックを左に
					weapon2_cursor_pos = CURSOR_LEFT;
				}
			}
		}

		// Bボタンで選択武器のキャンセル
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			if (weapon1_level_hierarchy == 1 || weapon1_level_hierarchy == 4)
			{
				weapon1_cursor_pos = CURSOR_LEFT;
			}

			if (weapon2_level_hierarchy == 1 || weapon2_level_hierarchy == 4)
			{
				weapon2_cursor_pos = CURSOR_LEFT;
			}

			weapon_selection = false;
		}
	}
}

// 描画
void WeaponLevelUp::draw() const
{
	// 背景
	DrawBox(160, 10, 1120, 710, 0xa0a0a0, TRUE);

	SetFontSize(30);
	DrawFormatString(560, 10, 0x000000, "レベルアップ");

	// テスト表示
	SetFontSize(20);
	DrawFormatString(160, 10, 0x000000, "level1(State?) : %d", weapon1_level);
	DrawFormatString(160, 30, 0x000000, "武器1レベル階層 : %d", weapon1_level_hierarchy);
	DrawFormatString(160, 50, 0x000000, "level2 (State?): %d", weapon2_level);
	DrawFormatString(160, 70, 0x000000, "武器2レベル階層 : %d", weapon2_level_hierarchy);
	DrawFormatString(160, 90, 0x000000, "cursor_x : %d", cursor_x);
	DrawFormatString(160, 110, 0x000000, "cursor_pos : %d", cursor_pos);
	DrawFormatString(160, 130, 0x000000, "weapon1_cursor_pos : %d", weapon1_cursor_pos);
	DrawFormatString(160, 150, 0x000000, "weapon2_cursor_pos : %d", weapon2_cursor_pos);

	// カーソル位置Y確認用
	//DrawFormatString(160, 190, 0x000000, "初期位置cursor_y : %d", cursor_y);
	//DrawFormatString(160, 210, 0x000000, "初期位置からの距離 : %d", 95 * (weapon1_level_hierarchy + 1));
	//DrawFormatString(160, 230, 0x000000, "cursor_y現在地 : %d", cursor_y + (90 * (weapon1_level_hierarchy + 1)));
	
	DrawFormatString(1000, 20, 0x000000, "P：%d", point);

	// レベルアップの詳細枠
	//DrawBox(190, 90, 420, 680, 0x000000, FALSE);
	//DrawFormatString(200, 100, 0x000000, "レベルアップ詳細");
	//DrawFormatString(200, 120, 0x000000, "例）");
	//DrawFormatString(200, 140, 0x000000, "ダメージ　15　→　20 (+5)");
	//DrawFormatString(200, 160, 0x000000, "攻撃速度　10　→　15 (+5)");
	//DrawFormatString(200, 180, 0x000000, "プレイヤーステータス");
	//DrawFormatString(200, 200, 0x000000, "体力　30");
	//DrawFormatString(200, 220, 0x000000, "移動速度　30");

	// 武器1の画像
	switch (weapon1_type)
	{
		case sword:			// 片手剣
			DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_sword, TRUE);
			DrawFormatString(200, 360, 0x000000, "片手剣");
			break;
		case dagger:		// 短剣
			DrawRotaGraph(img_x, img_y, 0.18f, 0.0f, img_dagger, TRUE);
			DrawFormatString(200, 360, 0x000000, "短剣");
			break;
		case greatSword:	// 大剣
			DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_great_sword, TRUE);
			DrawFormatString(200, 360, 0x000000, "大剣");
			break;
		default:
			DrawFormatString(img_x, img_y, 0x000000, "none");
			break;
	}

	// 武器2の画像
	switch (weapon2_type)
	{
		case 0:
			//DrawRotaGraph(cursor_x * 2, img_y, 0.2f, 0.0f, img_sword, TRUE);
			break;
		case 1:
			//DrawRotaGraph(cursor_x * 2, img_y, 0.2f, 0.0f, img_dagger, TRUE);
			break;
		case 2:
			//DrawRotaGraph(cursor_x * 2, img_y, 0.2f, 0.0f, img_great_sword, TRUE);
			break;
		default:
			DrawFormatString(img_x + 360, img_y, 0x000000, "none");
			break;
	}

	// 武器1、武器2スキルツリー表示
	DrawRotaGraph(img_x, img_y + 300, 1.0f, 0.0f, img_tree_diagram, TRUE);
	DrawRotaGraph(img_x + 380, img_y + 300, 1.0f, 0.0f, img_tree_diagram, TRUE);

	// 武器選択用の円を描画
	//DrawCircle(cursor_x , cursor_y, 20, 0x000000, FALSE);

	if (weapon_selection == false)
	{
		DrawRotaGraph(cursor_x, cursor_y - 50, 0.08f, 0.0f, img_cursor, TRUE);
	}

	// 武器選択済み
	if (weapon_selection == true)
	{
		if (weapon_number == 1)
		{
			if (weapon1_level_hierarchy == MAX_LEVEL_HIERARCHY)
			{
				//DrawFormatString(500, 650, 0xb00000, "最下層です");
				DrawFormatString(500, 670, 0xb00000, "次は最終強化です");
			}
			else if (point <= 0)
			{
				DrawFormatString(170, 670, 0xb00000, "ポイントが足りません");
			}

			// 武器1
			// レベル選択の円を描画
			DrawCircle(cursor_x + weapon1_cursor_pos, cursor_y + 48 + (90 * (weapon1_level_hierarchy + 1)), 20, 0xb00000, TRUE);
			// カーソル表示
			DrawRotaGraph(cursor_x + weapon1_cursor_pos, cursor_y + (90 * (weapon1_level_hierarchy + 1)), 0.08f, 0.0f, img_cursor, TRUE);
			// 丸画像表示
			//DrawRotaGraph(cursor_x + weapon1_cursor_pos, cursor_y + 47 + (90 * (weapon1_level_hierarchy + 1)), 0.09f, 0.0f, img_choose, TRUE);
		}
		else
		{
			//if (weapon2_type == NONE_WEAPON)
			//{
			//	DrawFormatString(600, 50, 0x000000, "武器がありません");
			//}
			//else
			//{
				if (weapon2_level_hierarchy == MAX_LEVEL_HIERARCHY)
				{
					//DrawFormatString(250, 650, 0xb00000, "最下層です");
					DrawFormatString(900, 670, 0xb00000, "次は最終強化です");
				}
				else if (point <= 0)
				{
					DrawFormatString(170, 670, 0xb00000, "ポイントが足りません");
				}

				// 武器2
				// レベル選択の円を描画
				DrawCircle(cursor_x + weapon2_cursor_pos, cursor_y + (90 * (weapon2_level_hierarchy + 1)), 20, 0xb00000, FALSE);
				DrawRotaGraph(cursor_x + weapon2_cursor_pos, cursor_y + (90 * (weapon2_level_hierarchy + 1)), 0.08f, 0.0f, img_cursor, TRUE);

		//	}
		}
	}
}