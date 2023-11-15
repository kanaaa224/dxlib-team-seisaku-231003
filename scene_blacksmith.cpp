#include "scene_blacksmith.h"

#include "scene_levelup.h"
#include "weapon.h"
#include "second_weapon.h"

Blacksmith::Blacksmith()
{
	// 画像の読込
	//img_tree_diagram = LoadGraph("resources/images/levelup.png");
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	//img_branch_point = LoadGraph("resources/images/branch_point.png");
	img_chooce = LoadGraph("resources/images/levelup_choose.png");
	img_hammer = LoadGraph("resources/images/hammer.png");
	img_spark = LoadGraph("resources/images/spark.png");
	img_exclamation_mark = LoadGraph("resources/images/mark_exclamation_white.png");
	img_arrow = LoadGraph("resources/images/arrow.png");

	// 武器画像
	img_sword = LoadGraph("resources/images/sword_longsword_brown.png");
	img_dagger = LoadGraph("resources/images/sword_shortsword_brown.png");
	img_great_sword = LoadGraph("resources/images/tsurugi_bronze_blue.png");
	img_spear = LoadGraph("resources/images/spear.png");
	img_frail = LoadGraph("resources/images/Frailt_dottoy.png");
	img_book = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	// 構造体初期化
	weapon1_info = { 0, none, 0, 0, 0 };
	weapon2_info = { 1, none, 0, 0, 0 };

	// 変数の初期化
	interval = 0;
	cursor_x = 580;
	cursor_y = 120;
	level_cursor_pos = 85;
	point = 7;
	weapon_number = weapon1_info.num;
	weapon_selection = false;
	is_blacksmith = false;

	// 画像パラメータ
	img_x = 580;
	img_y = 140;
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

	action_selection = false;
	action_number = levelup;
	restore_cursor_position = true;

	is_cancel = false;
	count = 0;

}

Blacksmith::~Blacksmith()
{

}

// 更新
void Blacksmith::update(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup)
{
	// カーソルの位置を元に戻す
	//if (restor_cursor_position == true)
	//{
	//	weapon_selection = false;
	//	cursor_x = 580;
	//	weapon_number = weapon1;
	//	restor_cursor_position = false;
	//	// 現在の武器レベルのセット
	//	weapon1_level = weapon->GetWeaponLevel();
	//	weapon2_level = second_weapon->GetWeaponLevel();

	//	// 武器の種類のセット
	//	weapon1_type = weapon->GetWeaponType();
	//	weapon2_type = second_weapon->GetWeaponType();
	//}

	// 15fのインターバル
	if (interval < 15)
	{
		interval++;
	}

	// 行動選択
	if (action_selection == false)
	{
		if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
		{
			//左スティックを右に
			interval = 0;
			cursor_x = 960;
			action_number++;

			if (action_number > reset_level)
			{
				cursor_x = 580;
				action_number = levelup;
			}
		}
		else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
		{
			//左スティックを左に
			interval = 0;
			cursor_x = 580;
			action_number--;

			if (action_number < levelup)
			{
				cursor_x = 960;
				action_number = reset_level;
			}
		}

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			action_selection = true;
		}
	}
	else
	{
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ
			weapon_levelup->SetIsBlacksmith(true);
			weapon_levelup->update(weapon, second_weapon, restore_cursor_position);

			// レベルアップ画面で武器の選択をしていた場合
			if (weapon_levelup->GetIsCloseLevelUp() == true)
			{				
				// Bボタンで行動選択に戻る
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
				{
					action_selection = false;
				}
			}
		}
		else if (action_number == reset_level)
		{
			// レベルの振り直し、ポイントの返却
			// 現在所持している武器のパラメータを変数に格納
			// 武器選択（カーソル移動）
			// Aボタンで決定→確認文言を表示したいためフラグを立てる
			// ①yesを選択（Aボタン）
			// ・ポイントの返却
			// ・選択した武器のレベル階層を0に
			// ・（選択した武器のレベルを0に）
			// ・level_up の bool is_chose[i][5] を全て false に（選択した分岐点の画像を非表示）
			// ②noを選択（Aボタン or Bボタン）
			// ・確認文言を非表示（フラグ管理）にし、武器選択に戻す（カーソル移動）
			// Bボタンで行動選択に戻る
			// 
		}

		//if (is_cancel == false)
		//{
		//	// Bボタンでキャンセル
		//	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		//	{
		//		is_cancel = true;
		//	}
		//}
		//else
		////if (is_cancel == true)
		//{
		//	count++;
		//	if (count >= 10)
		//	{
		//		action_selection = false;
		//		is_cancel = false;
		//		count = 0;
		//	}
		//}

	}

}

