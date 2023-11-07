#include "scene_levelup.h"
#include"weapon.h"
#include "second_weapon.h"

WeaponLevelUp::WeaponLevelUp()
{
	// 画像の読込
	//img_tree_diagram = LoadGraph("resources/images/levelup.png");
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_branch_point = LoadGraph("resources/images/branch_point.png");
	img_chooce = LoadGraph("resources/images/levelup_choose.png");
	// 武器画像
	img_sword = LoadGraph("resources/images/sword_longsword_brown.png");
	img_dagger= LoadGraph("resources/images/sword_shortsword_brown.png");
	img_great_sword = LoadGraph("resources/images/tsurugi_bronze_blue.png");
	img_spear = LoadGraph("resources/images/spear.png");
	img_frail = LoadGraph("resources/images/sword_shortsword_brown.png");
	img_book = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	// 変数の初期化
	interval = 0;
	cursor_x = 580;
	cursor_y = 120;
	point = 10;
	weapon_number = 1;
	weapon_selection = false;

	img_x = 580;
	img_y = 140;

	// 樹形図の分岐点の起点座標
	img_branch_point_x = cursor_x;
	img_branch_point_y = 260;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			branch_point_x[i][j] = cursor_x;
			branch_point_y[i][j] = img_branch_point_y;
			is_chooce[i][j] = false;

		}
	}

	cursor_pos = 0;

	weapon1_cursor_pos = 0;
	weapon2_cursor_pos = 0;
	weapon1_level_hierarchy = 0;
	weapon2_level_hierarchy = 0;

	// 武器1
	weapon1_type = NONE_WEAPON;
	weapon1_level = 0;

	// 武器2
	weapon2_type = NONE_WEAPON;
	weapon2_level = 0;
}

WeaponLevelUp::~WeaponLevelUp()
{

}

