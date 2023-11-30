#include "main.h"

Blacksmith::Blacksmith()
{
	// 画像の読込
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_chooce = LoadGraph("resources/images/levelup_choose.png");
	img_hammer = LoadGraph("resources/images/hammer.png");
	img_spark = LoadGraph("resources/images/spark.png");
	img_exclamation_mark = LoadGraph("resources/images/mark_exclamation_white.png");
	img_arrow = LoadGraph("resources/images/arrow.png");
	img_question_mark = LoadGraph("resources/images/mark_question.png");
	img_button_b = LoadGraph("resources/images/button_b.png");
	// テスト用
	img_background = LoadGraph("resources/images/stageimage2.png");

	// 武器画像
	img_sword = LoadGraph("resources/images/sword_longsword_brown.png");
	img_dagger = LoadGraph("resources/images/sword_shortsword_brown.png");
	img_great_sword = LoadGraph("resources/images/tsurugi_bronze_blue.png");
	img_spear = LoadGraph("resources/images/spear.png");
	img_frail = LoadGraph("resources/images/Frailt_dottoy.png");
	img_book = LoadGraph("resources/images/book_madousyo_necronomicon.png");

	// 構造体初期化
	weapon1_info = { 0, none, 0, 0, 0, false };
	weapon2_info = { 1, none, 0, 0, 0, false };

	// 変数の初期化
	interval = 0;
	cursor_x = 370;
	cursor_y = 320;
	weapon_number = weapon1_info.num;
	//is_blacksmith = false;

	// 画像パラメータ
	img_x = 350;
	img_y = 350;

	action_selection = false;
	action_number = levelup;
	restore_cursor_position = true;
	cursor_action = state_first;
}

Blacksmith::~Blacksmith()
{

}

// 更新
void Blacksmith::update(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, Player* player, int& point, int& mode, int& stage)
{
	// 15fのインターバル
	if (interval < 15)
	{
		interval++;
	}

	// 行動選択
	if (action_selection == false)
	{
		// カーソル左右移動
		CursorMove();

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			action_selection = true;

			if (action_number == reset_level)
			{
				cursor_action = state_weapon;
				// カーソル位置を武器1の上に変更
				cursor_x = img_x;
				cursor_y = 160;
			}
		}

		// Bボタンで出る
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			stage++;
			mode = GameSceneMode::map;
		}
	}
	else
	{
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ
			weapon_levelup->SetIsBlacksmith(true);
			weapon_levelup->update(weapon, second_weapon, player, restore_cursor_position, point);

			// レベルアップ画面で武器の選択をしていた場合
			if (weapon_levelup->GetIsCloseLevelUp() == true)
			{
				// Bボタンで行動選択に戻る
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
				{
					// レベルアップ画面の変数初期化
					// レベルアップ画面を閉じたときに初期化しないと画像の表示位置がおかしくなってしまう
					//restore_cursor_position = true;
					weapon_levelup->Init(weapon, second_weapon, restore_cursor_position);

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

			// カーソル左右移動
			CursorMove();

			// 武器の決定
			if (weapon_number == weapon1_info.num && weapon1_info.level != 0)
			{
				weapon1_info.can_reset = true;

				// 過去にレベルアップしたことがある場合選択できる
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
				{
					ResetLevel(weapon, second_weapon, weapon_levelup, &weapon1_info, point);
				}
			}
			else if (weapon2_info.num != none && weapon2_info.level_hierarchy != 0)
			{
				weapon2_info.can_reset = true;

				if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
				{
					ResetLevel(weapon, second_weapon, weapon_levelup, &weapon2_info, point);
				}
			}

			// Bボタンで行動選択に戻る
			if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
			{
				cursor_action = state_first;
				action_number = levelup;
				weapon_number = weapon1_info.num;
				cursor_x = 370;
				cursor_y = 320;
				action_selection = false;
			}
		}
	}
}

// 描画
void Blacksmith::draw(WeaponLevelUp* weapon_levelup) const
{
	// 背景
	DrawBox(0, 0, 1280, 720, 0x808080, TRUE);
	DrawGraph(0, 0, img_background, TRUE);

	if (action_selection == false)
	{
		// 行動選択時の描画
		FirstDraw(weapon_levelup);
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
			// レベルリセット画面描画
			DrawResetLevel(weapon_levelup);
		}
	}