// 描画
void Blacksmith::draw(WeaponLevelUp* weapon_levelup) const
{
	// 背景
	DrawBox(0, 0, 1280, 720, 0xb0c4de, TRUE);

	SetFontSize(30);
	DrawFormatString(560, 10, 0x000000, "鍛冶");

	// テスト表示
	SetFontSize(20);
	//DrawFormatString(160, 30, 0x000000, "W1レベル階層 : %d", weapon1_level_hierarchy);
	//DrawFormatString(160, 50, 0x000000, "W2level (State): %d", weapon2_level);
	//DrawFormatString(160, 70, 0x000000, "W2レベル階層 : %d", weapon2_level_hierarchy);

	//DrawFormatString(1000, 20, 0x000000, "仮）P：%d", point);
	DrawFormatString(0, 0, 0x000000, "action_number：%d", action_number);
	DrawFormatString(0, 0, 0x000000, "GetWeaponSelection：%d", weapon_levelup->GetIsCloseLevelUp());

	if (action_selection == false)
	{
		// カーソル画像
		DrawRotaGraph(cursor_x, cursor_y - 50, 0.08f, 0.0f, img_cursor, TRUE);

		DrawBox(100, 400, 200, 450, 0xff0000, TRUE);

		// 行動選択時の画像、テキストの表示
		SetFontSize(25);
		DrawFormatString(160, 300, 0x000000, "レベルアップ");
		DrawFormatString(760, 300, 0x000000, "レベルの振り直し");

		// 画像の表示
		if (action_number == reset_level)
		{
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_hammer, TRUE);
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_spark, TRUE);
		}
		else
		{
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_sword, TRUE);
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_arrow, TRUE);
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_chooce, TRUE);
		}

		// 最終強化できる場合
		if (weapon_levelup->GetWeapon1LevelHierarchy() == MAX_LEVEL_HIERARCHY || weapon_levelup->GetWeapon2LevelHierarchy() == MAX_LEVEL_HIERARCHY)
		{
			// ビックリマーク
			DrawRotaGraph(img_x, img_y - 50, 0.08f, 0.0f, img_exclamation_mark, TRUE);

		}
	
	}
	else
	{
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ時の画像、テキストの表示
			weapon_levelup->draw();
		}
		else
		{
			// レベルの振り直し時の画像、テキストの表示
			DrawFormatString(500, 100, 0x000000, "レベルの振り直し");

			// 武器画像
			// カーソル
			// 確認文言
		}
	}


#ifdef _DEBUG	
	// ガイドライン
	// 縦
	DrawLine(1280 / 2, 0, 1280 / 2, 720, 0xffff00);
	DrawLine(1280 / 2 / 2, 0, 1280 / 2 / 2, 720, 0xff0000);
	DrawLine(1280 / 2 / 2 + 1280 / 2, 0, 1280 / 2 / 2 + 1280 / 2, 720, 0x0000ff);
	// 横
	DrawLine(0, 720 / 2, 1280, 720 / 2, 0xffff00);
	DrawLine(0, 720 / 2 / 2, 1280, 720 / 2 / 2, 0xff0000);
	DrawLine(0, 720 / 2 / 2 + 720 / 2, 1280, 720 / 2 / 2 + 720 / 2, 0x0000ff);

#endif

}