// 更新
void WeaponLevelUp::update(weapon* weapon, second_weapon* second_weapon, bool& restor_cursor_position)
{
	// カーソルの位置を元に戻す
	if (restor_cursor_position == true)
	{
		weapon_selection = false;
		weapon_number = 1;
		restor_cursor_position = false;
		// 現在の武器レベルのセット
		weapon1_level = weapon->GetWeaponLevel();
		weapon2_level = second_weapon->GetWeaponLevel();

		// 武器の種類のセット
		weapon1_type = weapon->GetWeaponType();
		weapon2_type = second_weapon->GetWeaponType();
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
		if (weapon2_type != NONE_WEAPON)
		{
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
		}

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
				
				// 選択した分岐点の画像用パラメータの更新
				is_chooce[0][weapon1_level_hierarchy] = true;
				branch_point_x[0][weapon1_level_hierarchy] += weapon1_cursor_pos;
				branch_point_y[0][weapon1_level_hierarchy] += 90 * weapon1_level_hierarchy;

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

				// 選択した分岐点の画像用パラメータの更新
				is_chooce[1][weapon2_level_hierarchy] = true;
				branch_point_x[1][weapon2_level_hierarchy] += 380 + weapon2_cursor_pos;
				branch_point_y[1][weapon2_level_hierarchy] += 90 * weapon2_level_hierarchy;

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
				second_weapon->SetWeaponLevel(weapon2_level);
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
			// レベルカーソルの位置直し
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
	//DrawFormatString(160, 10, 0x000000, "level1(State?) : %d", weapon1_level);
	//DrawFormatString(160, 30, 0x000000, "武器1レベル階層 : %d", weapon1_level_hierarchy);
	//DrawFormatString(160, 50, 0x000000, "level2 (State?): %d", weapon2_level);
	//DrawFormatString(160, 70, 0x000000, "武器2レベル階層 : %d", weapon2_level_hierarchy);

	DrawFormatString(1000, 20, 0x000000, "P：%d", point);

	// レベルアップの詳細枠
	DrawBox(190, 90, 420, 680, 0x000000, FALSE);
	DrawFormatString(200, 140, 0x000000, "レベルアップ詳細");
	DrawFormatString(200, 160, 0x000000, "例）");
	DrawFormatString(200, 180, 0x000000, "ダメージ");
	DrawFormatString(200, 200, 0x000000, "　15　→　20 (+5)");
	DrawFormatString(200, 240, 0x000000, "攻撃速度");
	DrawFormatString(200, 260, 0x000000, "　10　→　15 (+5)");
	DrawFormatString(200, 320, 0x000000, "プレイヤーステータス");
	DrawFormatString(200, 360, 0x000000, "体力");
	DrawFormatString(200, 380, 0x000000, "　        30");
	DrawFormatString(200, 400, 0x000000, "移動速度");
	DrawFormatString(200, 420, 0x000000, "　        30");

	// 武器1の画像
	switch (weapon1_type)
	{
		case sword:			// 片手剣
			DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_sword, TRUE);
			DrawFormatString(200, 100, 0x000000, "片手剣");
			break;
		case dagger:		// 短剣
			DrawRotaGraph(img_x, img_y, 0.18f, 0.0f, img_dagger, TRUE);
			DrawFormatString(200, 100, 0x000000, "短剣");
			break;
		case greatSword:	// 大剣
			DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_great_sword, TRUE);
			DrawFormatString(200, 100, 0x000000, "大剣");
			break;
		default:
			DrawFormatString(img_x, img_y, 0x000000, "none");
			break;
	}

	// 武器2の画像
	switch (weapon2_type)
	{
		case 0:
			DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_spear, TRUE);
			DrawFormatString(img_x + 400, img_y - 60, 0x000000, "槍");
			break;
		case 1:
			DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_frail, TRUE);
			DrawFormatString(img_x + 400, img_y - 60, 0x000000, "フレイル");
			break;
		case 2:
			DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_book, TRUE);
			DrawFormatString(img_x + 400, img_y - 60, 0x000000, "本");
			break;
		default:
			DrawFormatString(img_x + 360, img_y, 0x000000, "none");
			break;
	}

	// スキルツリー表示
	//DrawRotaGraph(img_x + 380, img_y + 300, 1.0f, 0.0f, img_tree_diagram, TRUE);
	
	// スキルツリー分岐点
	for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			// レベル階層によって分岐
			if (i == 0 || i == 3)
			{
				DrawRotaGraph(img_branch_point_x + 380 * j, img_branch_point_y + 90 * i, 0.08f, 0.0f, img_branch_point, TRUE);
			}
			else
			{
				DrawRotaGraph(img_branch_point_x + CURSOR_LEFT + 380 * j, img_branch_point_y + 90 * i, 0.08f, 0.0f, img_branch_point, TRUE);
				DrawRotaGraph(img_branch_point_x + CURSOR_RIGHT + 380 * j, img_branch_point_y + 90 * i, 0.08f, 0.0f, img_branch_point, TRUE);
			}
		}
	}

	// 選択したレベル
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j <= MAX_LEVEL_HIERARCHY; j++)
		{
			if (is_chooce[i][j] == true)
			{
				DrawRotaGraph(branch_point_x[i][j], branch_point_y[i][j], 0.1f, 0.0f, img_chooce, TRUE);
			}
		}
	}

	// 武器選択用の円を描画
	//DrawCircle(cursor_x , cursor_y, 20, 0x000000, FALSE);
	
	// 武器選択カーソル
	if (weapon_selection == false)
	{
		DrawRotaGraph(cursor_x, cursor_y - 50, 0.08f, 0.0f, img_cursor, TRUE);
	}
	else
	{
		// 武器選択済み
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
			DrawCircle(cursor_x + weapon1_cursor_pos, cursor_y + 50 + (90 * (weapon1_level_hierarchy + 1)), 20, 0xb00000, FALSE);
			// カーソル表示
			DrawRotaGraph(cursor_x + weapon1_cursor_pos, cursor_y + (90 * (weapon1_level_hierarchy + 1)), 0.08f, 0.0f, img_cursor, TRUE);
			// 丸画像表示
			//DrawRotaGraph(cursor_x + weapon1_cursor_pos, cursor_y + 50 + (90 * (weapon1_level_hierarchy + 1)), 0.1f, 0.0f, img_chooce, TRUE);
		}
		else
		{
			if (weapon2_type == NONE_WEAPON)
			{
				DrawFormatString(600, 50, 0x000000, "武器がありません");
			}
			else
			{
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
			}
		}
	}
}