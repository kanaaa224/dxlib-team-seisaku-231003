#include "blacksmith.h"

#include "weaponLevelup.h"
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
	img_question_mark = LoadGraph("resources/images/mark_question.png");

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
	cursor_x = 300;
	cursor_y = 320;
	level_cursor_pos = 85;
	//point = 7;
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
	text_display = false;
	is_yes = false;
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
			cursor_x = 900;
			action_number = reset_level;
			//action_number++;

			//if (action_number > reset_level)
			//{
			//	cursor_x = 580;
			//	action_number = levelup;
			//}
		}
		else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
		{
			//左スティックを左に
			interval = 0;
			cursor_x = 300;
			action_number = levelup;

			//action_number--;

			//if (action_number < levelup)
			//{
			//	cursor_x = 960;
			//	action_number = reset_level;
			//}
		}

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			action_selection = true;

			if (action_number == reset_level)
			{
				// カーソル位置を武器1の上に変更
				cursor_x = 580;
				cursor_y = 100;
			}
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
					//restore_cursor_position = true;
					action_selection = false;
				}
			}
		}
		else
		{
			// レベルの振り直し、ポイントの返却


			// 武器の種類のセット
			weapon1_info.type = weapon->GetWeaponType();
			weapon2_info.type = second_weapon->GetWeaponType();

			// 初期設定
			Init(weapon, second_weapon, weapon_levelup);

			// 武器の選択
			if (weapon_selection == false)
			{
				// カーソル移動
				if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
				{
					//左スティックを右に
					interval = 0;
					cursor_x = 960;
					weapon_number = weapon2_info.num;

					//weapon_number++;

					//if (weapon_number > weapon2_info.num)
					//{
					//	cursor_x = 580;
					//	weapon_number = weapon1_info.num;
					//}
				}
				else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
				{
					//左スティックを左に
					interval = 0;
					cursor_x = 580;
					weapon_number = weapon1_info.num;

					//weapon_number--;

					//if (weapon_number < weapon1_info.num)
					//{
					//	cursor_x = 960;
					//	weapon_number = weapon2_info.num;
					//}
				}


				if (weapon_number == weapon1_info.num && weapon1_info.level != 0)
				{
					// Aボタンで武器の決定
					if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
					{
						weapon_selection = true;
						text_display = true;
						cursor_y = 420;
					}
				}
				else if (weapon2_info.num != none && weapon2_info.level_hierarchy != 0)
				{
					// Aボタンで武器の決定
					if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
					{
						weapon_selection = true;
						text_display = true;
						cursor_y = 420;
					}
				}

				// Bボタンで行動選択に戻る
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
				{
					action_number = levelup;
					weapon_number = weapon1_info.num;
					cursor_x = 300;
					cursor_y = 320;
					action_selection = false;
				}
			}
			else
			{
				// レベルリセット
				
				// カーソル初期位置（いいえの位置）
				//cursor_x = 960;

				// カーソル移動
				if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
				{
					//左スティックを右に
					interval = 0;
					cursor_x = 960;
					is_yes = false;
				}
				else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
				{
					//左スティックを左に
					interval = 0;
					cursor_x = 580;
					is_yes = true;
				}

				if (weapon_number == weapon1_info.num)
				{
					// 武器1
					// Aボタンで決定
					if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
					{
						cursor_y = 450;
						if (cursor_x == 580)
						{
							// はい
							// ポイント返却、レベルを0に
							weapon->SetWeaponLevel(0);
							weapon_levelup->Weapon1LevelInit();
							if (weapon1_info.level_hierarchy >= 3)
							{
								weapon_levelup->SetLevelUpPoint(3);
							}
							else
							{
								weapon_levelup->SetLevelUpPoint(weapon1_info.level_hierarchy - 1);
							}

							weapon_number = weapon1_info.num;
							cursor_x = 580;
							cursor_y = 100;
							weapon_selection = false;
							text_display = false;

							// 初期設定
							Init(weapon, second_weapon, weapon_levelup);
						}
						else
						{
							// いいえ
							weapon_number = weapon1_info.num;
							cursor_x = 580;
							cursor_y = 100;
							weapon_selection = false;
							text_display = false;
						}
					}

				}
				else
				{
					// 武器2
					// Aボタンで決定
					if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
					{
						cursor_y = 450;

						if (cursor_x == 580)
						{
							// はい
							// ポイント返却、レベルを0に
							second_weapon->SetWeaponLevel(0);
							weapon_levelup->Weapon2LevelInit();
							if (weapon2_info.level_hierarchy >= 3)
							{
								weapon_levelup->SetLevelUpPoint(3);
							}
							else
							{
								weapon_levelup->SetLevelUpPoint(weapon2_info.level_hierarchy - 1);
							}

							weapon_number = weapon1_info.num;
							cursor_x = 580;
							cursor_y = 100;
							weapon_selection = false;
							text_display = false;

							// 初期設定
							Init(weapon, second_weapon, weapon_levelup);
						}
						else
						{
							// いいえ
							weapon_number = weapon1_info.num;
							cursor_x = 580;
							cursor_y = 100;
							weapon_selection = false;
							text_display = false;
						}
					}

				}

				// Bボタンでレベルリセットキャンセル
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
				{
					// 武器選択に戻る
					weapon_number = weapon1_info.num;
					weapon_selection = false;
					text_display = false;

					// 武器1の上にカーソル位置を戻す
					cursor_x = 580;
					cursor_y = 100;
				}

			}
		
		}
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
	//DrawFormatString(0, 0, 0x000000, "action_number：%d", action_number);
	//DrawFormatString(0, 20, 0x000000, "GetWeaponSelection：%d", weapon_levelup->GetIsCloseLevelUp());
	//DrawFormatString(0, 40, 0x000000, "action_selection：%d", action_selection);
	//DrawFormatString(0, 60, 0x000000, "weapon_selection：%d", weapon_selection);
	//DrawFormatString(0, 80, 0x000000, "action_number：%d", action_number);
	DrawFormatString(0, 100, 0x000000, "cursor_x：%d", cursor_x);
	DrawFormatString(0, 120, 0x000000, "cursor_y：%d", cursor_y);
	DrawFormatString(0, 140, 0xb00000, "キーボードB：閉じる");
	DrawFormatString(0, 160, 0xb00000, "Aボタン：決定");
	DrawFormatString(0, 180, 0xb00000, "Bボタン：キャンセル・戻る");
	DrawFormatString(0, 200, 0x000000, "weapon_number %d", weapon_number);

	if (action_selection == false)
	{
		// カーソル画像
		DrawRotaGraph(cursor_x, cursor_y - 50, 0.08f, 0.0f, img_cursor, TRUE);

		//DrawBox(100, 400, 200, 450, 0xff0000, TRUE);

		// 行動選択時の画像、テキストの表示
		SetFontSize(25);
		DrawFormatString(160, 300, 0x000000, "レベルアップ");
		DrawFormatString(760, 300, 0x000000, "レベルリセット");

		// 画像の表示
		if (action_number == levelup)
		{
			DrawRotaGraph(img_x, img_y , 0.08f, 0.0f, img_hammer, TRUE);
			DrawRotaGraph(img_x, img_y + 50, 0.08f, 0.0f, img_spark, TRUE);
		}
		else
		{
			DrawRotaGraph(img_x, img_y , 0.08f, 0.0f, img_sword, TRUE);
			DrawRotaGraph(img_x, img_y + 50, 0.08f, 0.0f, img_chooce, TRUE);
			//DrawRotaGraph(img_x, img_y + 100, 0.08f, 0.0f, img_arrow, TRUE);
		}

		// 最終強化できる場合
		if (weapon_levelup->GetWeapon1LevelHierarchy() == MAX_LEVEL_HIERARCHY || weapon_levelup->GetWeapon2LevelHierarchy() == MAX_LEVEL_HIERARCHY)
		{
			// ビックリマーク
			DrawRotaGraph(img_x - 400, img_y + 140, 0.08f, 0.0f, img_exclamation_mark, TRUE);

		}
	
	}
	else
	{
		// 行動選択済み
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ時の画像、テキストの表示
			weapon_levelup->draw();
		}
		else
		{
			// レベルの振り直し時の画像、テキストの表示
			DrawFormatString(500, 100, 0x000000, "レベルリセット");

			// 武器画像
			// カーソル
			// 確認文言

				// 武器1の画像
			switch (weapon1_info.type)
			{
			case sword:			// 片手剣
				DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_sword, TRUE);
				break;
			case dagger:		// 短剣
				DrawRotaGraph(img_x, img_y, 0.18f, 0.0f, img_dagger, TRUE);
				break;
			case greatSword:	// 大剣
				DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_great_sword, TRUE);
				break;
			default:
				//DrawRotaGraph(img_x, img_y, 0.1f, 0.0f, img_question_mark, TRUE);
				//DrawFormatString(img_x, img_y, 0x000000, "none");
				break;
			}

			// 武器2の画像
			switch (weapon2_info.type)
			{
			case spear:			// 槍
				DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_spear, TRUE);
				break;
			case frail:			// フレイル
				DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_frail, TRUE);
				break;
			case book:			// 本
				DrawRotaGraph(img_x + 380, img_y, 0.2f, 0.0f, img_book, TRUE);
				break;
			default:
				DrawRotaGraph(img_x + 380, img_y, 0.1f, 0.0f, img_question_mark, TRUE);
				//DrawFormatString(img_x + 360, img_y, 0x000000, "none");
				break;
			}


			// 武器選択カーソル
			if (weapon_selection == false)
			{
				DrawRotaGraph(cursor_x, cursor_y , 0.08f, 0.0f, img_cursor, TRUE);

				// レベルアップをまだしていない場合
				if (weapon_number == weapon1_info.num)
				{
					DrawFormatString(100, 280, 0xff0000, "weapon1");

					if (weapon1_info.level_hierarchy == 0)
					{
						DrawFormatString(100, 300, 0xff0000, "武器のレベルが0です");
						DrawFormatString(100, 320, 0xff0000, "リセット不可");
					}
				}
				else if (weapon_number == weapon2_info.num)
				{
					DrawFormatString(100, 280, 0x0000ff, "weapon2");

					if (weapon2_info.level_hierarchy == 0)
					{
					DrawFormatString(100, 300, 0x0000ff, "武器のレベルが0です");
					DrawFormatString(100, 320, 0x0000ff, "リセット不可");
					}
				}
			}
			else
			{
				DrawRotaGraph(cursor_x, cursor_y, 0.08f, 0.0f, img_cursor, TRUE);
				
				if (text_display == true)
				{
					SetFontSize(20);
					DrawFormatString(500, 300, 0x000000, "武器のレベルを0にする");
					DrawFormatString(550, 450, 0x000000, "はい");
					DrawFormatString(950, 450, 0x000000, "いいえ");

					if (weapon_number == weapon1_info.num)
					{
						DrawFormatString(500, 280, 0xff0000, "weapon1");
						DrawFormatString(500, 350, 0x000000, "返却ポイント：%d", weapon1_info.level_hierarchy - 1);
					}
					else
					{
						DrawFormatString(500, 280, 0x0000ff, "weapon2");
						DrawFormatString(500, 350, 0x000000, "返却ポイント：%d", weapon2_info.level_hierarchy - 1);
					}
				}

			}

		}
	}


#ifdef _DEBUG	
	//// ガイドライン
	//// 縦
	//DrawLine(1280 / 2, 0, 1280 / 2, 720, 0xffff00);
	//DrawLine(1280 / 2 / 2, 0, 1280 / 2 / 2, 720, 0xff0000);
	//DrawLine(1280 / 2 / 2 + 1280 / 2, 0, 1280 / 2 / 2 + 1280 / 2, 720, 0x0000ff);
	//// 横
	//DrawLine(0, 720 / 2, 1280, 720 / 2, 0xffff00);
	//DrawLine(0, 720 / 2 / 2, 1280, 720 / 2 / 2, 0xff0000);
	//DrawLine(0, 720 / 2 / 2 + 720 / 2, 1280, 720 / 2 / 2 + 720 / 2, 0x0000ff);

#endif

}

void Blacksmith::Init(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup)
{
	// 現在の武器レベルのセット
	weapon1_info.level = weapon->GetWeaponLevel();
	weapon2_info.level = second_weapon->GetWeaponLevel();

	// レベル階層のセット
	weapon1_info.level_hierarchy = weapon_levelup->GetWeapon1LevelHierarchy();
	weapon2_info.level_hierarchy = weapon_levelup->GetWeapon2LevelHierarchy();
}