#ifdef _DEBUG	
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
	//DrawFormatString(0, 100, 0x000000, "cursor_x：%d", cursor_x);
	//DrawFormatString(0, 120, 0x000000, "cursor_y：%d", cursor_y);
	//DrawFormatString(0, 140, 0xb00000, "キーボードB：閉じる");
	//DrawFormatString(0, 160, 0xb00000, "Aボタン：決定");
	//DrawFormatString(0, 180, 0xb00000, "Bボタン：キャンセル・戻る");
	//DrawFormatString(0, 200, 0x000000, "weapon_number %d", weapon_number);
	//DrawFormatString(0, 220, 0x000000, "cursor_action %d", cursor_action);
	//DrawFormatString(0, 240, 0x000000, "cursor_x %d", cursor_x);
	//DrawFormatString(0, 260, 0x000000, "cursor_y %d", cursor_y);
	//DrawFormatString(0, 280, 0x000000, "action_number %d", action_number);

	// ガイドライン
	// 縦
	//DrawLine(1280 / 2, 0, 1280 / 2, 720, 0xffffaa);
	//DrawLine(1280 / 2 / 2, 0, 1280 / 2 / 2, 720, 0xffaaaa);
	//DrawLine(1280 / 2 / 2 + 1280 / 2, 0, 1280 / 2 / 2 + 1280 / 2, 720, 0xaaaaff);
	//// 横
	//DrawLine(0, 720 / 2, 1280, 720 / 2, 0xffffaa);
	//DrawLine(0, 720 / 2 / 2, 1280, 720 / 2 / 2, 0xffaaaa);
	//DrawLine(0, 720 / 2 / 2 + 720 / 2, 1280, 720 / 2 / 2 + 720 / 2, 0xaaaaff);
	
//	DrawFormatString(0, 0, 0x000000, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif

}

// 初期設定
void Blacksmith::Init(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup)
{
	// 現在の武器レベルのセット
	weapon1_info.level = weapon->GetWeaponLevel();
	weapon2_info.level = second_weapon->GetWeaponLevel();

	// レベル階層のセット
	weapon1_info.level_hierarchy = weapon_levelup->GetWeapon1LevelHierarchy();
	weapon2_info.level_hierarchy = weapon_levelup->GetWeapon2LevelHierarchy();
}

// カーソル左右移動処理
void Blacksmith::CursorMove()
{
	if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
	{
		//左スティックを右に
		interval = 0;

		if (cursor_action == state_first)
		{
			cursor_x = 900;
			action_number = reset_level;
		}
		else
		{
			cursor_x = img_x + 555;
			weapon_number = weapon2_info.num;
		}
	}
	else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
	{
		//左スティックを左に
		interval = 0;

		if (cursor_action == state_first)
		{
			cursor_x = 370;
			action_number = levelup;
		}
		else
		{
			cursor_x = img_x;
			weapon_number = weapon1_info.num;
		}
	}
}

// レベルリセット
void Blacksmith::ResetLevel(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, weapon_information* info, int& point)
{
	// レベルリセット
	if (info->num == weapon1_info.num)
	{
		// 武器1
		weapon->SetWeaponLevel(0);
		weapon_levelup->Weapon1LevelInit();
	}
	else
	{
		// 武器2
		second_weapon->SetWeaponLevel(0);
		weapon_levelup->Weapon2LevelInit();
	}

	// ポイントの返却
	if (info->level_hierarchy >= 3)
	{
		weapon_levelup->SetLevelUpPoint(point, 3);
	}
	else
	{
		weapon_levelup->SetLevelUpPoint(point, info->level_hierarchy - 1);
	}

	info->can_reset = false;

	// 初期設定
	Init(weapon, second_weapon, weapon_levelup);

}

// 行動選択時の描画
void Blacksmith::FirstDraw(WeaponLevelUp* weapon_levelup) const
{
	// カーソル画像
	DrawRotaGraph(cursor_x , 100, 0.1f, 0.0f, img_cursor, TRUE);

	DrawBox(170, 130, 570, 590, 0xaa0000, TRUE);
	DrawBox(710, 130, 1110, 590, 0xaa0000, TRUE);

	if (action_number == reset_level)
	{
		DrawBox(170, 130, 570, 590, 0xd3d3d3, TRUE);
	}
	else
	{
		DrawBox(710, 130, 1110, 590, 0xd3d3d3, TRUE);
	}

	SetFontSize(50);
	DrawFormatString(740, 520, 0x000000, "レベルリセット");
	DrawFormatString(210, 520, 0x000000, "レベルアップ");

	// 画像の表示
	DrawRotaGraph(430, 280, 0.5f, 0.0f, img_hammer, TRUE);
	DrawRotaGraph(250, 370, 0.2f, 0.0f, img_spark, TRUE);
	DrawRotaGraph(1030, 210, 0.2f, 0.0f, img_sword, TRUE);
	DrawRotaGraph(930, 270, 0.2f, M_PI / - 4.0f, img_arrow, TRUE);
	DrawRotaGraph(780, 340, 0.15f, 0.0f, img_chooce, TRUE);
	DrawRotaGraph(840, 355, 0.15f, 0.0f, img_chooce, TRUE);
	DrawRotaGraph(800, 390, 0.15f, 0.0f, img_chooce, TRUE);

	// 最終強化できる場合
	if (weapon_levelup->GetWeapon1LevelHierarchy() == MAX_LEVEL_HIERARCHY || weapon_levelup->GetWeapon2LevelHierarchy() == MAX_LEVEL_HIERARCHY)
	{
		// ビックリマーク
		DrawRotaGraph(170, 130, 0.2f, 0.0f, img_exclamation_mark, TRUE);
	}

	DrawBox(1100, 660, 1250, 710, 0xd3d3d3, TRUE);
	DrawRotaGraph(1150, 685, 0.25f, 0.0f, img_button_b, TRUE);
	SetFontSize(20);
	//DrawFormatString(1100, 675, 0x000000, "Bキーで");
	DrawFormatString(1180, 675, 0x000000, "出る");
}

