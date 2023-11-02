#include "scene_levelup.h"
#include"weapon.h"

WeaponLevelUp::WeaponLevelUp()
{
	// 画像の読込
	img_tree_diagram = LoadGraph("resources/images/levelup.png");
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_choose = LoadGraph("resources/images/levelup_choose.png");			// 現在未使用
	img_sword = LoadGraph("resources/images/sword_longsword_brown.png");
	img_dagger= LoadGraph("resources/images/sword_shortsword_brown.png");
	img_great_sword = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	// 変数の初期化
	interval = 0;
	cursor_x = 580;
	cursor_y = 130;
	weapon_number = 1;
	weapon_selection = false;

	img_x = 580;
	weapon1_img_x = 580;
	weapon2_img_x = 960;

	cursor_pos = -70;
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
				cursor_x = 960;
				weapon_number--;
				interval = 0;

				if (weapon_number < 1)
				{
					cursor_x = 580;
					weapon_number = 2;
				}
			}
		//}

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			cursor_y++;
			weapon_selection = true;
		}
	}
	else
	{
		if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
		{
			//左スティックを右に
			cursor_pos = 70;
		}
		else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
		{
			//左スティックを左に
			cursor_pos = -70;
		}

		if (weapon_number == 1 && weapon1_level_hierarchy != MAX_LEVEL_HIERARCHY)
		{
			// レベルアップ
			if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
			{
				weapon1_level_hierarchy++;
				// レベル階層の制御
				if (weapon1_level_hierarchy > MAX_LEVEL_HIERARCHY)
				{
					weapon1_level_hierarchy = MAX_LEVEL_HIERARCHY;
				}

				if (cursor_pos == -70)
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
		}

		if (weapon_number == 2 && weapon2_level_hierarchy != MAX_LEVEL_HIERARCHY)
		{
			// 武器2
			// レベルアップ
			if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
			{
				weapon2_level_hierarchy++;
				// レベル階層の制御
				if (weapon2_level_hierarchy > MAX_LEVEL_HIERARCHY)
				{
					weapon2_level_hierarchy = MAX_LEVEL_HIERARCHY;
				}

				if (cursor_pos == -70)
				{
					// 樹形図の左を選択
					weapon2_level++;
				}
				else
				{
					// 樹形図の右を選択
					weapon2_level += 2;
				}

				// レベルの制御
				//if (weapon2_level > MAX_LEVEL)
				//{
				//	weapon2_level = MAX_LEVEL;
				//}
				// 武器にレベルのセット
				//weapon->SetWeaponLevel(weapon2_level);
			}
		}

		// Bボタンで選択武器のキャンセル
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			cursor_y--;
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
	DrawFormatString(160, 10, 0x000000, "Xボタン：閉じる");
	DrawFormatString(160, 30, 0x000000, "Aボタン：加算");
	DrawFormatString(160, 50, 0x000000, "Bボタン：キャンセル");
	DrawFormatString(160, 70, 0x000000, "level1 : %d", weapon1_level);
	DrawFormatString(160, 90, 0x000000, "武器1レベル階層 : %d", weapon1_level_hierarchy);
	DrawFormatString(160, 110, 0x000000, "level2 : %d", weapon2_level);
	DrawFormatString(160, 130, 0x000000, "武器2レベル階層 : %d", weapon2_level_hierarchy);

	// レベルアップの詳細枠
	DrawBox(180, 100, 420, 680, 0x000000, FALSE);
	DrawFormatString(200, 400, 0x000000, "レベルアップ詳細");

	// 武器1の画像
	switch (weapon1_type)
	{
		case sword:			// 片手剣
			DrawRotaGraph(img_x, cursor_y, 0.2f, 0.0f, img_sword, TRUE);
			DrawFormatString(460, 60, 0x000000, "片手剣");
			break;
		case dagger:		// 短剣
			DrawRotaGraph(img_x, cursor_y, 0.2f, 0.0f, img_dagger, TRUE);
			DrawFormatString(460, 60, 0x000000, "短剣");
			break;
		case greatSword:	// 大剣
			DrawRotaGraph(img_x, cursor_y, 0.2f, 0.0f, img_great_sword, TRUE);
			DrawFormatString(460, 60, 0x000000, "大剣");
			break;
		default:
			DrawFormatString(img_x, cursor_y, 0x000000, "none");
			break;
	}

	// 武器2の画像
	switch (weapon2_type)
	{
		case 0:
			//DrawRotaGraph(cursor_x * 2, cursor_y, 0.2f, 0.0f, img_sword, TRUE);
			break;
		case 1:
			//DrawRotaGraph(cursor_x * 2, cursor_y, 0.2f, 0.0f, img_dagger, TRUE);
			break;
		case 2:
			//DrawRotaGraph(cursor_x * 2, cursor_y, 0.2f, 0.0f, img_great_sword, TRUE);
			break;
		default:
			DrawFormatString(img_x + 380, cursor_y, 0x000000, "none");
			break;
	}

	// 武器1、武器2スキルツリー表示
	DrawRotaGraph(img_x, 400, 1.0f, 0.0f, img_tree_diagram, TRUE);
	DrawRotaGraph(img_x + 380, 400, 1.0f, 0.0f, img_tree_diagram, TRUE);

	// 武器選択用の円を描画
	DrawCircle(cursor_x , cursor_y, 20, 0x000000, FALSE);

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

			// 武器1
			// レベル選択の円を描画
			DrawCircle(cursor_x + cursor_pos, cursor_y + 100 + (50 * (weapon1_level_hierarchy + 1)), 20, 0xb00000, FALSE);
			// カーソル表示
			DrawRotaGraph(cursor_x + cursor_pos, cursor_y + 100 + (50 * (weapon1_level_hierarchy + 1)), 0.1f, 0.0f, img_cursor, TRUE);
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
					DrawFormatString(660, 670, 0xb00000, "次は最終強化です");
				}
				// 武器2
				// レベル選択の円を描画
				DrawCircle(cursor_x + cursor_pos, cursor_y + 100 + (50 * (weapon2_level_hierarchy + 1)), 20, 0xb00000, FALSE);

		//	}
		}
	}
}