// レベルリセット画面描画
void Blacksmith::DrawResetLevel(WeaponLevelUp* weapon_levelup) const
{
	DrawBox(200, 200, 500, 600, 0x909090, TRUE);
	DrawBox(770, 200, 1070, 600, 0x909090, TRUE);
	if (weapon_number == weapon1_info.num)
	{
		DrawBox(200, 200, 500, 600, 0xd3d3d3, TRUE);
	}
	else
	{
		DrawBox(770, 200, 1070, 600, 0xd3d3d3, TRUE);
	}

	DrawBox(490, 35, 790, 120, 0xd3d3d3, TRUE);
	SetFontSize(35);
	DrawFormatString(510, 45, 0x000000, "レベルリセット");
	SetFontSize(15);
	DrawFormatString(530, 100, 0xb00000, "武器のレベルが0になります");

	// 武器の画像描画
	DrawWeaponImages();

	// 武器の情報のテキスト
	DrawResetLevelText();

	// カーソル画像
	DrawRotaGraph(cursor_x, cursor_y, 0.1f, 0.0f, img_cursor, TRUE);
	DrawBox(1100, 660, 1250, 710, 0xd3d3d3, TRUE);
	DrawRotaGraph(1150, 685, 0.25f, 0.0f, img_button_b, TRUE);
	DrawFormatString(1180, 675, 0x000000, "戻る");
}

// 武器の画像描画
void Blacksmith::DrawWeaponImages() const
{
	SetFontSize(20);
	// 武器1の画像
	switch (weapon1_info.type)
	{
	case sword:			// 片手剣
		DrawRotaGraph(img_x, img_y, 0.4f, 0.0f, img_sword, TRUE);
		DrawFormatString(250, 530, 0x000000, "片手剣");
		break;
	case dagger:		// 短剣
		DrawRotaGraph(img_x, img_y, 0.4f, 0.0f, img_dagger, TRUE);
		DrawFormatString(250, 530, 0x000000, "短剣");
		break;
	case greatSword:	// 大剣
		DrawRotaGraph(img_x, img_y, 0.4f, 0.0f, img_great_sword, TRUE);
		DrawFormatString(250, 530, 0x000000, "大剣");
		break;
	default:
		DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(250, 530, 0x000000, "武器がありません");
		break;
	}

	// 武器2の画像
	switch (weapon2_info.type)
	{
	case spear:			// 槍
		DrawRotaGraph(img_x + 570, img_y, 0.4f, 0.0f, img_spear, TRUE);
		DrawFormatString(830, 530, 0x000000, "槍");
		break;
	case frail:			// フレイル
		DrawRotaGraph(img_x + 570, img_y, 0.4f, 0.0f, img_frail, TRUE);
		DrawFormatString(830, 530, 0x000000, "フレイル");
		break;
	case book:			// 魔導書
		DrawRotaGraph(img_x + 570, img_y, 0.4f, 0.0f, img_book, TRUE);
		DrawFormatString(830, 530, 0x000000, "魔導書");
		break;
	default:
		DrawRotaGraph(img_x + 570, img_y, 0.2f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(830, 530, 0x000000, "武器がありません");
		break;
	}

}

// 武器の情報のテキスト
void Blacksmith::DrawResetLevelText() const
{
	SetFontSize(20);
	// 武器1
	DrawFormatString(250, 550, 0x000000, "Lv階層 %d", weapon1_info.level_hierarchy);
	DrawFormatString(400, 550, 0x000000, "Lv. %d", weapon1_info.level);

	if (weapon1_info.can_reset == false)
	{
		DrawFormatString(250, 570, 0xb00000, "レベルリセット不可");
	}
	else
	{
		if (weapon1_info.level_hierarchy > 0 && weapon1_info.level_hierarchy <= 3)
		{
			DrawFormatString(250, 570, 0x000000, "返却ポイント： %d", weapon1_info.level_hierarchy - 1);
		}
		else if (weapon1_info.level_hierarchy > 3)
		{
			DrawFormatString(250, 570, 0x000000, "返却ポイント： 3");
		}
	}

	// 武器2
	DrawFormatString(830, 550, 0x000000, "Lv. %d", weapon2_info.level_hierarchy);
	if (weapon2_info.can_reset == false)
	{
		DrawFormatString(830, 570, 0xb00000, "レベルリセット不可");
	}
	else
	{
		if (weapon2_info.level_hierarchy > 0 && weapon2_info.level_hierarchy <= 3)
		{
			DrawFormatString(830, 570, 0x000000, "返却ポイント： %d", weapon2_info.level_hierarchy - 1);
		}
		else if (weapon2_info.level_hierarchy > 3)
		{
			DrawFormatString(830, 570, 0x000000, "返却ポイント： 3");
		}
	}

}
